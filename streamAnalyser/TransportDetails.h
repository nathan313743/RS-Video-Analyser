
#ifndef TRANSDETAILS_H_
#define TRANSDETAILS_H_

#include "TransData.h"
#include <string>
using namespace std;

class TransData;
/************************************************
 ** Storage class.  Holds transport stream data.
 ************************************************/
 
class TransportDetails 
{
public:
	TransportDetails();
	
	bool get_audio_only();
	int get_num_aud_services();
	int get_num_vid_services();
	TransData& get_trans_data();
	
	void set_audio_only(bool);
	void set_num_aud_service(int num);
	void set_num_vid_service(int num);
	void set_trans_data(TransData &td);

private:
	bool _audio_only;
	int _num_aud_services;
	int _num_vid_services;
	TransData _trans_data;
};

#endif /* TRANSDETAILS_H_ */