#ifndef CONSTANTS_H
#define CONSTANTS_H

//const int kDiagramD = 2 ;
//const int kDiagramEdge = 100 ;

enum kRunningState{
    kRunning,
    kPausing,
    kStopping
};

const double kPlotSize = 250 ;
const double kPointSize = 3 ;
const double kSensorSize = 6.0 ;
const double kSqrt = 1.414 ;

enum kMOEA{
    kNSGA2,
    kMOEAD
};

enum kDisplay{

    kBestCoverage,
    kBestNodes,
    kBestEnergy
};


#endif // CONSTANTS_H
