#include <cv.h>
#include "stdafx.h"
#include <highgui.h>
#include "ImageWithPlaneData.h"
#include "../Pathfinding/Autosearch.h"
#include "PlaneDataReceiver.h"
#include "Util.h"
#include "GPSCoord.h"

using Intelligence::GPSCoord;

using namespace System;

ImageWithPlaneData::~ImageWithPlaneData(){
	clear();
}

ImageWithPlaneData::!ImageWithPlaneData(){
	clear();
}

void ImageWithPlaneData::clear(){
	delete image;
}

ImageWithPlaneData::ImageWithPlaneData(ImageWithPlaneData^ other) :
	imageFilename(other->imageFilename),
	image(other->image),
	latitude(other->latitude),
	longitude(other->longitude),
	altitude(other->altitude),
	roll(other->roll),
	pitch(other->pitch),
	yaw(other->yaw),
	gimbalRoll(other->gimbalRoll),
	gimbalPitch(other->gimbalPitch),
	xVelocity(other->xVelocity),
	yVelocity(other->yVelocity),
	zVelocity(other->zVelocity) {}

ImageWithPlaneData::ImageWithPlaneData(String ^ imageFilename, String ^data) {
	std::string imageFilenameStd = Util::managedToSTL(imageFilename);
	this->imageFilename = imageFilename;
	image = new cv::Mat(cv::imread(imageFilenameStd));
	// image->addref();
	auto vars = data->Split(' ');
	if (vars->Length >= 6){
		roll = 0;
		pitch = 0;
		yaw = 0;
		latitude = Convert::ToDouble(vars[3]);
		longitude = Convert::ToDouble(vars[4]);
		altitude = Convert::ToDouble(vars[5]) / 1000;
	} else {
		roll = 0;
		pitch = 0;
		yaw = 0;
		latitude = 0;
		longitude = 0;
		altitude = 0;
	}

	gimbalRoll = 0;
	gimbalPitch = 0;
	xVelocity = 0;
	yVelocity = 0;
	zVelocity = 0;

}


Intelligence::GPSCoord^ ImageWithPlaneData::toGPSCoord()
{
	return gcnew GPSCoord(longitude, latitude, altitude);
}

void ImageWithPlaneData::setPosition(GPSCoord^ coord)
{
	altitude = coord->alt;
	latitude = coord->lat;
	longitude = coord->lon;
}