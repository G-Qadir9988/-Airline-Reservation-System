#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Forward declarations
class Passenger;
class FlightState;
class Flight;
class Crew;
class Airline;
class PricingEngine;
class FileHandler;
class ScheduledState;
class CancelledState;
class DelayedState;
class Observer;
class PassengerObserver;
class CrewObserver;
class Reservation;

// Enum for crew states (Available or Training)
enum class CrewState {
    Available,
    Training
};

// Enum for crew roles
enum class CrewRole {
    Pilot,
    CoPilot,
    FlightAttendant
};

// Enum for seat types
enum class SeatType {
    Economy,
    Business,
    FirstClass
};

// Function to convert SeatType enum to string
string convertSeatTypeToString(SeatType seatType) {
    switch (seatType) {
    case SeatType::Economy:
        return "Economy";
    case SeatType::Business:
        return "Business";
    case SeatType::FirstClass:
        return "FirstClass";
    }
    return "";
}



// PricingEngine class 

//calculate the final price of ticket according to provided factors like seasonal factor, event factor and demand factor
class PricingEngine {
private:
    //PricingStrategy* strategy;
    double seasonalFactor;
    double eventFactor;
    double demandFactor;

public:

    PricingEngine(double sf = 1,double ef = 1 , double df = 1) : seasonalFactor(sf),eventFactor(ef),demandFactor(df){}
	/*If seasonalFactor is non-zero, basePrice is multiplied by seasonalFactor; otherwise, basePrice remains unchanged.
If eventFactor is non-zero, the intermediate result is further multiplied by eventFactor.
If demandFactor is non-zero, the result is finally multiplied by demandFactor.
This ensures that the final price is adjusted according to the provided factors.*/
  
    double calculatePrice(double basePrice) {
        double ans = (seasonalFactor ? basePrice * seasonalFactor : basePrice);
        if (eventFactor) ans *= eventFactor;
        if (demandFactor) ans *= demandFactor;
        return ans;
    }
};

// FileHandler class (Facade for handling file operations)
class FileHandler {
private:
    string filePath;

public:
    FileHandler(string filePath) : filePath(filePath) {}

    void readData(Airline& airline);

    void updateData(string route, double basePrice, double demandFactor, double seasonalFactor, double eventFactor);
};

// FlightState interface
class FlightState {
public:
    string status;
    virtual void updateStatus(string status) = 0;
};

// ScheduledState concrete state
class ScheduledState : public FlightState {
public:
    //string status;
    void updateStatus(string status) override {
        // Implement updating flight status to Scheduled
        this->status = "Scheduled";
    }
};

// CancelledState concrete state
class CancelledState : public FlightState {
public:
    //string status;
    void updateStatus(string status) override {
        // Implement updating flight status to Cancelled
        this->status = "Cancelled";
    }
};

// DelayedState concrete state
class DelayedState : public FlightState {
public:
    //string status;
    void updateStatus(string status) override {
        // Implement updating flight status to delayed
        this->status = "Delayed";
    }
};

// Observer interface
class Observer {
public:
    virtual void update() = 0;
};

// PassengerObserver concrete observer
class PassengerObserver : public Observer {
public:
    void update() override {
        // No Implementation Required
    }
};

// CrewObserver concrete observer
class CrewObserver : public Observer {
public:
    void update() override {
        // No Implementation Required
    }
};

// Airline class
class Airline {
private:
    string name;
    vector<Flight*> flights;
    vector<Crew*> crews;
    vector<Passenger*> passengers;
public:
    Airline(string name) : name(name) {}

    // Getter for name, name
    string getName() const {
        return name;
    }

    // Getter for flights , return flights
    //Returns a constant reference to the vector of flights pointers.
    const vector<Flight*>& getFlights() const {
        return flights;
    }

    // Getter for crews, return crew
    //Returns a constant reference to the vector of crews pointers.
    const vector<Crew*>& getCrews() const {
        return crews;
    }

    // Getter for passengers return passenger
    //Returns a constant reference to the vector of passengers pointers.
    const vector<Passenger*>& getPassengers() const {
        return passengers;
    }

    void addFlight(Flight* flight) {
        flights.push_back(flight);
    }

   

    void addCrew(Crew* crew) {
        crews.push_back(crew);
    }

    void removeCrew(Crew* crew) {
        // Implement removal logic
        for (int i = 0; i < crews.size(); i++) {
            if (crews[i] == crew) {
                for (int j = i; j < crews.size() - 1; j++) {
                    crews[i] = crews[i + 1];
                }
                crews.pop_back();
                break;
            }
        }
    }

