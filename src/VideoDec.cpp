#include <thread>
#include "VideoDecImpl.h"
#include <VideoDec.h>

VideoDec::VideoDec(const char* filename, int picW, int picH, ImageCallback& sc)
    : implPtr(std::make_unique<VideoDecImpl>(filename, picW, picH, sc))
{
}

VideoDec::~VideoDec() {
}

bool VideoDec::run() {
    std::thread th{[](auto ptr) {
        ptr->run();
    }, std::move(implPtr)};
    th.detach();
    return true;
}

bool VideoDec::setInterval(double tsStart, double tsEnd) {
    implPtr->setInterval(tsStart, tsEnd);
}
