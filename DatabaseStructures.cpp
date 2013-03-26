#include "StdAfx.h"

#include "DatabaseStructures.h"
#include "TelemetryStructures.h"
#include "GeoReference.h"
#include "ImageWithPlaneData.h"

using namespace Database;
using namespace Vision;


CandidateRowData::CandidateRowData()
{
	this->telemetry = gcnew TelemetryRowData();
}

CandidateRowData::CandidateRowData(ImageWithPlaneData ^ planeState, int originX, int originY, int widthPixels, int heightPixels)
{
	this->telemetry = gcnew TelemetryRowData(planeState, originX, originY, widthPixels, heightPixels);
}

bool CandidateRowData::Equals(CandidateRowData ^ object)
{
	if (!imageName->Equals(object->imageName)) return false;
	if (!telemetry->Equals(object->telemetry)) return false;
	if (processed != object->processed) return false;
	return true;
}

DescriptionRowData::DescriptionRowData()
{
	this->targetX = 0;
	this->targetY = 0;
	this->shape = "-";
	this->shapeColor = "-";
	this->letter = "-";
	this->letterColor = "-";
	this->heading = "-";
}

bool DescriptionRowData::Equals(DescriptionRowData ^ object)
{
	if (!shape->Equals(object->shape)) return false;
	if (!shapeColor->Equals(object->shapeColor)) return false;
	if (!letter->Equals(object->letter)) return false;
	if (!letterColor->Equals(object->letterColor)) return false;
	if (!heading->Equals(object->heading)) return false;
	if (targetX != object->targetX) return false;
	if (targetY != object->targetY) return false;
	return true;
}

DialogEditingData::DialogEditingData(VerifiedRowData ^ data)
{
	this->imageName = data->target->candidate->imageName;
	this->shape = data->target->description->shape;
	this->shapeColor = data->target->description->shapeColor;
	this->letter = data->target->description->letter;
	this->letterColor = data->target->description->letterColor;
	this->targetX = data->target->description->targetX;
	this->targetY = data->target->description->targetY;
}

DialogEditingData::DialogEditingData(UnverifiedRowData ^ data)
{
	this->imageName = data->candidate->imageName;
	this->shape = data->description->shape;
	this->shapeColor = data->description->shapeColor;
	this->letter = data->description->letter;
	this->letterColor = data->description->letterColor;
	this->targetX = data->description->targetX;
	this->targetY = data->description->targetY;

}

DialogEditingData::DialogEditingData(CandidateRowData ^ data)
{
	this->imageName = data->imageName;
	this->id = data->candidateid;
}

bool DialogEditingData::Equals(DialogEditingData ^ object)
{
	if (!imageName->Equals(object->imageName)) return false;
	if (!shape->Equals(object->shape)) return false;
	if (!shapeColor->Equals(object->shapeColor)) return false;
	if (!letter->Equals(object->letter)) return false;
	if (!letterColor->Equals(object->letterColor)) return false;
	if (dataWidth != object->dataWidth) return false;
	if (dataHeight != object->dataHeight) return false;
	if (targetX != object->targetX) return false;
	if (targetY != object->targetY) return false;
	if (topOfTargetX != object->topOfTargetX) return false;
	if (topOfTargetY != object->topOfTargetY) return false;
	return true;
}

LocationRowData::LocationRowData(TelemetryRowData ^ telemetry)
{
	// calculate from telemetry
	double BLLat, BLLon, BRLat, BRLon, TRLat, TRLon, TLLat, TLLon;
	GeoReference::getCorners(telemetry, BLLat, BLLon, BRLat, BRLon, TRLat, TRLon, TLLat, TLLon);

	this->loc_id = 0;
	this->lowerLeftGPS = gcnew GPSPositionRowData(BLLat, BLLon, 0);
	this->lowerRightGPS = gcnew GPSPositionRowData(BRLat, BRLon, 0);
	this->upperLeftGPS = gcnew GPSPositionRowData(TLLat, TLLon, 0);
	this->upperRightGPS = gcnew GPSPositionRowData(TRLat, TRLon, 0);
}

bool LocationRowData::Equals(LocationRowData ^ object)
{
	if (!lowerLeftGPS->Equals(object->lowerLeftGPS)) return false;
	if (!lowerRightGPS->Equals(object->lowerRightGPS)) return false;
	if (!upperLeftGPS->Equals(object->upperLeftGPS)) return false;
	if (!upperRightGPS->Equals(object->upperRightGPS)) return false;
	return true;
}

