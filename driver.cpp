#include <istream>
#include <iostream>
#include <fstream>
#include "Eigen/Dense"
#include "Eigen/Eigenvalues"


using namespace std;

float calcCov(Eigen::VectorXf x, Eigen::VectorXf y){
    float tot = 0;
    float xMean = x.mean();
    float yMean = y.mean();
    for(int i = 0; i<x.rows(); i++){
        tot = tot + (x(i)-xMean) * (y(i) - yMean);
    }
    return tot / (x.rows()-1);


}
int main(int argc, char *argv[]){

    ifstream inFile;

    inFile.open("2018-AvgRainfall_mm.csv");
    if(!inFile){
        cout << "Unable to open" << endl;
        exit(1);
    }
    string noEle;
    getline(inFile, noEle);
    string noComp;
    getline(inFile, noComp);
    const int noComponents = stoi(noComp);
    


    const int noElements = stoi(noEle);
    

    string strArray[noElements];

    for(int i =0; i<noElements; i++){
        string temp;
        getline(inFile, temp);
        strArray[i]=temp;
    }

    float june[noElements];
    float july[noElements];

    Eigen::VectorXf compOne(noElements);
    Eigen::VectorXf compTwo(noElements);

    for(int i = 0; i<noElements; i++){
        float juneStr = stof(strArray[i].substr(4,4));
        float julyStr = stof(strArray[i].substr(9,4));
        june[i] = juneStr;
        july[i] = julyStr;

    }

    for(int y = 0; y<noElements; y++){
            compOne[y] = june[y];
            compTwo[y] = july[y];
    }

    float covX = calcCov(compOne, compOne);
    float covY = calcCov(compTwo, compTwo);
    float covXY = calcCov(compOne, compTwo);
    float covYX = calcCov(compTwo, compOne);

    Eigen::Matrix<float, 2, 2> covMat;
    covMat<< covX, covXY, covYX, covY;
    

    float totalVar = covX + covY;

    float propOne = (154.311/totalVar)*100;
    float propTwo = (9.16296/totalVar)*100;

    Eigen::EigenSolver<Eigen::Matrix<float,2,2> > solve(covMat);
    

    ofstream myFile;
    myFile.open("output.txt");

    myFile << "1. EigenValues: " << endl;
    myFile << solve.eigenvalues() << endl;
    myFile << "2. EigenVectors: " << endl;
    myFile << solve.eigenvectors() << endl;
    myFile << "3. Covariance matrix: " << endl;
    myFile << covMat << endl;
    myFile << "4. Total variance: " << totalVar << endl;
    myFile << "5. Proportion Component 1: " << propOne << " Proportion Component 2: " << propTwo;       
    
    myFile.close();




}