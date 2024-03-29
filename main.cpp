#include <iostream>
#include <unordered_map>

// Initialize data structures for tracking available tickets, passengers, and earnings
std::unordered_map<std::string, int> available_tickets = {
    {"09:00_up", 6 * 80},
    {"11:00_up", 6 * 80},
    {"13:00_up", 6 * 80},
    {"15:00_up", 6 * 80},
    {"10:00_down", 6 * 80},
    {"12:00_down", 6 * 80},
    {"14:00_down", 6 * 80},
    {"16:00_down", 6 * 80 + 2 * 80}  // Extra coaches on the last train down
};

std::unordered_map<std::string, int> passengers_count = {
    {"09:00_up", 0},
    {"11:00_up", 0},
    {"13:00_up", 0},
    {"15:00_up", 0},
    {"10:00_down", 0},
    {"12:00_down", 0},
    {"14:00_down", 0},
    {"16:00_down", 0}
};

std::unordered_map<std::string, int> earnings = passengers_count;

// Function prototypes
void displayScreen();
std::string purchaseTickets(std::string journey, int num_tickets);
void endOfDaySummary();

// Task 1 - Start of the day
void displayScreen() {
    std::cout << "Train Schedule & Available Tickets" << std::endl;
    for (const auto &ticket : available_tickets) {
        if (ticket.second > 0) {
            std::cout << ticket.first << ": " << ticket.second << " tickets available" << std::endl;
        } else {
            std::cout << ticket.first << ": Closed" << std::endl;
        }
    }
}

// Task 2 - Purchasing tickets
std::string purchaseTickets(std::string journey, int num_tickets) {
    if (available_tickets[journey] >= num_tickets) {
        available_tickets[journey] -= num_tickets;
        int price = num_tickets * 25;
        if (num_tickets >= 10 && num_tickets <= 80) {
            int free_tickets = num_tickets / 10;
            price -= free_tickets * 25;
        }
        earnings[journey] += price;
        passengers_count[journey] += num_tickets;
        return "Tickets purchased successfully.";
    } else {
        return "Not enough tickets available for this journey.";
    }
}

// Task 3 - End of the day
void endOfDaySummary() {
    int total_passengers = 0;
    int total_earnings = 0;

    std::cout << "\nEnd of the day summary:" << std::endl;
    for (const auto &passenger : passengers_count) {
        std::cout << passenger.first << ": " << passenger.second << " passengers, Total earnings: $" << earnings[passenger.first] << std::endl;
        total_passengers += passenger.second;
        total_earnings += earnings[passenger.first];
    }

    std::cout << "\nTotal Passengers for the day: " << total_passengers << std::endl;
    std::cout << "Total Earnings for the day: $" << total_earnings << std::endl;

    std::string max_passengers_journey;
    int max_passengers = 0;
    for (const auto &passenger : passengers_count) {
        if (passenger.second > max_passengers) {
            max_passengers = passenger.second;
            max_passengers_journey = passenger.first;
        }
    }
    std::cout << "Journey with the most passengers: " << max_passengers_journey << " - " << max_passengers << " passengers" << std::endl;
}

int main() {
    displayScreen();

    // Test purchasing tickets
    std::cout << purchaseTickets("09:00_up", 5) << std::endl;
    std::cout << purchaseTickets("09:00_up", 15) << std::endl;
    std::cout << purchaseTickets("09:00_up", 25) << std::endl;

    // Test end of the day summary
    endOfDaySummary();

    return 0;
}
