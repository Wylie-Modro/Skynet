/*
 *  Auvsi_Ocr.h
 *  OpenCV21btest
 *
 *  Created by Lewis Anderson on 6/5/10.
 *  Copyright 2010 UCSD AUVSI. All rights reserved.
 *
 */
 
#pragma once
#pragma warning(push)
#pragma warning(disable:4996 4267)
#include <cv.h>
#include <highgui.h>
#pragma warning(pop)
#include "Auvsi_DualTree.h"
#include "Auvsi_cvFft.h"
#include "Auvsi_Radon.h"
#include "Auvsi_Recognize.h"

class Auvsi_Ocr {
public:
	Auvsi_Ocr();	// constructor
	~Auvsi_Ocr();	// destructor
	void processImage(cv::Mat image, float **letterFeatDesc, float **shapeFeatDesc);	// process the image
private:	// objects used for processing
	Auvsi_DualTree *theDualTree;
	Auvsi_Radon *theRadon;
	Auvsi_Fft *theFft;
	Auvsi_Recognize *theRecognize;
	
};