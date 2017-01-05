#include<cuda_runtime_api.h>
#include"timeInterval.h"

// this class is intended to compute the time spent between two reference points.
// the computation is started by calling the following method
void Interval::startInterval(){
	cudaEventRecord (start, 0);
}

// the following method finishs the timer and computes the interval length
void Interval::endInterval(){
	cudaEventRecord (end,   0);
	cudaEventSynchronize ( end );
	cudaEventElapsedTime ( &elapsedTime, start, end);
}

// return the interval length
float Interval::getTime(){
	return elapsedTime/1000;
}

// constructor , initializing variables
Interval::Interval(){
	cudaEventCreate( &start );
	cudaEventCreate( &end   );
	elapsedTime = 0;
}

// cleaning variables from memory
Interval::~Interval(){
	cudaEventDestroy( start );
	cudaEventDestroy( end   );
}
