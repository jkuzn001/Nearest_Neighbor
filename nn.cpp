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

node nearestNeighbor(node n, vector<node> points) {
    node bestsofar;         //closest node so far
    double mindist = 0;     // distance to best so far
    for(int i = 0; i < points.size(); ++i) {
        double temp = 0;    //variable used to calculate distance
        for(int j = 0; j < points.at(i).features.size(); ++j) {
            double num = n.features.at(j) - points.at(i).features.at(j);
            temp += pow(num, 2.0);
        }
        temp = sqrt(temp);
        if(temp < mindist || mindist == 0) { 
            mindist = temp;
            bestsofar = points.at(i);
        }
    }
    return bestsofar;
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
    node temp = points.at(points.size() - 1);
    points.pop_back();
    temp = nearestNeighbor(temp,points);
    cout << temp.type;
}