    void assignCrewToFlight(Flight* flight, Crew* crew);

    void handleScheduleConflicts(Flight* flight) {
        // Handle schedule conflicts for the flight
    }
};

// Flight class with state pattern integration
class Flight {
private:
    int price;
    string route;
    vector<Passenger*> passengers;
    vector<Crew*> crew;
    FlightState* currentState;
    string time;

public:
    Flight(string route , string time = "1 am ,Day 1",int price = 100) : route(route), time(time),price(price) {
        currentState = new ScheduledState();
        currentState->status = "Scheduled.\n";
    }

    void setPrice(int price) {
        this->price = price;
    }

    int getPrice() {
        return price;
    }

    // Getter for route
    string getRoute() const {
        return route;
    }

    // Getter for passengers
    const vector<Passenger*>& getPassengers() const {
        return passengers;
    }

    // Getter for crew
    vector<Crew*>& getCrew() {
        return crew;
    }

    void setRoute(string s) {
        route = s;
    }

    // Getter for currentState
    FlightState* getCurrentState() const {
        return currentState;
    }

    FlightState*& getState() { return currentState; }

    void updateSchedule(string status) {
        currentState->updateStatus(status);
    }

    void setState(FlightState* state) {
        currentState = state;
        updateSchedule("Cancelled");
    }

    string getTime() const {
        return time;
    }

    void removeCrew(int idx) {
        for (int i = idx; i < crew.size()-1; i++) {
            crew[i] = crew[i + 1];
        }
        crew.pop_back();
    }

    void setTime(string newTime) {
        time = newTime;
        //cout << "\nNew time has been set Successfully.\n";
    }

    void reroute(string newRoute) {

        route = newRoute;
    }

    void makeReservation(Passenger* passenger, string seat) {
        // Logic Already implemented
    }
};


// Passenger class
class Passenger {
private:
    string name;
    vector<Reservation*> reservations;
    bool loyaltyEligibility;
    string seat;

public:
    Passenger(string name) : name(name), loyaltyEligibility(rand() % 2) {}

    void bookFlight(Flight* flight, string seat) {
        // Implemented
    }

    void cancelReservation(int idx) {
        // Implement cancellation logic
        for (int i = idx; i < reservations.size() - 1; i++) {
            reservations[i] = reservations[i + 1];
        }
        reservations.pop_back();

        cout << "Your Desired Reservation has been successfully removed.\n";
    }

    vector<Reservation*>& getReservations() { return reservations; }

    void modifyReservation(int idx);

    void setName(string name) {
        this->name = name;
    }

    void setSeat(string newSeat) {
        seat = newSeat;
    }

    bool getEligibility() const {
        return loyaltyEligibility;
    }
};

// Reservation Class
class Reservation {
private:
    vector<Passenger*> passengers;
    vector<Flight*> flights;
    string seat;
    string specialRequest;
    //size_t is data type of integer, unassigned data type use for size and count
    int numPassengers;
    int numFlights;

public:
    Reservation(vector<Passenger*> passengers = {}, vector<Flight*> flights = {}, string seat = "")
        : passengers(passengers), flights(flights), seat(seat) {
        numPassengers = passengers.size();
        numFlights = flights.size();
    }

    Reservation(Flight* flight, string seat) : seat(seat) {
        flights.push_back(flight);
    }

    void changeSeat(string newSeat) {
        // Implement special request to change seat
        seat = newSeat;
    }

    // Getters
    vector<Passenger*>& getPassengers() {
        return passengers;
    }

    vector<Flight*>& getFlights() {
        return flights;
    }

    string getSeat() {
        return seat;
    }

    string getSpecialRequest() {
        return specialRequest;
    }

    size_t getNumPassengers() {
        return numPassengers;
    }

    size_t getNumFlights() {
        return numFlights;
    }

    // Setters
    void setPassengers(vector<Passenger*> newPassengers) {
        passengers = newPassengers;
        numPassengers = passengers.size();
    }

    void setFlights(vector<Flight*> newFlights) {
        flights = newFlights;
        numFlights = flights.size();
    }

    void setSeat(string newSeat) {
        seat = newSeat;
    }

    void setSpecialRequest(string newSpecialRequest) {
        specialRequest = newSpecialRequest;
    }
};

