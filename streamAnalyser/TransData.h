
#ifndef TRANSDATA_H_
#define TRANSDATA_H_

/*************************************************************
 ** Storage class.  Holds part of the tranport stream data 
 ** where the relationship is one to many.  Many data to one
 ** transport stream.
 *************************************************************/
class TransData
{
public:
	TransData();
	bool getTeletext();
	bool getSubtitle();
	bool getMHP();
	bool getMHEG5();

	void setTeletext(bool b);
	void setSubtitle(bool b);
	void setMHP(bool b);
	void setMHEG5(bool b);

private:

		bool _bTeletext;
		bool _bSubtitle;
		bool _bMHP;				//Not supported yet
		bool _bMHEG5;;		//Not supported yet
};

#endif