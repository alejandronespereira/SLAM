
#include <iostream>

#include <locale.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


#include "opencv2/opencv.hpp"
//#include "../thirdparty/tum_reader/src/BenchmarkDatasetReader.h"
#include "frameProvider.hpp"

int main( int argc, char** argv )
{
  setlocale(LC_ALL, "C");
  std::string dataset = argv[1];

  FrameProvider* provider = new FrameProvider(dataset);




}
