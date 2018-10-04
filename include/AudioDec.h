#ifndef AUDIODEC_H
#define AUDIODEC_H

#include <memory>
#include "Callback.h"

class AudioDecImpl;

class AudioDec {
public:
	// Create video decoder detect object 
	// filename - media file name
	// sc - callback object		
	AudioDec(const char* filename, AudioCallback& sc);
	AudioDec(const AudioDec& orig) = delete;
	virtual ~AudioDec();
	
	// Set decoding interval
	// tsStart - start decoding interval (in sec)
	// tsEnd - start decoding interval (in sec)
    bool setInterval(double tsStart, double tsEnd);
	
	// Run video decoder in self thread
    bool run();
private:
    std::unique_ptr<AudioDecImpl> implPtr;
};

#endif /* AUDIODEC_H */

