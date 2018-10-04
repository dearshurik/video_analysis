/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AudioDecoder.cpp
 * Author: kuznetsov
 * 
 * Created on October 4, 2018, 3:30 PM
 */

#include "AudioDecoder.h"

AudioDecoder::AudioDecoder(const char * filename)
   : Decoder(filename, AVMEDIA_TYPE_AUDIO)
{
}

AudioDecoder::~AudioDecoder() {
}

bool AudioDecoder::decode(Packet& packet, Frame& frame) {
    int frame_finished;
    if(packet.getStreamIdx() == streamIdx) {
        avcodec_decode_audio4(codecContext, frame, &frame_finished, packet);
        packet.free();
        return (frame_finished > 0);  
    }
    return false;
}
