//
// Created by root on 19-4-17.
//

#include <cstdio>
#include <cstring>
#include <netinet/in.h>
#include "arp.h"
#include "ethernet.h"

arp::arp(unsigned char *packet) {
    unsigned int first;
    memcpy(&first, packet + ethernet::HEADER_LENGTH, 4);
    first = ntohl(first);
    hwType = (first >> 16) & 0xFFFF;
    ptType = first & 0xFFFF;

    unsigned int second;
    memcpy(&second, packet + ethernet::HEADER_LENGTH + 4, 4);
    second = ntohl(second);
    hwLen = (second >> 24) & 0xFF;
    ptLen = (second >> 16) & 0xFF;
    operation = second & 0xFFFF;

    memcpy(senderHwAddr, packet + ethernet::HEADER_LENGTH + 8, 6);
    memcpy(senderPtAddr, packet + ethernet::HEADER_LENGTH + 14, 4);
    memcpy(targetHwAddr, packet + ethernet::HEADER_LENGTH + 18, 6);
    memcpy(targetPtAddr, packet + ethernet::HEADER_LENGTH + 24, 4);
}


char *arp::toString() {
    char * summary = new char [1024]{0};
    sprintf(summary,
            "    hwType=%u, ptType=%#.2x, hwLen=%u, ptLen=%u, operation=%u\n"
            "    senderHwAddr=%.2x:%.2x:%.2x:%.2x:%.2x:%.2x, senderPtAddr=%u.%u.%u.%u\n"
            "    targetHwAddr=%.2x:%.2x:%.2x:%.2x:%.2x:%.2x, targetPtAddr=%u.%u.%u.%u\n",
            hwType, ptType, hwLen, ptLen, operation,
            senderHwAddr[0], senderHwAddr[1], senderHwAddr[2], senderHwAddr[3], senderHwAddr[4], senderHwAddr[5],
            senderPtAddr[0], senderPtAddr[1], senderPtAddr[2], senderPtAddr[3],
            targetHwAddr[0], targetHwAddr[1], targetHwAddr[2], targetHwAddr[3], targetHwAddr[4], targetHwAddr[5],
            targetPtAddr[0], targetPtAddr[1], targetPtAddr[2], targetPtAddr[3]);
    return summary;
}



unsigned short arp::getHwType() const {
    return hwType;
}

unsigned short arp::getPtType() const {
    return ptType;
}

unsigned char arp::getHwLen() const {
    return hwLen;
}

unsigned char arp::getPtLen() const {
    return ptLen;
}

unsigned short arp::getOperation() const {
    return operation;
}

const unsigned char *arp::getSenderHwAddr() const {
    return senderHwAddr;
}

const unsigned char *arp::getSenderPtAddr() const {
    return senderPtAddr;
}

const unsigned char *arp::getTargetHwAddr() const {
    return targetHwAddr;
}

const unsigned char *arp::getTargetPtAddr() const {
    return targetPtAddr;
}



void arp::setHwType(unsigned short hwType) {
    arp::hwType = hwType;
}

void arp::setPtType(unsigned short ptType) {
    arp::ptType = ptType;
}

void arp::setHwLen(unsigned char hwLen) {
    arp::hwLen = hwLen;
}

void arp::setPtLen(unsigned char ptLen) {
    arp::ptLen = ptLen;
}

void arp::setOperation(unsigned short operation) {
    arp::operation = operation;
}
