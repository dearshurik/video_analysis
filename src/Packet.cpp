#include "Packet.h"

Packet::Packet() {
    av_init_packet(&packet);    
}

Packet::Packet(const Packet& orig) {
}

Packet::~Packet() {
}

void Packet::free() {
    av_free_packet(&packet);
}

