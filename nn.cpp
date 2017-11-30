#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

//node struct to store the data points

struct node {
    double type;                  //class of data point
    int numFeatures = 10;         //number of features given 10 for small data set 50 for big
    double features[numFeatures]; //array holding the value of each feature
};

int main(int argc, char** argv) {
    vector<node> points;
    ifstream fin;
    fin.open(argv[1]);
    string data;                  //string to hold the current data point  
    while(!fin.eof()){
        getline(fin, data);
        node temp;
        stringstream ss;
        ss.str(data);
        double feat;
        ss >> feat;
        temp.type = feat;
        while(ss >> feat) {
            temp.features
        }
    }
}
