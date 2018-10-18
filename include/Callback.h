#ifndef CALLBACK_H
#define CALLBACK_H

#include "Config.h"

namespace VideoAnalysis {

class AudioFrame {
public:
    AudioFrame(uint8_t ch, short* samples, size_t size, double timestamp) 
        : ch_(ch)
        , samples_(samples)
        , size_(size)
        , timestamp_(timestamp)
    {
    }
    
    virtual ~AudioFrame() {
    }
	
	uint8_t getChannel() const { 
		return ch_; 
	}

	short* getSamples() const { 
		return samples_; 
	}
	
	void getSamples(short *outSamples) const { 
		for(int i = 0; i < getSize(); i++) {
			outSamples[i] = samples_[i];
		}
	}	

	size_t getSize() const { 
		return size_; 
	}

	double getTimestamp() const { 
		return timestamp_; 
	}	

private:
    uint8_t ch_;
    short* samples_;
    size_t size_;
    double timestamp_;
};

class ImageFrame {
public:
    ImageFrame(uint8_t* img, size_t size, double timestamp) 
        : image_(img)
        , size_(size)
        , timestamp_(timestamp)
    {
    }
    
    virtual ~ImageFrame() {
    }
	
	uint8_t* getImage() const { 
		return image_; 
	}
	
	void getImage(short *outSamples) const { 
		for(int i = 0; i < getSize(); i++) {
			outSamples[i] = image_[i];
		}
	}	

	size_t getSize() const { 
		return size_; 
	}

	double getTimestamp() const { 
		return timestamp_; 
	}	

private:
    uint8_t* image_;
    size_t size_;
    double timestamp_;
};

class CPP_API ImageCallback {
public:
	virtual ~ImageCallback() {}
    virtual void putImage(VideoAnalysis::ImageFrame img) = 0;
    virtual void finishMsg() = 0;
};

class CPP_API AudioCallback {
public:
	virtual ~AudioCallback() {}
    virtual void putSamples(VideoAnalysis::AudioFrame frame) = 0;
    virtual void finishMsg() = 0;	
};

}

#endif /* CALLBACK_H */

