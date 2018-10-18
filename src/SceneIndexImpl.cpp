#include "SceneIndexImpl.h"
#include "VideoDecoder.h"
#include "VideoEncoder.h"
#include "FilterChain.h"
#include "Converter.h"

SceneIndexImpl::SceneIndexImpl(const char* filename, int W, int H, ImageCallback& sc)
    : videoDec(std::make_shared<VideoDecoder>(filename))
    , filterChain(nullptr)
    , converter(nullptr)
    , scene(sc)
    , picW(W)
    , picH(H)
{
    filterChain = std::make_unique<FilterChain>(*videoDec);
    filterChain->add("select", "gt(scene,0.4)");
    filterChain->finish();
    
    converter = std::make_unique<Converter>(*videoDec, picW, picH, AV_PIX_FMT_BGR24);
}

SceneIndexImpl::~SceneIndexImpl() {
}

bool SceneIndexImpl::run() {
    Packet pkt;
    VideoEncoder enc(AV_CODEC_ID_BMP, AV_PIX_FMT_BGR24, picW, picH);
    while(videoDec->readPacket(pkt)) {
        Frame decodedFrm;
        
        if(videoDec->decode(pkt, decodedFrm)) {
            filterChain->pushFrame(decodedFrm);
            
            Frame filteredFrame;
            
            if(filterChain->popFrame(filteredFrame) == COMPLETE) {
                Frame outFrame(converter->getFrameSize(), AV_PIX_FMT_BGR24, picW, picH);
                converter->convert(decodedFrm, outFrame);
                
                Packet outPacket;
                enc.encode(outFrame, outPacket);
                ImageFrame img(outPacket.getData(), outPacket.getSize(), 
                        decodedFrm.timestamp()*videoDec->getStreamTimeBase());
                scene.putImage(img);
            }
        }
    }
    scene.finishMsg();
    return true;
}

