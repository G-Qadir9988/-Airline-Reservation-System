#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
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

//make code easy to maintain  and less complex
//return normal numbers
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
class PricingEngine {
private:
    double seasonalFactor;
    double eventFactor;
    double demandFactor;

public:
    PricingEngine(double sf = 1, double ef = 1, double df = 1) : seasonalFactor(sf), eventFactor(ef), demandFactor(df) {}

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
    void updateStatus(string status) override {
        this->status = "Scheduled";
    }
};

// CancelledState concrete state
class CancelledState : public FlightState {
public:
    void updateStatus(string status) override {
        this->status = "Cancelled";
    }
};

// DelayedState concrete state
class DelayedState : public FlightState {
public:
    void updateStatus(string status) override {
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
    // No more vectors for flights, crews, and passengers
public:
    Airline(string name) : name(name) {}

    // Getter for name
    string getName() const {
        return name;
    }

    // No more getters for flights, crews, and passengers

    void addFlight(Flight* flight) {
        // No more vectors to push_back
    }

    void addCrew(Crew* crew) {
        // No more vectors to push_back
    }

    void removeCrew(Crew* crew) {
        // No more vectors to remove
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
    // No more vector for passengers and crew
    FlightState* currentState;
    string time;

public:
    Flight(string route, string time = "1 am ,Day 1", int price = 100) : route(route), time(time), price(price) {
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

    void setTime(string newTime) {
        time = newTime;
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
    // No more vector for reservations
    bool loyaltyEligibility;
    string seat;

public:
    Passenger(string name) : name(name), loyaltyEligibility(rand() % 2) {}

    void bookFlight(Flight* flight, string seat) {
        // Implemented
    }

    void cancelReservation(int idx) {
        // No more vectors to remove reservation
        cout << "Your Desired Reservation has been successfully removed.\n";
    }

    // No more getter for reservations

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
    // No more vectors for passengers and flights
    string seat;
    string specialRequest;
    int numPassengers;
    int numFlights;

public:
    Reservation(vector<Passenger*> passengers = {}, vector<Flight*> flights = {}, string seat = "")
        : seat(seat) {
        numPassengers = passengers.size();
        numFlights = flights.size();
    }

    Reservation(Flight* flight, string seat) : seat(seat) {
        // No more vectors to push_back flight
    }

    void changeSeat(string newSeat) {
        // Implement special request to change seat
        seat = newSeat;
    }

    // Getters
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
    void setSeat(string newSeat) {
        seat = newSeat;
    }

    void setSpecialRequest(string newSpecialRequest) {
        specialRequest = newSpecialRequest;
    }
};

void Passenger::modifyReservation(int idx) {
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
    // Implement modification of seat in reservation
    cout << "Your Given Seat Type is Successfully Modified.\n";
}

// Crew class
class Crew {
private:
    string name;
    string role;
    // No more vector for flights
    CrewState curr; // States of crew (Available or training)
    bool compliance; // Compliance with aviation regulations

public:
    Crew(string name, string role, CrewState curr, bool compliance)
        : name(name), role(role), curr(curr), compliance(compliance) {}

    // Getters
    string getName() const { return name; }
    string getRole() const { return role; }
    // No more getter for flights
    CrewState getState() const { return curr; }
    bool getCompliance() const { return compliance; }

    // Setters
    void setName(string name) { this->name = name; }
    void setRole(string role) { this->role = role; }
    // No more setter for flights
    void setState(CrewState state) { this->curr = state; }
    void setCompliance(bool compliance) { this->compliance = compliance; }

    void assignFlight(Flight* flight) {
        // No more vector to push_back flight
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
    // No more vector to push_back crew
}

int main() {
    // Your main program logic here
    return 0;
}
int main() {
    // Generate random numbers for time but current time for booking of flight 
    srand(time(0));

    cout << " ~*~*~*~*~*~*~* Welcome to Airline Reservation System Simulation *~*~*~*~*~*~*~\n";
    string a_name; // Airline name
    cout << "Enter the name for the Airline : ";
    getline(cin, a_name);

    PricingEngine price(1.2, 1, 1.3); // These are the hard coded factors

    // Create airline object
    Airline airline(a_name);

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
        // dynamically allocating the derived object address to pointer object of parent observer
        observer = new PassengerObserver();
    }
    else if (observerChoice == 2) {
        observer = new CrewObserver();
        // Setting up time for each flight
        for (int i = 0; i < airline.getFlightCount(); i++) {
            string time = to_string((i + 1) % 12 + 1) + ((i % 24) < 13 ? " pm" : " am") + ", Day " + to_string(i / 10 + 1);
            airline.getFlight(i)->setTime(time);
        }
    }
    else {
        cout << "Invalid choice\n";
        return 1;
    }

    bool Flag = 0; // for taking name of the passenger only once
    Passenger newPassenger("");
    // Handling choices for functionalities
    int choice;
    do {
        // Menu options
        // Based on observer choice, different options will be displayed
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

        // Switch case based on user's choice
        switch (choice) {
            // Cases for each functionality option
        }
    } while ((choice != 6 && observerChoice == 2) || (choice != 4 && observerChoice == 1));
    delete observer; // Freeing memory
    return 0;
}
