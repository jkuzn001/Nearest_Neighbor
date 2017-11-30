#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
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
            double num = n.features.at(j) - points.at(i).features.at(feats.at(j));
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
    vector<int> bestSoFar;
    double acc;
    int ones = 0;
    for(int i = 0; i < points.size(); ++i) {
        if(points.at(i).type == 1) {
            ++ones;
        }
    }
    if(ones > (points.size() / 2)) {
        acc = (double) ones / points.size();
    }
    else {
        acc = (double) (points.size() - ones) / points.size();
    }
    vector<int> curr;
    for(int i = 0; i < points.at(0).features.size(); ++i) {
        curr.push_back(i);
        if(leaveOne(points, curr) > acc) {
            
        }
    }
}

void backwardSelect(vector<node> points) {

}

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
}