TelemetryRowData::TelemetryRowData(ImageWithPlaneData ^ planeState, int originXIn, int originYIn, int widthPixelsIn, int heightPixelsIn)
{
	this->originX = originXIn;
	this->originY = originYIn;
	this->widthPixels = widthPixelsIn;
	this->heightPixels = heightPixelsIn;

	this->gimbalRoll = planeState->gimbalRoll;
	this->gimbalPitch = planeState->gimbalPitch;
	this->gimbalZoom = 1;
	this->planeRoll = planeState->roll;
	this->planePitch = planeState->pitch;
	this->planeHeading =  planeState->yaw;
	this->planeLocation = gcnew GPSPositionRowData(planeState->latitude, planeState->longitude, planeState->altitude);
	this->blurFactor = 0;

}

bool TelemetryRowData::Equals(TelemetryRowData ^ object)
	{
		if (!planeLocation->Equals(object->planeLocation)) return false;
		if (originX != object->originX) return false;
		if (originY != object->originY) return false;
		if (!approxEqual(gimbalRoll,object->gimbalRoll)) return false;
		if (!approxEqual(gimbalPitch, object->gimbalPitch)) return false;
		if (!approxEqual(gimbalYaw, object->gimbalYaw)) return false;
		if (gimbalZoom != object->gimbalZoom) return false;
		if (!approxEqual(blurFactor, object->blurFactor)) return false;
		if (widthPixels != object->widthPixels) return false;
		if (heightPixels != object->heightPixels) return false;
		if (!approxEqual(planeRoll, object->planeRoll)) return false;
		if (!approxEqual(planePitch, object->planePitch)) return false;
		if (!approxEqual(planeHeading, object->planeHeading)) return false;
		return true;
	}

//TelemetryRowData::TelemetryRowData(ImageWithPlaneData ^ planeState)
//{
//	this->originX = 0;
//	this->originY = 0;
//	this->widthPixels = 720;
//	this->heightPixels = 480;
//
//	this->gimbalRoll = planeState->gimbalRoll;
//	this->gimbalPitch = planeState->gimbalPitch;
//	this->gimbalZoom = planeState->gimbalInfo->zoom;
//	this->planeRoll = planeState->roll;
//	this->planePitch = planeState->pitch;
//	this->planeHeading =  planeState->yaw;
//	this->planeLocation = gcnew GPSPositionRowData(planeState->latitude, planeState->longitude, planeState->altitude);
//	this->blurFactor = planeState->blurFactor;
//
//}

UnverifiedRowData::UnverifiedRowData(CandidateRowData ^ candidate)
{
	this->candidate = candidate;
	this->location = gcnew LocationRowData(candidate->telemetry);
	this->description = gcnew DescriptionRowData();
}

UnverifiedRowData::UnverifiedRowData(ImageWithPlaneData ^ planeState, int originXIn, int originYIn, int widthPixelsIn, int heightPixelsIn)
{
	this->candidate = gcnew CandidateRowData(planeState, originXIn, originYIn, widthPixelsIn, heightPixelsIn);
	this->location = gcnew LocationRowData(this->candidate->telemetry);
	this->description = gcnew DescriptionRowData();
}

void UnverifiedRowData::updateCandidate(CandidateRowData ^ candidate)
{
	this->candidate = candidate;
	this->location = gcnew LocationRowData(this->candidate->telemetry);
}

bool UnverifiedRowData::Equals(UnverifiedRowData ^ object)
{
	if (!candidate->Equals(object->candidate)) return false;
	if (!location->Equals(object->location)) return false;
	if (!description->Equals(object->description)) return false;
	if (processed != object->processed) return false;
	if (revision != object->revision) return false;
	return true;
}

VerifiedRowData::VerifiedRowData(UnverifiedRowData ^ unverified)
{
	this->target = unverified;
	this->centerGPS = gcnew GPSPositionRowData(unverified);
}

bool VerifiedRowData::Equals(VerifiedRowData ^ object)
{
	if (!target->Equals(object->target)) return false;
	if (!centerGPS->Equals(object->centerGPS)) return false;
	return true;
}

GPSPositionRowData::GPSPositionRowData(UnverifiedRowData ^ unverified)
{
	double latGeoref, lonGeoref, altGeoref;
	GeoReference::getTargetGPS(unverified, latGeoref, lonGeoref, altGeoref);

	this->lat = latGeoref;
	this->lon = lonGeoref;
	this->alt = altGeoref;
}

double GPSPositionRowData::distanceTo(GPSPositionRowData ^ gps)
{
	double latDiff = fabs(gps->lat - this->lat);
	double lonDiff = fabs(gps->lon - this->lon);

	double latDiffMeters = Vision::GeoReference::GPStoMeters(latDiff);
	double lonDiffMeters = Vision::GeoReference::GPStoMeters(lonDiff);

	return sqrt(latDiffMeters*latDiffMeters + lonDiffMeters*lonDiffMeters);
}

bool GPSPositionRowData::Equals(GPSPositionRowData ^ object)
{
	if (!Vision::approxEqual(lat,object->lat)) return false;
	if (!Vision::approxEqual(lon,object->lon)) return false;
	if (!Vision::approxEqual(alt,object->alt)) return false;
	return true;
}