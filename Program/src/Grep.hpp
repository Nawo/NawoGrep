#pragma once

#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <queue>
#include <regex>
#include <stack>
#include <string>
#include <thread>

#include "FindedFiles.hpp"

class Grep {
private:
    // START PROGRAM VARIABLES
    int searchedFiles = 0;
    int filesWithPattern = 0;
    int patternsNumber = 0;
    int numberOfThreads = 4;

    std::string pattern;
    std::string startSearchDirection = ".";
    std::string logFile = "NawoGrep";
    std::string resultFile = "NawoGrep";

    // PARSE FILES VARIABLES
    int lineNumber = 1;
    int inFilePatternsNumber = 0;
    bool find = false;

    // CONTAINERS
    std::deque<std::filesystem::directory_entry*> filesToParse;
    std::deque<FindedFiles*> findedFiles;

    std::mutex queueMutex;
    std::mutex findedFilesMutex;
    std::vector<std::thread> threads;

    std::multimap<std::thread::id, std::string> toLogFile;
    std::map<std::thread::id, int> threadFileCount;
    std::vector<std::pair<std::thread::id, int>> sortedThreads;

    // TIME VARIABLES
    std::chrono::time_point<std::chrono::system_clock> startProgramTime;
    std::chrono::time_point<std::chrono::system_clock> endProgramTime;

    // FUNCTIONS
    void parseArguments(const int& argc, char* argv[]);
    void getStartTime();
    void searchFiles();
    void processFilesInQueue();
    void parseFiles();
    void saveToResultFile();
    void saveToLogFile();
    void getEndTime();
    void printVariables();

public:
    Grep() = delete;
    Grep(const int& argc, char* argv[]);

    ~Grep() = default;

    void run();
};