void Passenger::modifyReservation(int idx) {
    // Implement modification logic
    cout << "You have the option to modify which kind of seat you want to reserve.\n";
    int seatChoice;
    cout << "Please choose the seat type:\n";
    cout << "1. Economy\n";
    cout << "2. Business\n";
    cout << "3. FirstClass\n";
    cin >> seatChoice;
    while (cin.fail() || seatChoice < 1 || seatChoice > 3) {
        cout << "Please Enter a valid value: \n";
        cin >> seatChoice;
    }
    SeatType chosenSeatType;
    switch (seatChoice) {
    case 1:
        chosenSeatType = SeatType::Economy;
        break;
    case 2:
        chosenSeatType = SeatType::Business;
        break;
    case 3:
        chosenSeatType = SeatType::FirstClass;
        break;
    default:
        cout << "Invalid seat choice\n";
        break;
    }
    seat = convertSeatTypeToString(chosenSeatType);
    reservations[idx]->changeSeat(seat);
    cout << "Your Given Seat Type is Successfully Modified.\n";
}

// Crew class
class Crew {
private:
    string name;
    string role;
    vector<Flight*> flights;
    CrewState curr; // States of crew (Available or training)
    bool compliance; // Compliance with aviation regulations

public:
    Crew(string name, string role, CrewState curr, bool compliance)
        : name(name), role(role), curr(curr), compliance(compliance) {}

    // Getters
    string getName() const { return name; }
    string getRole() const { return role; }
    vector<Flight*> getFlights() const { return flights; }
    CrewState getState() const { return curr; }
    bool getCompliance() const { return compliance; }

    // Setters
    void setName(string name) { this->name = name; }
    void setRole(string role) { this->role = role; }
    void setFlights(vector<Flight*> flights) { this->flights = flights; }
    void setState(CrewState state) { this->curr = state; }
    void setCompliance(bool compliance) { this->compliance = compliance; }

    void assignFlight(Flight* flight) {
        flights.push_back(flight);
    }

    void removeFlight(Flight* flight) {
        // Implemented removal logic
    }

    void resolveScheduleConflict(Flight* flight, string newRoute) {
        // Resolved scheduling conflicts by changing the route of a flight
    }
};


// Implementation of FileHandler readData method
void FileHandler::readData(Airline& airline) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filePath << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string route, flightState, crewName, crewRole, crewComplianceStr, crewStateStr;
        getline(ss, route, ',');
        getline(ss, flightState, ',');
        getline(ss, crewName, ',');
        getline(ss, crewRole, ',');
        getline(ss, crewComplianceStr, ',');
        getline(ss, crewStateStr);

        bool crewCompliance = (crewComplianceStr == "1");
        CrewState crewState = (crewStateStr == "Available") ? CrewState::Available : CrewState::Training;

        FlightState* currentState;
        if (flightState == "Scheduled") {
            currentState = new ScheduledState();
        }
        else if (flightState == "Cancelled") {
            currentState = new CancelledState();
        }
        else if (flightState == "Delayed") {
            currentState = new DelayedState();
        }
        else {
            cerr << "Error: Invalid flight state encountered: " << flightState << endl;
            continue;
        }

        Flight* flight = new Flight(route);
        flight->setState(currentState);
        flight->setPrice(100 + rand() % 50);

        Crew* crew = new Crew(crewName, crewRole, crewState, crewCompliance);
        airline.addFlight(flight);
        airline.addCrew(crew);
    }

    file.close();
}

// Implementation of FileHandler updateData method
void FileHandler::updateData(string route, double basePrice, double demandFactor, double seasonalFactor, double eventFactor) {
    // Implement updating pricing factors in final_draft.csv
}

void Airline::assignCrewToFlight(Flight* flight, Crew* crew) {
    // Assign crew to the flight
    flight->getCrew().push_back(crew);
    removeCrew(crew);

}

