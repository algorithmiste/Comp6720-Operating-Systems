//
// Created by casey on 4/15/2019.
//

//#include <iterator> // ostream_iterator and istream_iterator //istream_iterator< int > inputInt( cin ); int number1 = *inputInt; // read int from standard input
//++inputInt; // move iterator to next input value // int number2 = *inputInt; // read int from standard input

//If the string is not found, the value string::npos (a public static constant defined in class string) is returned.
// rfind (search from right of string
// size_t position = string1.find( " " ); // find first space

#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <cstddef> // header for size_t which is the type of array subscripts
#include <fstream> // contains file stream processing types
#include <cstdlib> // exit function prototype
//#include <stdlib.h> not good idea to use C standards in C++
#include <vector>
#include <deque>
#include <iterator>
using namespace std;

#include <utility> // pair, make_pair
#include <map>
#include <algorithm>
#include <sstream> // for stringstream converter between

static void checkSafe(deque< vector<int> >, deque< vector<int> > , deque<int> );
static deque<int> getResourceRequest();
static void makeResourceRequest(deque< vector<int> >, deque< vector<int> > , deque<int>,
                                deque< vector<int> >, deque< vector<int> > , deque<int>,
                                deque<int>);
static deque< vector<int> > updateNeedVector(deque< vector<int> > need, deque< int > request); // for requesting process
static deque< vector<int> > updateAllocationVector(deque< vector<int> > allocation, deque< int > request); // for requesting process
static deque< int > updateAvailableVector(deque<int> available, deque<int> request);

