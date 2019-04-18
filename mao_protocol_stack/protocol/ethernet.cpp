//
// Created by mao on 19-4-16.
//

#include <cstdio>
#include <cstring>
#include <netinet/in.h>
#include "ethernet.h"

ethernet::ethernet(unsigned char *packet) {
    memcpy(dst, packet, 6);
    memcpy(src, packet + 6, 6);
    memcpy(&etherType, packet + 12, 2);
    etherType = ntohs(etherType);
}

char *ethernet::getDstAddr() {
    char *dstAddr = new char[18]{0};
    sprintf(dstAddr, "%.2x:%.2x:%.2x:%.2x:%.2x:%.2x", dst[0], dst[1], dst[2], dst[3], dst[4], dst[5]);
    return dstAddr;
}

char *ethernet::getSrcAddr() {
    char *srcAddr = new char[18]{0};
    sprintf(srcAddr, "%.2x:%.2x:%.2x:%.2x:%.2x:%.2x", src[0], src[1], src[2], src[3], src[4], src[5]);
    return srcAddr;
}

char *ethernet::toString() {
    char *summary = new char[1024]{0};
    sprintf(summary,
            "dst=%.2x:%.2x:%.2x:%.2x:%.2x:%.2x, src=%.2x:%.2x:%.2x:%.2x:%.2x:%.2x, etherType=%#.4x\n",
            dst[0], dst[1], dst[2], dst[3], dst[4], dst[5],
            src[0], src[1], src[2], src[3], src[4], src[5],
            etherType);
    return summary;
}


const unsigned char *ethernet::getDst() const {
    return dst;
}

const unsigned char *ethernet::getSrc() const {
    return src;
}

unsigned short ethernet::getEtherType() const {
    return etherType;
}


void ethernet::setEtherType(unsigned short etherType) {
    ethernet::etherType = etherType;
}


