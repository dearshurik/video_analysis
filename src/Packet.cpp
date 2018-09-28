#include "Packet.h"

Packet::Packet() {
    packet.data = NULL;
    packet.size = 0;
    av_init_packet(&packet);    
}

Packet::Packet(const Packet& orig) {
}

Packet::~Packet() {
}

void Packet::free() {
    av_free_packet(&packet);
}

