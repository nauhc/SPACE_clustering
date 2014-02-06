#ifndef _MIPASATTRIBUTE_H_
#define _MIPASATTRIBUTE_H_
struct MIPASAttribute
{
	double time;//time 
	double lat, lon; 
	float alt;//longitude, latitude and altitude.
	unsigned int orbitNr;
	unsigned char profileId;
	unsigned char detection;
	MIPASAttribute(double t=0.0,float latitude=0.0f, float longitude=0.0f,
				   float altitude=0.0f, unsigned int oNr=0, unsigned char pId=0,
				   unsigned char det=0) 
	{
		time=t;
		lon=latitude;
		lat=longitude;
		alt=altitude;
		orbitNr=oNr;
		profileId=pId;
		detection=det;
	}
	bool operator != (const MIPASAttribute& mipas){
		 return (time!=mipas.time)||(lat!=mipas.lat)||(lon!=mipas.lon)
				||(alt != mipas.alt) || (profileId != mipas.profileId)
				||(detection != mipas.detection);
	}
	friend ostream& operator << (ostream& os, const MIPASAttribute& d){
		os << "time: "<<d.time<<" lat: "<<d.lat<<" lon: "<<d.lon <<" alt: "
			<< d.alt << " orbitNr: "<<d.orbitNr << " profileId: "<<(int)d.profileId
			<<" detection: "<<(int)d.detection<<endl;
	   return os;
	}
};
#endif