#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <chrono>
#include <thread>
#include "file_utils.h"  // Include the header for the file saving function

using namespace std;

// Function prototypes
string getUserInput(const string& prompt, bool allowSpaces = true);  // Keep the default argument here
string vigenereEncrypt(const string& message, const string& key);
string hashMessage(const string& message);
void displayMenu();
int getChoice();
bool getYesOrNo(const string& prompt);
void clearScreen(); // Function to clear the terminal screen after a delay

const string DEFAULT_KEY = "defaultkey"; // Hardcoded default key for encryption

int main() {
    while (true) {
        displayMenu(); // Show menu to the user
        int choice = getChoice();

        switch (choice) {
        case 1: { // Encrypt a message
            string message = getUserInput("Enter the message to encrypt (can include spaces): ");
            string encryptedMessage = vigenereEncrypt(message, DEFAULT_KEY);
            cout << "Encrypted Message: " << encryptedMessage << endl;

            // Ask if the user wants to save the hashed message
            if (getYesOrNo("Do you want to save the hashed encrypted message to a file? (y/n): ")) {
                string hashedMessage = hashMessage(encryptedMessage);
                saveHashedMessageToFile(hashedMessage); // Call the function from file_utils.cpp
            }

            // Delay for 5 seconds before clearing the screen
            clearScreen();

            break;
        }
        case 2: { // Exit the program
            cout << "Exiting program..." << endl;
            return 0;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    }
}

// Display menu to the user
void displayMenu() {
    cout << "----- Vigenere Cipher Program -----" << endl;
    cout << "1. Encrypt a message" << endl;
    cout << "2. Exit" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Enter your choice: ";
}

// Get the user's choice from the menu
int getChoice() {
    int choice;
    cin >> choice;
    cin.ignore(); // Clear input buffer
    return choice;
}

// Prompt the user for input and return it
string getUserInput(const string& prompt, bool allowSpaces) { // No default argument in the definition
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (!allowSpaces && input.find(' ') != string::npos) {
            cout << "Input not valid. Try again." << endl;
            continue;
        }
        if (!input.empty()) break; // Accept non-empty input
        cout << "Input not valid. Try again." << endl;
    }
    return input;
}

// Encrypt the message using the Vigenere Cipher with a predefined key
string vigenereEncrypt(const string& message, const string& key) {
    string encryptedMessage = "";
    for (size_t i = 0, j = 0; i < message.length(); i++) {
        if (isalpha(message[i])) {
            char offset = isupper(message[i]) ? 'A' : 'a';
            encryptedMessage += (message[i] + (key[j % key.length()] - offset) - offset) % 26 + offset;
            j++;
        }
        else {
            encryptedMessage += message[i]; // Preserve non-alphabetic characters
        }
    }
    return encryptedMessage;
}

// Simple placeholder for hashing the message
string hashMessage(const string& message) {
    size_t hash = 0;
    for (char ch : message) {
        hash = (hash * 31 + ch) % 1000000007; // Simple hash computation
    }
    return to_string(hash);
}

// Ask a yes/no question and return true for 'yes' and false for 'no'
bool getYesOrNo(const string& prompt) {
    char response;
    while (true) {
        cout << prompt;
        cin >> response;
        cin.ignore(); // Clear input buffer
        response = tolower(response);
        if (response == 'y') return true;
        if (response == 'n') return false;
        cout << "Input not valid. Try again." << endl;
    }
}

// Function to clear the terminal screen after a delay
void clearScreen() {
    // Delay for 5 seconds before clearing the screen
    cout << "Waiting for 5 seconds before clearing the screen..." << endl;
    this_thread::sleep_for(chrono::seconds(5));

    // Check the OS and run the appropriate command
#if defined(_WIN32) || defined(_WIN64)
    system("CLS");
#else
    system("clear");
#endif
}