int main() {
	//generate random numbers for time but current time for booking of flight 
    srand(time(0));

    cout << " ~*~*~*~*~*~*~* Welcome to Airline Reservation System Simulation *~*~*~*~*~*~*~\n";
    string a_name; // Airline name
    cout << "Enter the name for the Airline : ";
    getline(cin, a_name);

    PricingEngine price(1.2, 1, 1.3); // These are the hard coded factors

    // Create airline object
    Airline airline(a_name);
    // Initializing the reservation system
    Reservation reservations;

    // Load data using file handler
    //read data from file that is created in drive
    FileHandler fileHandler("final_draft.txt");
    fileHandler.readData(airline);


    // Menu to choose observer state
    cout << "\nChoose observer state:\n";
    cout << "1. Passenger Observer\n";
    cout << "2. Head Observer\n";
    int observerChoice;
    cin >> observerChoice;
    // cin.fail() Checks if the previous input operation failed (e.g., if the user entered a non-integer).
    while (cin.fail() || observerChoice < 1 || observerChoice > 2) {
        cout << "Please Enter a Valid Observer Type: ";
        cin >> observerChoice;
    }
    // Creating pointer observer object of base based on choice
    Observer* observer = nullptr;
    if (observerChoice == 1) {
    	// dynamically allocating the derived object address  to pointer object of parent observer
        observer = new PassengerObserver();
    }
    else if (observerChoice == 2) {
        observer = new CrewObserver();
        // Setting up time for each flight
        for (int i = 0; i < airline.getFlights().size(); i++) {
            string time = to_string((i + 1) % 12 + 1) + ((i % 24) < 13 ? " pm" : " am") + ", Day " + to_string(i / 10 + 1);
            airline.getFlights()[i]->setTime(time);
        }
    }
    else {
        cout << "Invalid choice\n";
        return 1;
    }

    bool Flag = 0; // for taking name of the passenger only once
    //bool Flag2 = 0; // For Checking if the passenger has any reservations
    Passenger newPassenger("");
    // Handling choices for functionalities
    int choice;
    do {
        cout << "\nChoose an option:\n";
        if (observerChoice == 1) {
            cout << "1. Book a flight\n";
            cout << "2. Cancel a reservation\n";
            cout << "3. Modify a reservation\n";
            cout << "4. Exit\n";
        }
        else if (observerChoice == 2) {
            cout << "1. Manage Crews to a flight\n"; // For adding and removing crews
            cout << "2. Handle schedule conflicts\n";
            cout << "3. Update flight status\n";
            cout << "4. Reroute a flight\n";
            cout << "5. Modify Flights \n"; // Adding and Removing
            cout << "6. Exit\n";
        }
        cin >> choice;
        int CrewNum;
        int flightNum;
        switch (choice) {
        case 1: {
            if (observerChoice == 1) {
                // Book a flight
                string passengerName;
                if (!Flag) {
                    cout << "Enter passenger name: ";

                    getline(cin >> ws, passengerName); // ws for white space
                }
                int seatChoice;
                cout << "Choose seat type:\n";
                cout << "1. Economy\n";
                cout << "2. Business\n";
                cout << "3. FirstClass\n";
                cin >> seatChoice;
                while (cin.fail() || seatChoice < 1 || seatChoice > 3) {
                    cout << "Please Enter a valid value: \n";
                    cin >> seatChoice;
                }
                SeatType chosenSeatType;
                switch (seatChoice) {
                case 1:
                    chosenSeatType = SeatType::Economy;
                    break;
                case 2:
                    chosenSeatType = SeatType::Business;
                    break;
                case 3:
                    chosenSeatType = SeatType::FirstClass;
                    break;
                default:
                    cout << "Invalid seat choice\n";
                    continue; // Go back to the main menu
                }
                string seat = convertSeatTypeToString(chosenSeatType);
                if (!Flag) {
                    newPassenger.setName(passengerName);
                    Flag = 1;
                }
                cout << "You have the following Avaiable flights : \n";
                for (int i = 0; i < airline.getFlights().size(); i++) {
                    string time = to_string((i + 1) % 12 + 1) + ((i % 24) < 13 ? " pm" : " am") + ", Day " + to_string(i / 10 + 1);
                    airline.getFlights()[i]->setTime(time);
                    if (airline.getFlights()[i]->getCurrentState()->status == "Scheduled") {
                        cout << " " << i + 1 << ": ~~~ " << airline.getFlights()[i]->getRoute() << ", Time : [ " << airline.getFlights()[i]->getTime() << " ]" << endl;
                    }
                    
                }
                int flightNum = 0;
                cout << "Enter the flight you want to take : ";
                cin >> flightNum;
                while (cin.fail() || flightNum < 1 || flightNum > 37 || airline.getFlights()[flightNum - 1]->getCurrentState()->status != "Scheduled") {
                    cout << "Please Enter a valid Flight Number : ";
                    cin >> flightNum;
                }

                newPassenger.getReservations().push_back(new Reservation(airline.getFlights()[flightNum - 1], seat));
                // Deleting OLD STATE
                delete airline.getFlights()[flightNum - 1]->getCurrentState();
                // Assigning New State
                airline.getFlights()[flightNum - 1]->setState(new CancelledState);
                //reservations.getFlights().push_back(new Flight());

                if (seat == "Business") airline.getFlights()[flightNum - 1]->setPrice(airline.getFlights()[flightNum - 1]->getPrice() + 40);
                else if(seat == "FirstClass") airline.getFlights()[flightNum - 1]->setPrice(airline.getFlights()[flightNum - 1]->getPrice() + 100);
                string loyalityCheck;
                cout << "Are you eligible for the loyality program? \n ";
                cin >> loyalityCheck;
                cout << "\nYou are successfully Registered in the Flight heading " << airline.getFlights()[flightNum - 1]->getRoute() << " \n";
                cout << "Regardless of your input , We have decided that you are " << (newPassenger.getEligibility() ? "" : "not ") << "eligible for the loyality Program.\n";
                cout << "\n\nConsidering All the Current Factors , Your final price comes out to be : " << price.calculatePrice(airline.getFlights()[flightNum - 1]->getPrice()) << "$ \n";
            }
            else if (observerChoice == 2) {
                // Assign crew to a flight
                cout << "Choose one of the following : \n";
                cout << "1. Add crew to Flight\n";
                cout << "2. Remove crew from Flight\n";
                int choice = 0;
                cin >> choice;
                while (cin.fail() || choice < 1 || choice > 2) {
                    cout << "Enter a Valid Option : ";
                    cin >> choice;
                }
                switch (choice) {
                case 1:
                    cout << "You have the following Flights Available: \n";
                    for (int i = 0; i < airline.getFlights().size(); i++) {
                        //string time = to_string((i + 1) % 12 + 1) + ((i % 24) < 13 ? " pm" : " am") + ", Day " + to_string(i / 10 + 1);
                        if (airline.getFlights()[i]->getCurrentState()->status == "Scheduled") {
                            cout << " " << i + 1 << ": ~~~ " << airline.getFlights()[i]->getRoute() << ", Time : [ " << airline.getFlights()[i]->getTime() << " ]" << endl;
                        }
                        //airline.getFlights()[i]->setTime(time);
                    }
                    
                    cout << "Enter the Flight number that you want to add the crew to : ";
                    cin >> flightNum;
                    while (cin.fail() || flightNum < 1 || flightNum > 37 || airline.getFlights()[flightNum - 1]->getCurrentState()->status != "Scheduled") {
                        cout << "Please Enter a valid Flight Number : ";
                        cin >> flightNum;
                    }
                    if (airline.getCrews().size()) {
                        cout << "You Currently have the following crew : \n";
                        for (int i = 0; i < airline.getCrews().size(); i++) {
                            cout << " " << i + 1 << ". " << airline.getCrews()[i]->getName() << " [ " << airline.getCrews()[i]->getRole() << " ] \n";
                        }
                    }
                    else cout << "No , Crew Available.\n";
                    cout << "Enter the Crew Number that you want to assign to the this Flight : ";
                    
                    cin >> CrewNum;
                    while (cin.fail() || CrewNum < 1 || CrewNum > airline.getCrews().size()) {
                        cout << "Enter a Valid Crew no. : ";
                        cin >> CrewNum;
                    }
                    if (airline.getCrews()[CrewNum - 1]->getCompliance()) {
                        airline.assignCrewToFlight(airline.getFlights()[flightNum - 1], airline.getCrews()[CrewNum - 1]);
                        cout << "Your Desired Crew is added to the desired Flight.\n";
                    }
                    else cout << " This Crew's compliance with aviation regulations is subpar.\n So, Please select another one next time.\n";
                    break;
                case 2:
                    cout << "You have the following Flights Available: \n";
                    for (int i = 0; i < airline.getFlights().size(); i++) {
                        //string time = to_string((i + 1) % 12 + 1) + ((i % 24) < 13 ? " pm" : " am") + ", Day " + to_string(i / 10 + 1);
                        if (airline.getFlights()[i]->getCurrentState()->status == "Scheduled") {
                            cout << " " << i + 1 << ": ~~~ " << airline.getFlights()[i]->getRoute() << ", Time : [ " << airline.getFlights()[i]->getTime() << " ]" << endl;
                        }
                        //airline.getFlights()[i]->setTime(time);
                    }
                    
                    cout << "Enter the Flight number that you want to remove the crew from : ";
                    cin >> flightNum;
                    while (cin.fail() || flightNum < 1 || flightNum > 37 || airline.getFlights()[flightNum - 1]->getCurrentState()->status != "Scheduled") {
                        cout << "Please Enter a valid Flight Number : ";
                        cin >> flightNum;
                    }
                    if (airline.getFlights()[flightNum-1]->getCrew().size()) {
                        cout << "You Currently have the following crew : \n";
                        for (int i = 0; i < airline.getFlights()[flightNum - 1]->getCrew().size(); i++) {
                            cout << " " << i + 1 << ". " << airline.getFlights()[flightNum - 1]->getCrew()[i]->getName() << " [ " << airline.getFlights()[flightNum - 1]->getCrew()[i]->getRole() << " ] \n";
                        }
                    }
                    else { 
                        cout << "No , Crew Available.\n"; 
                        break;
                    }
                    cout << "Enter the Crew Number that you want to remove from this flight : ";
                    
                    cin >> CrewNum;
                    while (cin.fail() || CrewNum < 1 || CrewNum > airline.getFlights()[flightNum - 1]->getCrew().size()) {
                        cout << "Enter a Valid Crew no. : ";
                        cin >> CrewNum;
                    }
                    airline.addCrew(airline.getFlights()[flightNum - 1]->getCrew()[CrewNum - 1]);
                    airline.getFlights()[flightNum - 1]->removeCrew(CrewNum-1);

                    cout << "Your Desired Crew has been successfully removed from the inteneded Flight .\n";
                    break;
                default:
                    cout << "This line is not supposed to print.\n";
                }
            }
            break;
        }
        case 2: {
            if (observerChoice == 1) {
                // Cancel a reservation
                // Implement cancellation logic
                int FlightNum = 0;
                if (newPassenger.getReservations().size()) {
                    cout << "Currently , you have the following Flights : \n";
                    for (int i = 0; i < newPassenger.getReservations().size(); i++) {
                        cout << " " << i + 1 << ". Heading " << newPassenger.getReservations()[i]->getFlights()[i]->getRoute() << "  [ " << newPassenger.getReservations()[i]->getSeat() << " ] , Time : " << "[ " << newPassenger.getReservations()[i]->getFlights()[i]->getTime() << " ]" << endl;
                    }
                    cout << "Enter the flight no. that you want to cancel : ";
                    cin >> FlightNum;
                    while (cin.fail() || FlightNum < 1 || FlightNum > newPassenger.getReservations().size()) {
                        cout << "Enter a Valid Flight no. : ";
                        cin >> FlightNum;
                    }
                    if (rand() % 2 == 1) {
                        cout << "Sorry , Your Cancellation Request can't be executed.\n";
                        cout << "Do you want to make a Special Request ? (yes/no)\n";
                        string ans;
                        getline(cin >> ws, ans);
                        while (ans != "yes" && ans != "no") {
                            cout << "Enter a valid Option: ";
                            getline(cin >> ws, ans);
                        }
                        if (ans == "no") {
                            cout << "Sure ! \n";
                            break;
                        }
                        string request;
                        cout << "Enter the request you want to give : \n";
                        getline(cin >> ws, request);
                        newPassenger.getReservations()[FlightNum - 1]->setSpecialRequest(request);
                        cout << "\nConsidering Your Special Request , we have made our decision.\n\n";
                    }
                    if (rand() % 2 == 1)
                        newPassenger.cancelReservation(FlightNum);
                    else cout << "You can't Cancel this flight.\n";
                }
                else cout << "You don't have any Reservations.\n";
            }
            else if (observerChoice == 2) {
                // Handle schedule conflicts
                static int DateCnt = 0;
                static int DayCnt = 0;
                cout << "You have the following Flights Available: \n";
                for (int i = 0; i < airline.getFlights().size(); i++) {
                    //string time = to_string((i + 1) % 12 + 1) + ((i % 24) < 13 ? " pm" : " am") + ", Day " + to_string(i / 10 + 1);
                    if (airline.getFlights()[i]->getCurrentState()->status == "Scheduled") {
                        cout << " " << i + 1 << ": ~~~ " << airline.getFlights()[i]->getRoute() << ", Time : [ " << airline.getFlights()[i]->getTime() << " ]" << endl;
                    }
                }

                cout << "Enter the Flight number that you want to change schedule of the crew to : ";
                cin >> flightNum;
                while (cin.fail() || flightNum < 1 || flightNum > 37 || airline.getFlights()[flightNum - 1]->getCurrentState()->status != "Scheduled") {
                    cout << "Please Enter a valid Flight Number : ";
                    cin >> flightNum;
                }
                cout << "The next possible Time that you can set for this flight is : \n";
                if (DateCnt / 24) DayCnt++;
                string newTime =  to_string((1 + DateCnt++) % 12) + (DateCnt % 24 < 13 ? "pm" : "am")  + ", Day " + to_string(10+DayCnt);
                cout << newTime << endl;
                cout << "Do you want to Modify the previous time (yes/no)? ";
                string timeopt;
                cin >> timeopt;
                while (timeopt != "yes" && timeopt != "no") {
                    cout << "Give a valid answer : ";
                    cin >> timeopt;
                }
                if (timeopt == "yes") {
                    airline.getFlights()[flightNum - 1]->setTime(newTime);
                }
                cout << "Your Request has been fulfilled.\n";
            }
            break;
        }
        case 3: {
            if (observerChoice == 1) {
                // Modify a reservation
                // Implement modification logic
                int FlightNum = 0;
                if (newPassenger.getReservations().size()) {
                    cout << "Currently , you have the following Flights : \n";
                    for (int i = 0; i < newPassenger.getReservations().size(); i++) {
                        cout << " " << i + 1 << ". Heading " << newPassenger.getReservations()[i]->getFlights()[i]->getRoute() << "  [ " << newPassenger.getReservations()[i]->getSeat() << " ] , Time : " << "[ " << newPassenger.getReservations()[i]->getFlights()[i]->getTime() << " ]" << endl;
                    }
                    cout << "Enter the flight no. that you want to Modify : ";
                    cin >> FlightNum;
                    while (cin.fail() || FlightNum < 1 || FlightNum > newPassenger.getReservations().size()) {
                        cout << "Enter a Valid Flight no. : ";
                        cin >> FlightNum;
                    }
                    if (rand() % 2 == 1) {
                        cout << "Sorry , Your Flight Modification Request can't be executed.\n";
                        cout << "Do you want to make a Special Request ? (yes/no)\n";
                        string ans;
                        getline(cin >> ws, ans);
                        while (ans != "yes" && ans != "no") {
                            cout << "Enter a valid Option: ";
                            getline(cin >> ws, ans);
                        }
                        if (ans == "no") {
                            cout << "Sure ! \n";
                            break;
                        }
                        string request;
                        cout << "Enter the request you want to give : \n";
                        getline(cin >> ws, request);
                        newPassenger.getReservations()[FlightNum - 1]->setSpecialRequest(request);
                        cout << "\nConsidering Your Special Request , we have made our decision.\n\n";
                    }
                    newPassenger.modifyReservation(FlightNum - 1);
                }
                else cout << "You don't have any Reservations.\n";
            }
            else if (observerChoice == 2) {
                // Update flight status
                cout << "You have the following Flights Available: \n";
                for (int i = 0; i < airline.getFlights().size(); i++) {
                    //string time = to_string((i + 1) % 12 + 1) + ((i % 24) < 13 ? " pm" : " am") + ", Day " + to_string(i / 10 + 1);
                    //if (airline.getFlights()[i]->getCurrentState()->status == "Scheduled") {
                    cout << " " << i + 1 << ": ~~~ " << airline.getFlights()[i]->getRoute() << ", Time : [ " << airline.getFlights()[i]->getTime() << " ]" << endl;
                    //}
                }
                cout << "Select the one that you want to update the state of : \n";
                cin >> flightNum;
                while (cin.fail() || flightNum < 1 || flightNum > airline.getFlights().size()) {
                    cout << "Please Enter a valid Flight Number : ";
                    cin >> flightNum;
                }
                cout << "The Current State of the given flight is : " << airline.getFlights()[flightNum - 1]->getState()->status << ". \n";
                cout << "Select any of the following Choices that you want the state to update to: \n";
                cout << "1. Scheduled \n2. Delayed \n3.Cancelled\n";
                int StChoice;
                cin >> StChoice;
                while (cin.fail() || StChoice < 1 || StChoice > 3) {
                    cout << "Enter a valid Choice : ";
                    cin >> StChoice;
                }
                switch (StChoice) {
                case 1:
                    delete airline.getFlights()[flightNum - 1]->getState();
                    airline.getFlights()[flightNum - 1]->getState() = new ScheduledState();
                    airline.getFlights()[flightNum - 1]->getState()->updateStatus("Scheduled");
                    break;
                case 2:
                    delete airline.getFlights()[flightNum - 1]->getState();
                    airline.getFlights()[flightNum - 1]->getState() = new DelayedState();
                    airline.getFlights()[flightNum - 1]->getState()->updateStatus("Delayed");
                    break;
                case 3:
                    delete airline.getFlights()[flightNum - 1]->getState();
                    airline.getFlights()[flightNum - 1]->getState() = new CancelledState();
                    airline.getFlights()[flightNum - 1]->getState()->updateStatus("Cancelled");
                    break;
                default:
                    cout << "This line is not supposed to print.\n";
                }
                cout << "Your Required State has been set Successfully.\n";
            }
            break;
        }
        case 4: {
            if (observerChoice == 1) {
                // No action for Passenger Observer
                cout << "Exiting...\n";
                break;
            }
            else if (observerChoice == 2) {
                // Reroute a flight
                cout << "You have the following Flights Available: \n";
                for (int i = 0; i < airline.getFlights().size(); i++) {
                    //string time = to_string((i + 1) % 12 + 1) + ((i % 24) < 13 ? " pm" : " am") + ", Day " + to_string(i / 10 + 1);
                    if (airline.getFlights()[i]->getCurrentState()->status == "Scheduled") {
                        cout << " " << i + 1 << ": ~~~ " << airline.getFlights()[i]->getRoute() << ", Time : [ " << airline.getFlights()[i]->getTime() << " ]" << endl;
                    }
                }
                cout << "Enter the Flight number that you want to Reroute : ";
                cin >> flightNum;
                while (cin.fail() || flightNum < 1 || flightNum > 37 || airline.getFlights()[flightNum - 1]->getCurrentState()->status != "Scheduled") {
                    cout << "Please Enter a valid Flight Number : ";
                    cin >> flightNum;
                }
                cout << "Enter the Route you want it to follow : \n";
                string newRoute;
                cin >> newRoute;
                airline.getFlights()[flightNum - 1]->setRoute(newRoute);
                cout << "Your desired Flight has been rerouted successfully.\n";
            }
            break;
        }
        case 5: {
            // Logic To Add/Remove Flights
            if (observerChoice == 2) {
                cout << "Select one of the following options: \n";
                cout << "1. Add Flight\n"
                    << "2. Remove Flight\n";
                int flChoice;
                cin >> flChoice;
                while (cin.fail() || flChoice < 1 || flChoice > 2) {
                    cout << "Choose a Valid Option: ";
                    cin >> flChoice;
                }
                if (flChoice == 1) {
                    cout << "Enter the route for the new Flight.\n";
                    string newRoute;
                    cin >> newRoute;
                    cout << "Now select any of the following times : \n"
                        << "1. 10 pm , Day 7\n2. 11 am ,Day 8\n3. 6 pm , Day 8\n4. 9 pm , Day 8\n";
                    int timeChoice;
                    cin >> timeChoice;
                    while (cin.fail() || timeChoice < 1 || timeChoice > 4) {
                        cout << "Enter a Valid Option: ";
                        cin >> timeChoice;
                    }
                    string newtime;
                    switch (timeChoice) {
                    case 1:
                        newtime = "10 pm , Day 7";
                        break;
                    case 2:
                        newtime = "11 am ,Day 8";
                        break;
                    case 3:
                        newtime = "6 pm , Day 8";
                        break;
                    case 4:
                        newtime = "9 pm , Day 8";
                        break;
                    }
                    Flight* newFlight = new Flight(newRoute,newtime);
                    airline.addFlight(newFlight);
                    cout << "Your Desired Flight has been added successfully.\n";
                }
                else {
                    cout << "You have the following Flights Available: \n";
                    for (int i = 0; i < airline.getFlights().size(); i++) {
                        //string time = to_string((i + 1) % 12 + 1) + ((i % 24) < 13 ? " pm" : " am") + ", Day " + to_string(i / 10 + 1);
                        //if (airline.getFlights()[i]->getCurrentState()->status == "Scheduled") {
                            cout << " " << i + 1 << ": ~~~ " << airline.getFlights()[i]->getRoute() << ", Time : [ " << airline.getFlights()[i]->getTime() << " ]" << endl;
                        //}
                    }

                    cout << "Enter the Flight number that you want to remove : ";
                    cin >> flightNum;
                    while (cin.fail() || flightNum < 1 || flightNum > airline.getFlights().size()) {
                        cout << "Please Enter a valid Flight Number : ";
                        cin >> flightNum;
                    }
               //     airline.removeFlight(airline.getFlights()[flightNum - 1]);
                    cout << "Your intended Flight has been removed successfully.\n";
                }
            }
            break;
        }
        case 6: {
            if (observerChoice == 2) {
                cout << "Exiting...\n";
                break;
            }
        }
        default:
            cout << "\nInvalid choice. Please Enter Again: ";
        }
    } while ((choice != 6 && observerChoice == 2) || (choice != 4 && observerChoice == 1));
    delete observer;
    return 0;
}
