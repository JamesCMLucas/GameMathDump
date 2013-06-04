#ifndef __JL_cTimer_HG_20130314__
#define __JL_cTimer_HG_20130314__

class cTimer
{
public:
	cTimer();
	virtual ~cTimer();

	void Start();
	void Stop();
	void Reset();

	float Split(); // get total time passed, keep timing
	float Restart(); // get total time passed, restart
	float Elapsed(); // get total time passed

	unsigned long long GetFrequency(void);	
private:
	unsigned long long mElapsedTime;
	unsigned long long mStartTime;
	unsigned long long mStopTime;
	unsigned long long mFrequency;
};

#endif