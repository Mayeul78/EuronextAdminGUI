//
// Created by Mayeul Boucher on 13/12/2024.
//
#include <iostream>
#include "APIManager.h"

int main() {
    APIManager apiManager("http://localhost:18080");

    std::string response = apiManager.get("/ping");
    std::cout << "\n\nTesting ping: " << std::endl;
    std::cout << response << std::endl;

    // Test with invalid credentials
    std::cout << "\n\nTesting login function with Invalid Username and Password:" << std::endl;
    if (!apiManager.login("admin", "wrongpassword")) {
        std::cout << "Login test passed: Invalid credentials." << std::endl;
    } else {
        std::cerr << "Login test failed: Invalid credentials." << std::endl;
    }

    std::cout << "\nTesting Secure Endpoint with Invalid Token:" << std::endl;
    if (apiManager.secure()) {
        std::cout << "Secure test failed: Valid token with invalid credentials." << std::endl;
    } else {
        std::cout << "Secure test passed: Invalid token correctly detected." << std::endl;
    }

    // Test with valid credentials
    std::cout << "\n\nTesting login function with Valid Username and Password:" << std::endl;
    if (apiManager.login("admin", "admin123")) {
        std::cout << "Login test passed: Valid credentials." << std::endl;
    } else {
        std::cerr << "Login test failed: Valid credentials." << std::endl;
        return 1; // Stop testing if login fails
    }

    std::cout << "\nTesting Secure Endpoint with Valid Token:" << std::endl;
    if (apiManager.secure()) {
        std::cout << "Secure test passed: Valid token." << std::endl;
    } else {
        std::cerr << "Secure test failed: Valid token." << std::endl;
    }

    // Retrieve and display instruments
    std::cout << "\nTesting GET Instruments:" << std::endl;
    std::vector<std::unordered_map<std::string, std::string>> instruments = apiManager.getInstruments();
    for (const auto& instrument : instruments) {
        std::cout << "\nInstrument:" << std::endl;
        for (const auto& [key, val] : instrument) {
            std::cout << "   -" << key << " : " << val << std::endl;
        }
    }

    // Add a new instrument
    std::cout << "\n\nTesting Add Instrument:" << std::endl;
    std::string newISIN = "US1234567890";
    std::string newMIC = "XNYS";
    std::string newCurrency = "USD";
    std::string newStatus = "active";

    if (apiManager.addInstrument(newISIN, newMIC, newCurrency, newStatus)) {
        std::cout << "Add Instrument test passed: Instrument added successfully." << std::endl;
    } else {
        std::cerr << "Add Instrument test failed: Could not add instrument." << std::endl;
    }

    // Modify an existing instrument
    std::cout << "\n\nTesting Modify Instrument (Update Currency):" << std::endl;
    std::string updatedCurrency = "EUR";

    if (apiManager.modifyInstrument(newISIN, "currency", "ABB","bOB")) {
        std::cout << "Modify Instrument test passed: Instrument updated successfully." << std::endl;
    } else {
        std::cerr << "Modify Instrument test failed: Could not update instrument." << std::endl;
    }

    // Retrieve and display instruments again to verify changes
    std::cout << "\nTesting GET Instruments After Add/Modify:" << std::endl;
    instruments = apiManager.getInstruments();
    for (const auto& instrument : instruments) {
        std::cout << "\nInstrument:" << std::endl;
        for (const auto& [key, val] : instrument) {
            std::cout << "   -" << key << " : " << val << std::endl;
        }
    }

    // Perform the deletion of an instrument
    std::cout << "\nAttempting to delete instrument with ISIN: " << newISIN << std::endl;
    if (apiManager.dellInstrument(newISIN)) {
        std::cout << "Instrument with ISIN " << newISIN << " deleted successfully.\n";
    } else {
        std::cerr << "Failed to delete instrument with ISIN " << newISIN << ".\n";
    }

    return 0;
}
