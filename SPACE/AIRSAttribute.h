#ifndef _AIRSATTRIBUTE_H_
#define _AIRSATTRIBUTE_H_

struct AIRSAttribute
{
	double time;//time longitude and latitude.
	double lat, lon;
	
	float ash;
	float SO2;
	
	AIRSAttribute(double t=0.0, double X=0.0, double Y=0.0, float a=0.0f, float s=0.0f)
	{
		time=t;
		lon=X;
		lat=Y;
		ash = a;
		SO2 = s;
	}
	bool operator != (const AIRSAttribute& air){
		return (time!=air.time)||(lat!=air.lat)||(lon!=air.lon)
			   ||(ash != air.ash) || (SO2!=air.SO2);
	}
	friend ostream& operator << (ostream& os, const AIRSAttribute& air){
		os << "time: "<<air.time<<" lat: "<<air.lat<<" lon: "<<air.lon
		   << " ash: "<<air.ash << " SO2: "<<air.SO2<<endl;
	   return os;
	}
};
#endif