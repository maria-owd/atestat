#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

ifstream f("dive-log.csv");

/**
 * @brief 
 * 
 * @struct DiveLog
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
    string date;
    string location;
    int depth;
    int duration;
};

const int MAX_DIVES = 100; // Maximum number of dives

void citire() {
    DiveLog diveLogs[MAX_DIVES];
    int count = 0;
    string line;
    
    // Skip the header line
    getline(f, line);
    
    while (getline(f, line) && count < MAX_DIVES) {
        stringstream ss(line);
        DiveLog log;
        string depth, duration;
        
        getline(ss, log.date, ',');
        getline(ss, log.location, ',');
        getline(ss, depth, ',');
        getline(ss, duration, ',');
        
        log.depth = stoi(depth);
        log.duration = stoi(duration);
        
        diveLogs[count++] = log;
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
