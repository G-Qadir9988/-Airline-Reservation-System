# ✈️ Airline Reservation System

## 🌟 Overview

A comprehensive **console-based Airline Reservation System** implemented in **C++** using **Object-Oriented Programming (OOP)** principles and software design patterns such as **State**, **Observer**, and **Facade**.  
This project simulates real-world airline operations including:

- Flight booking  
- Crew management  
- Flight scheduling  
- Pricing dynamics  
- Reservation handling

---

## 👨‍💻 Team Members

| Name           | Role           |
|----------------|----------------|
| Ghulam Qadir   | C++ Developer  |
| Muqeem Ahmed   | C++ Developer  |
| Ahmed Raza     | C++ Developer  |

---

## 🚀 Features

- **✈️ Flight Booking**  
  Passengers can book, modify, and cancel flights with different seat types.

- **🧑‍✈️ Crew Management**  
  Admins can assign/remove crew to/from flights with role and compliance verification.

- **🕒 Flight Scheduling**  
  Update flight times and resolve scheduling conflicts.

- **🔁 Flight State Updates**  
  Modify status as Scheduled, Cancelled, or Delayed using the **State Pattern**.

- **🎯 Pricing Engine**  
  Dynamic pricing based on seasonal, event, and demand factors.

- **🧾 Reservation System**  
  Maintain reservations with seat types and special requests.

- **🔄 Observer Pattern**  
  Support for **PassengerObserver** and **CrewObserver** functionalities.

- **🗃️ File Handler (Facade Pattern)**  
  Load crew and flight data from external files.

---

## 🛠️ Technologies Used

- **Language:** C++
- **Paradigm:** Object-Oriented Programming (OOP)
- **Design Patterns:** State, Observer, Facade
- **File I/O:** `fstream`, `ifstream`, `ofstream`
- **Standard Library:** `vector`, `string`, `sstream`, `ctime`

---

## 📂 Project Structure

AirlineReservationSystem/
│
├── main.cpp # Entry point and interface logic
├── Airline/ # Airline class: handles crew, flights, passengers
├── Flight/ # Flight class with state and scheduling
├── Passenger/ # Manages reservations and loyalty
├── Crew/ # Manages crew details and assignments
├── Reservation/ # Handles seat and flight details
├── FileHandler/ # Facade for reading/writing external data
├── PricingEngine/ # Calculates price with multiple factors
├── ObserverPattern/ # Implements Passenger and Crew Observers
└── FlightState/ # Implements Scheduled, Cancelled, Delayed States


---

## 🧪 How It Works

- On launch, the user selects their role:
  - **Passenger** – Can book, cancel, or modify a flight.
  - **Crew/Admin** – Can manage flights, crew, reroute, and update flight statuses.

- **Data is dynamically loaded** via the FileHandler.
- **Seat types** (Economy, Business, FirstClass) affect pricing.
- **Flight status** is managed through the **State Pattern**.
- **Crew compliance** and **roles are verified** before assignment.
- **Random factors** like loyalty and cancellation simulate real-world behavior.

---

## ✅ Functional Modules

| Module         | Description                                      |
|----------------|--------------------------------------------------|
| Flight         | Represents individual flight with state, crew    |
| Passenger      | Manages user info, booking, and cancellations    |
| Crew           | Role, state, compliance, scheduling              |
| Reservation    | Links passengers and flights with seat info      |
| PricingEngine  | Dynamically calculates ticket prices             |
| FileHandler    | Reads and updates flight/crew data               |
| FlightState    | States: Scheduled, Delayed, Cancelled            |
| Observer       | Observers react to actions (not implemented)     |

---

## 🔍 Sample Functional Flow

Welcome to Airline Reservation System

Enter your name for Airline: SkyWings

Choose Observer:

Passenger Observer

Crew/Admin Observer

Crew Observer Selected

[Manage Crew]

Add/Remove Crew

Handle Conflict

Update Status

Reroute Flight

Add/Remove Flights


---

## 📜 License

This project is open-source and available for **educational and academic use** under the **MIT License**.

---

## 📧 Contact

**Ghulam Qadir**  
- Email: [gqitspecialist@gmail.com](mailto:gqitspecialist@gmail.com)  
- LinkedIn: [Ghulam Qadir](https://www.linkedin.com/in/ghulam-qadir-07a982365)


