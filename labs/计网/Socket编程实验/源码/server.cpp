#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;

const int BUFFER_SIZE = 1024;

struct ServerConfig {
    string address;
    int port;
    string rootPath;
};

bool checkDirectoryExist(const std::string& directoryPath) {
    std::ifstream file(directoryPath);
    return file.good();
}

bool readConfig(const string& configFile, ServerConfig& config) {
    ifstream file(configFile);
    if (!file) {
        cout << "Failed to open config file: " << configFile << endl;
        return false;
    }
    string line;
    while (getline(file, line)) {
        size_t delimiterPos = line.find('=');
        if (delimiterPos != string::npos) {
            string key = line.substr(0, delimiterPos);
            string value = line.substr(delimiterPos + 1);

            if (key == "ADDRESS") {
                config.address = value;
            } else if (key == "PORT") {
                config.port = stoi(value);
            } else if (key == "ROOT_PATH") {
                config.rootPath = value;
            }
        }
    }
    file.close();

    if (!checkDirectoryExist(config.rootPath)) {
        std::cerr << "Config root directory not found: " << config.rootPath << std::endl;
        std::exit(1);
    }

    return true;
}

const char* getFileType(const char* fileName) {
    const char* dot = strrchr(fileName, '.');
    if (!dot) return "application/octet-stream";
    if (strcmp(dot, ".html") == 0) return "text/html";
    if (strcmp(dot, ".jpg") == 0) return "image/jpeg";
    if (strcmp(dot, ".png") == 0) return "image/png";
    if (strcmp(dot, ".gif") == 0) return "image/gif";
    if (strcmp(dot, ".mp4") == 0) return "video/mp4";
    return "application/octet-stream";
};

void handleClientRequest(int clientSocket, const char* rootPath) {
    char requestData[BUFFER_SIZE] = {'\0'};
    int bytesRead = recv(clientSocket, requestData, BUFFER_SIZE, 0);
    if (bytesRead < 0) {
        cout << "Failed to receive request data!" << endl;
        close(clientSocket);
        return;
    }

    cout << "Received request: " << requestData << endl;

    // Parse the request to get the file name
    char fileName[100] = {'\0'};
    sscanf(requestData, "GET /%s", fileName);

    // Construct the full file path
    char filePath[200];
    sprintf(filePath, "%s/%s", rootPath, fileName);

    // Send the requested file to the client
    FILE* file = fopen(filePath, "rb");
    if (file == nullptr) {
        cout << "Failed to open file: " << filePath << endl;
        const char* response404 = "HTTP/1.1 404 Not Found\r\n\r\n";
        send(clientSocket, response404, strlen(response404), 0);
        // Load the custom error page
        string errorPagePath = string(rootPath) + "/404.html";
        ifstream errorPageFile(errorPagePath);
        string errorPageContent((istreambuf_iterator<char>(errorPageFile)),
                                istreambuf_iterator<char>());
        errorPageFile.close();

        // Send the custom error page to the client
        send(clientSocket, errorPageContent.c_str(), errorPageContent.size(), 0);
        close(clientSocket);
        return;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // construct http response header
    char responseHeader[200];
    sprintf(responseHeader, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %ld\r\n\r\n",
            getFileType(filePath), filesize);

    // send http response header
    if (send(clientSocket, responseHeader, strlen(responseHeader), 0) < 0) {
        cout << "Failed to send response header!" << endl;
        fclose(file);
        return;
    }

    char buffer[BUFFER_SIZE];
    size_t bytesReadFromFile;
    while ((bytesReadFromFile = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        if (send(clientSocket, buffer, bytesReadFromFile, 0) < 0) {
            cout << "Failed to send file!" << endl;
            break;
        }
    }

    fclose(file);
    close(clientSocket);
}

int main() {
    ServerConfig config;
    if (!readConfig("config.ini", config)) {
        return 1;
    }

    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        cout << "Failed to create socket!" << endl;
        return 1;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(config.port);
    serverAddr.sin_addr.s_addr = inet_addr(config.address.c_str());

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cout << "Failed to bind socket!" << endl;
        perror("");
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) < 0) {
        cout << "Failed to listen for connections!" << endl;
        return -1;
    }

    cout << "Server started. Listening on " << config.address << ":" << config.port << "..."
         << endl;

    while (true) {
        struct sockaddr_in clientAddr;
        socklen_t addrLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
        if (clientSocket < 0) {
            cout << "Accept failed!" << endl;
            continue;
        }

        pid_t pid = fork();
        if (pid < 0) {
            cout << "Failed to create child process!" << endl;
            close(clientSocket);
            continue;
        } else if (pid == 0) {
            // Child process
            close(serverSocket);
            handleClientRequest(clientSocket,
                                config.rootPath.c_str());  // Replace with your actual root path
            exit(0);
        } else {
            // Parent process
            close(clientSocket);
        }
    }

    close(serverSocket);
    return 0;
}