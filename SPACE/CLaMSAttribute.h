#ifndef _CLAMSATTRIBUTE_H_
#define _CLAMSATTRIBUTE_H_

struct CLaMSAttribute
{
	double time;//time longitude and latitude.
	double lat, lon, alt;

	float pressure;
	float temperature;
	float pot_temperature;
	float pot_vorticity;
//	int	  seed_id;
	CLaMSAttribute(double t=0.0, double latitude=0.0, double longitude=0.0,
					float altitude=0.0f, float pres=0.0f, float temp=0.0f,
					float pt=0.0f, float pv=0.0f)//, int si=0)
	{
		time=t; lon=longitude; lat=latitude;
		alt=altitude; pressure = pres;
		temperature = temp; pot_temperature = pt;
		pot_vorticity = pv;
		//seed_id = si;
	}
	bool operator != (const CLaMSAttribute& clams){
		return   (time!=clams.time) ||(lat!=clams.lat)||(lon!=clams.lon)
			   ||(alt != clams.alt) || (pressure != clams.pressure)
			   ||(temperature != clams.temperature)
			   ||(pot_temperature != clams.pot_temperature)
			   ||(pot_vorticity != clams.pot_vorticity)
			   //||(seed_id != clams.seed_id)
			   ;
	}
	friend ostream& operator << (ostream& os, const CLaMSAttribute& clams){
		os << "time: "<<clams.time<<" lat: "<<clams.lat<<" lon: "<<clams.lon
		   << "pressure: "<<clams.pressure<<"pot_temp: "<<clams.pot_temperature
		   <<"pot_vort: "<<clams.pot_vorticity<<endl;
	   return os;
	}
};
struct CLaMSPathLine{
    int seedId;
    std::vector<size_t> pointIndices;
};
#endif