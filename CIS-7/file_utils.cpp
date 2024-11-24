#include "file_utils.h"
#include <fstream>
#include <cstdlib>
#include <iostream>

void saveHashedMessageToFile(const std::string& hashedMessage) {
    std::string documentsDir;
    char* envValue = nullptr;

#ifdef _WIN32
    // Use _dupenv_s for safer environment variable retrieval
    size_t len;
    if (_dupenv_s(&envValue, &len, "USERPROFILE") == 0 && envValue != nullptr) {
        documentsDir = std::string(envValue) + "\\Documents";
        free(envValue);  // Don't forget to free the allocated memory
    }
#else
    // Use getenv on non-Windows systems
    const char* homeDir = getenv("HOME");
    if (homeDir != nullptr) {
        documentsDir = std::string(homeDir) + "/Documents";
    }
#endif

    if (documentsDir.empty()) {
        std::cerr << "Error: Unable to locate the Documents directory." << std::endl;
        return;
    }

    // Define the file path
    std::string filePath = documentsDir + "/hashed_message.txt";

    // Save the file
    std::ofstream file(filePath);
    if (file.is_open()) {
        file << hashedMessage;
        file.close();
        std::cout << "Hashed encrypted message saved to: " << filePath << std::endl;
    }
    else {
        std::cerr << "Error: Unable to write to file in Documents directory." << std::endl;
    }
}
