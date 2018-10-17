#include <thread>

#include "AudioDecImpl.h"
#include <AudioDec.h>

using namespace VideoAnalysis;

AudioDec::AudioDec(const char* filename, AudioCallback& sc) 
    : implPtr(std::make_unique<AudioDecImpl>(filename, sc))
{
}

AudioDec::~AudioDec() {
}

bool AudioDec::setInterval(double tsStart, double tsEnd) {
    implPtr->setInterval(tsStart, tsEnd); 
}

bool AudioDec::run() {
    std::thread th{[](auto ptr) {
        ptr->run();
    }, std::move(implPtr)};
    th.detach();
    return true;    
}
