#ifndef AUDIODECIMPL_H
#define AUDIODECIMPL_H

#include <memory>
#include "Callback.h"

class AudioDecoder;

class AudioDecImpl {
public:
	AudioDecImpl(const char* filename, AudioCallback& sc);
	AudioDecImpl(const AudioDecImpl& orig) = delete;
	virtual ~AudioDecImpl();
	
    bool setInterval(double tsStart, double tsEnd);
    bool run();	
private:
    std::shared_ptr<AudioDecoder>   audioDec;
    AudioCallback&                  cb;
    double							endTimestamp;
};

#endif /* AUDIODECIMPL_H */