deque< vector<int> > allocationRequest;
static vector<pair<int, int>> orderAllocatedResources(deque< vector<int> >);
bool notGranted; // global bool variable for makeRequest and PART 3
static bool tryAgain;
static bool stop;
deque<int> processToTerminate;
deque<int> request;
deque<int> availableRequest;
unsigned int recoveryBit = 1;
bool canModifyNeed; // set to true when we can proceed with banker's algorithm
bool canModifyAvailable;
deque<int> tempRequest;
unsigned int iteration;
int main() {

    string fileName;

    cout << "Enter the data file path (e.g. C:\\Users\\casey\\Desktop\\Prog3_Comp6270\\sys_config.txt) : " << endl;
    cin >> fileName;

//    ifstream constructor opens the file
    ifstream dataFile(fileName, ios::in);

    // exit program if ifstream could not open the file
    if (!dataFile) {
        cerr << "File could not be opened!" << endl;
        exit(EXIT_FAILURE);
    }

    string str;
    deque< vector<int> > allocation;
    deque< vector<int> > max;
    deque<int> available;
    // Fill ALLOCATION, MAX, and AVAILABLE data structures
    do {
        getline(dataFile, str);
        size_t lenStr = str.size();
        size_t position;
        size_t lenStrRemain;

        if (str.substr(0, lenStr) == "Allocation") {
            getline(dataFile, str);
            lenStr = str.size();
            position = str.find(':', 0);
            lenStrRemain = lenStr - position - 1;
            while(str.substr(0, lenStr) != "Max") {

                vector<int> vectorToPush;
                int position = str.find(':', 0);
                string pResources = str.substr(position+2, lenStrRemain);
                stringstream check1(pResources);
                string intermediate;
                // Tokenizing w.r.t. space ' '
                while(getline(check1, intermediate, ' ')) {
                    stringstream ss1;
                    int toInt;
                    ss1 << intermediate;
                    ss1 >> toInt;

                    vectorToPush.push_back(toInt);
                }
                allocation.push_back(vectorToPush);

                getline(dataFile, str);
                position = str.find(':', 0);
                lenStr = str.size();
                lenStrRemain = lenStr - position - 1;
            }
        }
        lenStr = str.size();
        if (str.substr(0, lenStr) == "Max") {

            getline(dataFile, str);
            while(str.substr(0, str.size()) != "Available") {
                position = str.find(':', 0);
                lenStr = str.size();
                lenStrRemain = lenStr - (position) - 1;
                vector<int> vectorToPush;
                string pResources = str.substr(position+2, lenStrRemain);
                stringstream check1(pResources);
                string intermediate;
                // Tokenizing w.r.t. space ' '
                while(getline(check1, intermediate, ' ')) {
                    stringstream ss1;
                    int toInt;
                    ss1 << intermediate;
                    ss1 >> toInt;

                    vectorToPush.push_back(toInt);
                }
                max.push_back(vectorToPush);
                getline(dataFile, str);
            }
        }
        lenStr = str.size();
        if (str.substr(0, str.size()) == "Available") {
            getline(dataFile, str);

            stringstream check1(str);
            string intermediate;
            // Tokenizing w.r.t. space ' '
            while(getline(check1, intermediate, ' ')) {
                stringstream ss1;
                int toInt;
                ss1 << intermediate;
                ss1 >> toInt;

                available.push_back(toInt);
            }
        }
    } while (!dataFile.eof());

    deque< vector<int> > need;
    deque<int> work = available;
    need = max;
    // Fill in NEED vector
    for (size_t i = 0; i < max.size(); ++i) {
        for (size_t j = 0; j < max[j].size(); ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    // Check for an ordering of the Pi's given the initial work = available
    int size = need.size(); // size represents number of processes
    checkSafe(allocation, need, work);

//    // Part 2: Take a ‘Request’ vector as user input and print out either ‘GRANTED’ or ‘NOT
//    //GRANTED’ to indicate whether the resource request can be granted or not.

    request = getResourceRequest();
    deque<vector<int>> needRequest = updateNeedVector(need, request);
    availableRequest = updateAvailableVector(available, request);
    allocationRequest = updateAllocationVector(allocation, request);

    makeResourceRequest(allocation, need, available,
                        allocationRequest, needRequest, availableRequest,
                        request); // false indicates NOT GRANTED !!

// PART 3: Identify the minimum number of processes that should be forced to be terminated
    // such that the requested resources can be granted.
    // So if request Not Granted compute the number of resources allocated, Ri,  to each Pi (excluding P0),
    // and find the minimum, or
    // even better order the Pi in terms of increasing Ri
    // In increasing order of the Ri, allocate the next Min Ri to Available, until the request is Granted!

    if (notGranted) { //

        vector<pair<int, int>> allocationOrdered = orderAllocatedResources(allocationRequest);

        // tryAgain means add additional allocated resources from next Min Ri
        // needRequest, allocationRequest, availableRequest have been UPDATED
        // allocationOrdered Ready to go

        vector<int> safeState2(size); // size represents number of processes
        vector<bool> isSafe2(size);
        int ordering2 = 1;

        for (int w = 0; w < work.size(); ++w) {// NEED work back in INITIAL STATE
            work[w] = available[w] - tempRequest[w];
        }
        size_t index = 0; // index of a given process (not including P0)
        bool finished;
        while (!stop && tryAgain && (index < allocationOrdered.size())) {
            size_t process = allocationOrdered[index].first;
            int counter2 = 0;

            for (int p = 0; p < work.size(); ++p) {
                work[p] += allocationRequest[process][p];
                allocationRequest[process][p] = 0;
            }
            processToTerminate.push_back(process);

            int res;
            for (int val = 0; val < request.size(); ++val) {
                res = work[val] - tempRequest[val];
                if ( (res < 0) ) {
                    finished = false;
                }
                if ((val == request.size()-1) && (res >= 0)) {
                    finished = true;
                    int ptt = processToTerminate.size();
                    cout << "To grant the requested resources, ";
                    cout << "we must terminate the following processes: ";
                    int c;
                    if (ptt == 1) {
                        cout << processToTerminate[0] << endl;
                    } else {
                        for (c = 0; c < ptt - 1; ++c) {
                            cout << processToTerminate[c] << ", ";
                        }
                        cout << processToTerminate[ptt - 1] << endl;
                    }
                    return 0;
                }
                else if ((process == allocationOrdered.size()-1) && (val == request.size()-1) && (res < 0)) {
                    cerr << "Still can\'t grant the request after terminating all other processes" << endl;
                    exit(EXIT_FAILURE);
                }
            }

            if (!finished) {
                makeResourceRequest(allocation, need, available,
                                    allocationRequest, needRequest, availableRequest,
                                    request); // changed availableRequest -> work
                ++index;
            }
        }
        notGranted = true;
    }

    return 0;
}

static void checkSafe(deque< vector<int> > allocation, deque< vector<int> > need, deque<int> work) {
    int size = need.size();
    vector<int> safeState1(size);
    vector<bool> isSafe1(size);
    int ordering1 = 1;
    int counter1;
    while ( (ordering1 <= size) ||  (counter1 < size*size)) {
        for (size_t i = 0; i < size; ++i) {
            if ( !isSafe1[i] ) {
                for (size_t j = 0; j < need[j].size(); ++j) {

                    int result = work[j] - need[i][j];
                    if ( result < 0) { // in this case we try another Pi
                        safeState1[i] = 0;
                        break;
                    }
                    if (j == need[j].size() - 1) {isSafe1[i] = true;}
                }
                if (isSafe1[i]) {
                    for (int k = 0; k < work.size(); ++k) {
                        work[k] += allocation[i][k];
                    }
                    safeState1[i] = ordering1;
                    isSafe1[i] = true;
                    ++ordering1;
                }
            }
        }
        ++counter1;
    }
    int where1 = 0;
    for (bool b : isSafe1) {
        if (b == false) {
            cout << "\nUNSAFE\n" << endl;
            exit(EXIT_FAILURE);
        }
        if (where1 == isSafe1.size()-1) {
            cout << "\nSAFE\n" << endl;
        }
        ++where1;
    }
}
static void makeResourceRequest(deque< vector<int> > allocation, deque< vector<int> > need, deque<int> available,
        deque< vector<int> > allocationRequest, deque< vector<int> > needRequest, deque<int> availableRequest,
        deque<int> request) {
    size_t size = need.size();
    deque<int> work;
    deque< vector<int> > tempNeed; // create temp vectors for resetting initial state
    tempNeed = need;
    deque<int> tempAvailable; // create temp vectors for resetting initial state
    tempAvailable = available;
    deque< vector<int> > tempAllocation; // create temp vectors for resetting initial state
    tempAllocation = allocation;

    bool valid = true;
    unsigned int run = 1;
    iteration = 1;
    do {
        if (request.size() != available.size()) {
            cout << "Wrong Input!" << endl;
            break;
        }
        if (recoveryBit == 1) {
            if (iteration == 1) {
                work = availableRequest;
            } else {
                needRequest = updateNeedVector(need, request);
                availableRequest = updateAvailableVector(available, request);
                allocationRequest = updateAllocationVector(allocation, request);
                work = availableRequest;
            }
        } else {work = availableRequest;}

        vector<int> safeState2(size); // size represents number of processes
        vector<bool> isSafe2(size);
        int ordering2 = 1;
        int counter2 = 0;
        bool found;
        while ((ordering2 <= size) && (counter2 < size * size)) {

            for (size_t i = 0; i < size; ++i) {

                if (!isSafe2[i]) {
                    for (size_t j = 0; j < needRequest[j].size(); ++j) {

                        int result = work[j] - needRequest[i][j];
                        if (result < 0) { // in this case we try another Pi
                            safeState2[i] = 0;
                            break;
                        } else {found = true;}
                        if (j == needRequest[j].size() - 1) { isSafe2[i] = true; }
                    }
                    if (isSafe2[i]) {
                        for (int k = 0; k < work.size(); ++k) {
                            work[k] += allocationRequest[i][k];
                        }
                        safeState2[i] = ordering2;
                        isSafe2[i] = true;
                        ++ordering2;
                    }
                }
            }
            ++counter2;
        }
        int where2 = 0;
        for (bool b : isSafe2) {
            if (b == false) {
                if (recoveryBit == 1) {
                    cout << "\nNOT GRANTED\n" << endl;
                }
                valid = false;
                notGranted = true;
                stop = false;
                tryAgain = true;
                ++recoveryBit;
                tempRequest = request;
                break;
            }
            if (where2 == isSafe2.size()-1) {
                stop = true;
                tryAgain = false;

                if (recoveryBit == 1) { // while "Granted" continue
                    cout << "\nGRANTED\n" << endl;
                    request.clear();
                    ++iteration;
                    notGranted = false;
                    valid = true;
                }
                else {
                    valid = false;
                }
            }
            ++where2;
        }
        if (valid) {
            cout << "Request vector: " << endl;
            string buffer;
            getline(cin, buffer);
            stringstream check1(buffer);
            string intermediate;
            // Tokenizing w.r.t. space ' '
            while(getline(check1, intermediate, ' ')) {
                stringstream ss1;
                int toInt;
                ss1 << intermediate;
                ss1 >> toInt;

                request.push_back(toInt);
            }
            tempRequest = request;
        }
    } while(valid);

}
static deque< vector<int> > updateNeedVector(deque< vector<int> > need, deque< int > request) { // for requesting process
    // update need vector for requestingProcess
    deque<vector<int>> needRequest = need; //tempNeed
    for (int j = 0; j < need[j].size(); ++j) {
        if ((needRequest[0][j] - request[j]) < 0) {
            canModifyNeed = false;
            for (int k = j; k >= 0; --k) {
                needRequest[0][k] += request[k];
            } // add back requested resources starting from j going backwards
            cerr << "Requested resources has exceeded maximum claim!";
            exit(EXIT_FAILURE);
        } else {
            canModifyNeed = true;
            needRequest[0][j] -= request[j];
        }
    }
    return needRequest;
}
static deque< vector<int> > updateAllocationVector(deque< vector<int> > allocation, deque<int> request){ // for requesting process
    deque<vector<int>> allocationRequest = allocation; //tempAllocation;
    if (canModifyNeed && canModifyAvailable) {
        for (int j = 0; j < allocation[j].size(); ++j) {
            allocationRequest[0][j] += request[j];
        }
    }
    return allocationRequest;
}
static deque< int > updateAvailableVector(deque<int> available, deque<int> request) { // for requesting process
    deque<int> availableRequest = available; //tempNeed;
    if (canModifyNeed) {
        for (int j = 0; j < available.size(); ++j) {
            if ((availableRequest[j] - request[j]) < 0) {
                canModifyAvailable = false;
                for (int k = j; k >= 0; --k) {
                    availableRequest[k] += request[k];
                } // add back requested resources starting from j going backwards
                break;
            }
            else {
                canModifyAvailable = true;
                availableRequest[j] -= request[j];
            }
        }
    }
    return availableRequest;
}
static deque<int> getResourceRequest() {

    string buffer;
    deque<int> request;
    cout << "Request vector: " << endl;

    for (int i = 0; i < 2; ++i) {
        getline(cin, buffer);
    }
    stringstream check1(buffer);
    string intermediate;
    // Tokenizing w.r.t. space ' '
    while(getline(check1, intermediate, ' ')) {
        stringstream ss1;
        int toInt;
        ss1 << intermediate;
        ss1 >> toInt;
        request.push_back(toInt);
    }
    return request;
}
static vector<pair<int, int>> orderAllocatedResources(deque< vector<int> > allocationRequest) {
    map<int,int> allocationToOrder; // in this case i = 0 indicates process P1

    for (int i = 1; i < allocationRequest.size(); ++i) {
        int total = 0;
        for (int j = 0; j < allocationRequest[i].size(); ++j) {
            total += allocationRequest[i][j];
        }
        allocationToOrder.insert({i, total});
    }
    // create a empty vector of pairs
    vector<pair<int, int>> allocationOrdered;
    for (int m = 1; m <= allocationToOrder.size(); ++m) {
        auto var = allocationToOrder.find(m);
        int val = var->second;
        allocationOrdered.emplace_back(m, val);
    }
    // sort the vector by increasing order of its pair's second value
    // if second value are equal, order by the pair's first value
    std::sort(allocationOrdered.begin(), allocationOrdered.end(),
              [](const pair<int, int>& l, const pair<int, int>& r) {
                  if (l.second != r.second)
                      return l.second < r.second;

                  return l.first < r.first;
              });
    return allocationOrdered;
}