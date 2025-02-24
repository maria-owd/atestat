#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

ifstream f("dive-log.csv");

/**
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

void citire() {
    vector<DiveLog> diveLogs;
    string line;
    
    // Skip the header line
    getline(f, line);
    
    while (getline(f, line)) {
        stringstream ss(line);
        DiveLog log;
        string depth, duration;
        
        getline(ss, log.date, ',');
        getline(ss, log.location, ',');
        getline(ss, depth, ',');
        getline(ss, duration, ',');
        
        log.depth = stoi(depth);
        log.duration = stoi(duration);
        
        diveLogs.push_back(log);
    }
    
    // Print the dive logs to verify
    for (const auto& log : diveLogs) {
        cout << "Date: " << log.date << ", Location: " << log.location
             << ", Depth: " << log.depth << "m, Duration: " << log.duration << "min" << endl;
    }
}

int main() {
    citire();
    return 0;
}
