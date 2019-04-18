//
// Created by root on 19-4-17.
//

#include <cstdio>
#include <cstring>
#include <netinet/in.h>
#include "udp.h"
#include "ethernet.h"
#include "ipv4.h"


udp::udp(unsigned char *packet) {
    unsigned int first;
    memcpy(&first, packet + ethernet::HEADER_LENGTH + ipv4::HEADER_LENGTH, 4);
    first = ntohl(first);
    src = (first >> 16) & 0xFFFF;
    dst = first & 0xFFFF;

    unsigned int second;
    memcpy(&second, packet + ethernet::HEADER_LENGTH + ipv4::HEADER_LENGTH + 4, 4);
    second = ntohl(second);
    length = (second >> 16) & 0xFFFF;
    checksum = second & 0xFFFF;
}


char *udp::toString() {
    char *summary = new char[1024]{0};
    sprintf(summary,
            "        src=%u, dst=%u, length=%u, checksum=%u\n",
            src, dst, length, checksum);
    return summary;
}


unsigned short udp::getSrc() const {
    return src;
}

unsigned short udp::getDst() const {
    return dst;
}

unsigned short udp::getLength() const {
    return length;
}

unsigned short udp::getChecksum() const {
    return checksum;
}


void udp::setSrc(unsigned short src) {
    udp::src = src;
}

void udp::setDst(unsigned short dst) {
    udp::dst = dst;
}

void udp::setLength(unsigned short length) {
    udp::length = length;
}

void udp::setChecksum(unsigned short checksum) {
    udp::checksum = checksum;
}
