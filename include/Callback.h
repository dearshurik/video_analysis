#ifndef CALLBACK_H
#define CALLBACK_H

#include "Config.h"

namespace VideoAnalysis {

class CPP_API ImageCallback {
public:
    virtual void putImage(uint8_t* picData, size_t picSize, double timestamp) = 0;
    virtual void finishMsg() = 0;
};

class CPP_API AudioCallback {
public:
    virtual void putSamples(uint8_t ch, short* samples, size_t size, double timestamp) = 0;
    virtual void finishMsg() = 0;	
};

}

#endif /* CALLBACK_H */

