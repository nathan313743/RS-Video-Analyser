#include "TransportDetails.h"

TransportDetails::TransportDetails()
{
	_audio_only = false;
	_num_aud_services = 0;
	_num_vid_services = 0;
}

	bool TransportDetails::get_audio_only()
	{
		return _audio_only;
	}

	int TransportDetails::get_num_aud_services()
	{
		return _num_aud_services;
	}

	int TransportDetails::get_num_vid_services()
	{
		return _num_vid_services;
	}

	TransData& TransportDetails::get_trans_data()
	{
		return _trans_data;
	}
	
	void TransportDetails::set_audio_only(bool b)
	{
		_audio_only = b;
	}

	void TransportDetails::set_num_aud_service(int num)
	{
		_num_aud_services = num;
	}

	void TransportDetails::set_num_vid_service(int num)
	{
		_num_vid_services = num;
	}

	void TransportDetails::set_trans_data(TransData &td)
	{
		_trans_data = td;
	}