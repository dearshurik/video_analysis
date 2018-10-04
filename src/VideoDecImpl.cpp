#include "VideoDecImpl.h"
#include "VideoDecoder.h"
#include "VideoEncoder.h"
#include "Converter.h"

VideoDecImpl::VideoDecImpl(const char* filename, int W, int H, ImageCallback& sc) 
    : videoDec(std::make_shared<VideoDecoder>(filename))
    , converter(nullptr)
    , scene(sc)
    , picW(W)
    , picH(H)
    , endTimestamp(-1)
{
    converter = std::make_unique<Converter>(*videoDec, picW, picH, AV_PIX_FMT_BGR24);
}

VideoDecImpl::~VideoDecImpl() {
}

bool VideoDecImpl::setInterval(double tsStart, double tsEnd) {
    if(videoDec->seek(tsStart)) {
        endTimestamp = tsEnd;
        return true;
    }
    return false;
}

bool VideoDecImpl::run() {
    Packet pkt;
    VideoEncoder enc(AV_CODEC_ID_BMP, AV_PIX_FMT_BGR24, picW, picH);
    while(videoDec->readPacket(pkt)) {
        Frame decodedFrm;
        
        if(videoDec->decode(pkt, decodedFrm)) {

            Frame outFrame(converter->getFrameSize(), AV_PIX_FMT_BGR24, picW, picH);
            converter->convert(decodedFrm, outFrame);
                
            Packet outPacket;
            enc.encode(outFrame, outPacket);
            double currTs = decodedFrm.timestamp()*videoDec->getStreamTimeBase();
            scene.putImage(outPacket.getData(), outPacket.getSize(), currTs);

            if((endTimestamp >= 0) && (currTs >= endTimestamp))
                break;
        }
    }
    scene.finishMsg();
    return true;    
}

