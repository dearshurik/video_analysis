#include <cstdlib>

#include <iostream>
#include <jpeglib.h>
#include "VideoDecoder.h"
#include "VideoEncoder.h"
#include "Frame.h"
#include "FilterChain.h"
#include "Converter.h"
#include "Packet.h"

const int dst_w = 320;
const int dst_h = 240;

int main(int argc, char** argv) {
    VideoDecoder dec("/home/kuznetsov/video/4308.mp4");
    FilterChain filterChain(dec);

    filterChain.addFilter("select", "gt(scene,0.1)");
    filterChain.finishChain();

    auto frameCnt = 0;

    Converter conv(dec, 320, 240, AV_PIX_FMT_BGR24);
    VideoEncoder enc(AV_CODEC_ID_BMP, AV_PIX_FMT_BGR24, 320, 240);

    Packet pkt;
    
    while(dec.readPacket(pkt)) {
        Frame frm;
        
        if(dec.decode(pkt, frm)) {
            Frame frame_out;
            filterChain.pushFrame(frm);
            
            if(filterChain.popFrame(frame_out) == COMPLETE) {
                Frame frm_to_save(conv.getFrameSize(), AV_PIX_FMT_BGR24, 320, 240);
                std::cout << "Scene detect " << ++frameCnt << " " << frm.getTimestamp() << " " << frame_out.getTimestamp() << std::endl;
                std::string filename = "scene" + std::to_string(frameCnt) + ".bmp";
                
                conv(frm, frm_to_save);
                
                Packet pkt_out;
                enc.encode(frm_to_save, pkt_out);
                //frame_out.saveJPEG(filename.c_str(), dec.getVideoCodecCtx());
                
                FILE *f = fopen(filename.c_str(), "wb");
                fwrite(pkt_out.getPacketData(), 1, pkt_out.getPacketSize(), f);
                fclose(f);
                        
            }
        }
    }
}
        