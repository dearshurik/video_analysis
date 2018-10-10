#include "AudioDecImpl.h"
#include "AudioDecoder.h"

AudioDecImpl::AudioDecImpl(const char* filename, AudioCallback& sc)
    : audioDec(std::make_shared<AudioDecoder>(filename))
    , cb(sc)
    , endTimestamp(-1)
{
}

AudioDecImpl::~AudioDecImpl() {
}

bool AudioDecImpl::setInterval(double tsStart, double tsEnd) {
    if(audioDec->seek(tsStart)) {
        endTimestamp = tsEnd;
        return true;
    }
    return false;        
}

bool AudioDecImpl::run() {
    Packet pkt;
    while(audioDec->readPacket(pkt)) {
        Frame decodedFrm;
        
        if(audioDec->decode(pkt, decodedFrm)) {
            double currTs = decodedFrm.timestamp()*audioDec->getStreamTimeBase();
            for(int i = 0; i < decodedFrm.channels(); i++)
                cb.putSamples(i, decodedFrm.audio_data(i), decodedFrm.audioSize(), currTs);

            if((endTimestamp >= 0) && (currTs >= endTimestamp))
                break;
        }
    }
    cb.finishMsg();
    return true;    
}

