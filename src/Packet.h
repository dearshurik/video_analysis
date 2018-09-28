#ifndef PACKET_H
#define PACKET_H

extern "C"{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
}

class Packet {
public:
    Packet();
    Packet(const Packet& orig);
    virtual ~Packet();
    
    operator AVPacket*() { return &packet; }
    
    void free();
    int getStreamIdx() const noexcept { return packet.stream_index; }
    
    size_t getPacketSize() const { return packet.size; }
    uint8_t* getPacketData() const { return packet.data; }
    
private:
    AVPacket            packet;
};

#endif /* PACKET_H */

