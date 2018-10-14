#ifndef CALLBACK_H
#define CALLBACK_H

class ImageCallback {
public:
    virtual void putImage(uint8_t* picData, size_t picSize, double timestamp) = 0;
    virtual void finishMsg() = 0;
};

class AudioCallback {
public:
    virtual void putSamples(uint8_t ch, float* samples, size_t size, double timestamp) = 0;
    virtual void finishMsg() = 0;	
};


#endif /* CALLBACK_H */

