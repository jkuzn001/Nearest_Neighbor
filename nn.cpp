#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <set>
using namespace std;

//node struct to store the data points

struct node {
    double type;                  //class of data point
    vector<double> features;      //vector holding the value of each feature
};

node nearestNeighbor(node n, vector<node> points, vector<int> feats) {
    node bestsofar;         //closest node so far
    double mindist = 0;     // distance to best so far
    for(int i = 0; i < points.size(); ++i) {
        double temp = 0;    //variable used to calculate distance
        for(int j = 0; j < feats.size(); ++j) {
            //test only the features that we are trying in feature select
            double num = n.features.at(feats.at(j)) - points.at(i).features.at(feats.at(j));
            temp += pow(num, 2);
        }
        temp = sqrt(temp);
        if(temp < mindist || mindist == 0) { 
            mindist = temp;
            bestsofar = points.at(i);
        }
    }
    return bestsofar;
}

//helper function to move an element from the back of a vector to the front
void backToFront(vector<node> &points) {
    for(int i = points.size() - 1; i > 0; --i) {
        node temp = points.at(i);
        points.at(i) = points.at(i - 1);
        points.at(i - 1) = temp;
    }
}

//function to test the feature set using leave one out cross validation
double leaveOne(vector<node> points, vector<int> feats) {
    int succ = 0;
    for(int i = 0; i < points.size(); ++i) {
        node temp = points.at(points.size() - 1);
        points.pop_back();
        if(temp.type == nearestNeighbor(temp, points, feats).type) {
            ++succ;
        }
        points.push_back(temp);
        backToFront(points);
    }
    return (double) succ / points.size();
}

void forwardSelect(vector<node> points) {
    vector<int> curr;
    vector<int> best;
    double bestAcc = 0;
    int numfeatures = points.at(0).features.size();
    set<int> currset;
    for(int i = 0; i < numfeatures; ++i) {
        cout << "On the " << i + 1 << "th level of the search tree" << endl;
        int featToAdd;
        double bestSoFarAcc = 0;
        for(int j = 0; j < numfeatures; ++j) {
            if(currset.find(j) == currset.end()) {
                cout << "--Considering adding feature " << j + 1 << endl;
                vector<int> totry = curr;
                totry.push_back(j);
                double acc = leaveOne(points, totry);
                if(acc > bestSoFarAcc) {
                    bestSoFarAcc = acc;
                    featToAdd = j;
                }
            }
        }
        cout << "Added feature " << featToAdd + 1 << " with accuracy " << bestSoFarAcc << endl;
        curr.push_back(featToAdd);
        currset.insert(featToAdd);
        if(bestSoFarAcc > bestAcc) {
            bestAcc = bestSoFarAcc;
            best = curr;
        }
    }
    cout << "Final feature set: ";
    for(int i = 0; i < best.size(); ++i) {
        cout << best.at(i) + 1 << " ";
    }
    cout << endl << "Accuracy " << bestAcc << endl;
}

void backwardSelect(vector<node> points) {
    vector<int> curr;
    vector<int> best;
    double bestAcc = 0;
    int numfeatures = points.at(0).features.size();
    set<int> currset;
    //populate the current feature set with all of the features
    for(int i = 0; i < numfeatures; ++i) {
        curr.push_back(i);
        currset.insert(i);
    }
    for(int i = 0; i < numfeatures; ++i) {
        cout << "On the " << i + 1 << "th level of the search tree" << endl;
        int featToRem = 0;
        double bestSoFarAcc = 0;
        for(int j = 0; j < curr.size(); ++j) {
            if(currset.find(j) != currset.end()) {
              cout << "Considering removing feature " << j + 1 << endl;
              vector<int> totry = curr;
              totry.erase(totry.begin() + j);
              double acc = leaveOne(points, totry);
              if(acc > bestSoFarAcc) {
                  bestSoFarAcc = acc;
                  featToRem = j;
              }
            }
        }
        cout << "Removed feature " << featToRem + 1 << " with accuracy " << bestSoFarAcc << endl;
        curr.erase(curr.begin() + featToRem);
        currset.erase(featToRem);
        if(bestSoFarAcc > bestAcc) {
            bestAcc = bestSoFarAcc;
            best = curr;
        }
    }
    cout << "Final Feature set: ";
    for(int i = 0; i < best.size(); ++i) {
        cout << best.at(i) + 1 << " ";
    }
    cout << endl << "Accuracy " << bestAcc << endl;
}

//like foward select but takes the top 2 features 
void customSelect(vector<node>points) {
    
}
int main(int argc, char** argv) {
    vector<node> points;
    ifstream fin;
    fin.open(argv[1]);
    string data;                  //string to hold the current data point  
    //read in the data
    while(getline(fin, data)) {
        node temp;
        stringstream ss(data);
        double feat;
        ss >> feat;               //first number is always class  
        temp.type = feat;
        while(ss >> feat) {
            temp.features.push_back(feat);
        }
        points.push_back(temp);
    }
    fin.close();
    //normalize the data
    for(int i = 0; i < points.at(0).features.size(); ++i) {
        //calculate mean
        double mean = 0;
        for(int j = 0; j < points.size(); ++j) {
            mean += points.at(j).features.at(i);
        }
        mean /= (double) points.size();
        //calculate standard deviation
        double stddev = 0;
        for(int j = 0; j < points.size(); ++j) {
            stddev += pow((points.at(j).features.at(i) - mean), 2);
        }
        stddev /= (double) points.size();
        //assign z values to features
        for(int j = 0; j < points.size(); ++j) {
            points.at(j).features.at(i) = ((points.at(j).features.at(i) - mean) / stddev);
        }
    }
    cout << "Welcome to Jacob Kuznicki's Feature Selection Algorithm." << endl;
    cout << "Type the number of the algorithm you want to run." << endl;
    cout << "1) Forward Select" << endl;
    cout << "2) Backward Elimination" << endl;
    cout << "3) Custom Selection Algorithm" << endl;
    int input;
    cin >> input;
    cout << "The dataset has " << points.at(0).features.size() << " features (not inlcuding the class attribute), with " << points.size() << " instances." << endl;
    cout << "Data has been normalized beginning search" << endl;
}
