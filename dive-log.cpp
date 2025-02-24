#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

ifstream f("dive-log.csv");

/**
  @struct DiveLog
 * @brief A structure to store information about a dive.
 * 
 * @var DiveLog::date
 * The date of the dive in string format.
 * 
 * @var DiveLog::location
 * The location where the dive took place.
 * 
 * @var DiveLog::depth
 * The depth of the dive in meters.
 * 
 * @var DiveLog::duration
 * The duration of the dive in minutes.
 */
struct DiveLog {
    char date[20];
    char location[50];
    int depth;
    int duration;
};

const int MAX_DIVES = 100; // Maximum number of dives
const int MAX_LINE = 1000; // Maximum number of characters in a line

void parseLine(const char* line, DiveLog& log) {
    char* cstr = new char[strlen(line) + 1];
    strcpy(cstr, line);
    
    char* token = strtok(cstr, ",");
    strcpy(log.date, token);
    
    token = strtok(NULL, ",");
    strcpy(log.location, token);
    
    token = strtok(NULL, ",");
    log.depth = atoi(token);
    
    token = strtok(NULL, ",");
    log.duration = atoi(token);
    
    delete[] cstr;
}

void citire() {
    DiveLog diveLogs[MAX_DIVES];
    int count = 0;
    char line[MAX_LINE];
    
    // Skip the header line
    f.getline(line, MAX_LINE);
    
    while (f.getline(line, MAX_LINE) && count < MAX_DIVES) {
        parseLine(line, diveLogs[count++]);
    }
    
    // Print the dive logs to verify
    for (int i = 0; i < count; ++i) {
        cout << "Date: " << diveLogs[i].date << ", Location: " << diveLogs[i].location
             << ", Depth: " << diveLogs[i].depth << "m, Duration: " << diveLogs[i].duration << "min" << endl;
    }
}

int main() {
    citire();
    return 0;
}
