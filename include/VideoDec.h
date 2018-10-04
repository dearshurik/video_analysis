#ifndef VIDEODEC_H
#define VIDEODEC_H

#include <memory>
#include "Callback.h"

class VideoDecImpl;

class VideoDec {
public:
	// Create video decoder detect object 
	// filename - media file name
	// picW, picH - output picture whidth and height
	// sc - callback object	
    VideoDec(const char* filename, int picW, int picH, ImageCallback& sc);
    VideoDec(const VideoDec& orig) = delete;
    virtual ~VideoDec();
    
	// Set decoding interval
	// tsStart - start decoding interval (in sec)
	// tsEnd - start decoding interval (in sec)
    bool setInterval(double tsStart, double tsEnd);
	
	// Run video decoder in self thread
    bool run();
private:
    std::unique_ptr<VideoDecImpl> implPtr;
};

#endif /* VIDEODEC_H */

