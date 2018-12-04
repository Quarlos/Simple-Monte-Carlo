//
//  SimpleMCMain1.cpp
//  Created by carlos on 26/10/2018.
//
//  Simple routine for pricing European call options (non-dividend) using Monte Carlo simulation
//
//  requires Random1.cpp

//#include "SimpleMCMain1.hpp"

#include "Random1.hpp"
#include <iostream>
#include <cmath>
using namespace std;

double SimpleMonteCarlo1(double Expiry,
                         double Strike,
                         double Spot,
                         double Vol,
                         double r,
                         unsigned long NumberOfPaths)

{
    double variance = Vol*Vol*Expiry;
    double rootVariance = sqrt(variance);
    double itoCorrection = -0.5*variance;
    
    double movedSpot = Spot*exp(r*Expiry + itoCorrection);
    double thisSpot;
    double runningSum=0;
    
    for (unsigned long i=0; i < NumberOfPaths; i++)
    {
        double thisGaussian = GetOneGaussianByBoxMuller();
        thisSpot = movedSpot*exp(rootVariance*thisGaussian);
        double thisPayoff = thisSpot - Strike;
        thisPayoff = thisPayoff >0 ? thisPayoff : 0;
        runningSum += thisPayoff;
    }
    
    double mean = runningSum / NumberOfPaths;
    mean *= exp(-r*Expiry);
    return mean;
}


int main()
{
    double Expiry;
    double Strike;
    double Spot;
    double Vol;
    double r;
    unsigned long NumberOfPaths;
    
    cout << "Enter expiry T: ";
    cin >> Expiry;
    
    cout << "Enter strike K: ";
    cin >> Strike;
    
    cout << "Enter spot S_0: ";
    cin >> Spot;
    
    cout << "Enter volatility: ";
    cin >> Vol;
    
    cout << "Enter risk-free interest rate r: ";
    cin >> r;
    
    cout << "Number of paths (iterations): ";
    cin >> NumberOfPaths;
    
    double result = SimpleMonteCarlo1(Expiry,
                                      Strike,
                                      Spot,
                                      Vol,
                                      r,
                                      NumberOfPaths);
    
    cout << "\nThe price is: " << result << endl;
    cout << endl;
    
    return 0;
}
