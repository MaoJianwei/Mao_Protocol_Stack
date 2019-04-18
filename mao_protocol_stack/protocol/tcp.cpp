//
// Created by root on 19-4-17.
//

#include <cstring>
#include <netinet/in.h>
#include <cstdio>
#include "tcp.h"
#include "ethernet.h"
#include "ipv4.h"


tcp::tcp(unsigned char *packet) {

    unsigned int first;
    memcpy(&first, packet + ethernet::HEADER_LENGTH + ipv4::HEADER_LENGTH, 4);
    first = ntohl(first);
    src = (first >> 16) & 0xFFFF;
    dst = first & 0xFFFF;

    unsigned int second;
    memcpy(&second, packet + ethernet::HEADER_LENGTH + ipv4::HEADER_LENGTH + 4, 4);
    seq = ntohl(second);

    unsigned int third;
    memcpy(&third, packet + ethernet::HEADER_LENGTH + ipv4::HEADER_LENGTH + 8, 4);
    ack = ntohl(third);

    unsigned int fourth;
    memcpy(&fourth, packet + ethernet::HEADER_LENGTH + ipv4::HEADER_LENGTH + 12, 4);
    fourth = ntohl(fourth);
    dataOffset = (fourth >> 28) & 0x0F;
    NS = fourth & 0x01000000;
    CWR = fourth & 0x00800000;
    ECE = fourth & 0x00400000;
    URG = fourth & 0x00200000;
    ACK = fourth & 0x00100000;
    PSH = fourth & 0x00080000;
    RST = fourth & 0x00040000;
    SYN = fourth & 0x00020000;
    FIN = fourth & 0x00010000;
    windowSize = fourth & 0xFFFF;

    unsigned int fifth;
    memcpy(&fifth, packet + ethernet::HEADER_LENGTH + ipv4::HEADER_LENGTH + 16, 4);
    fifth = ntohl(fifth);
    checksum = (fifth >> 16) & 0xFFFF;
    urgentPointer = fifth & 0xFFFF;
}


char *tcp::toString() {
    char *summary = new char[1024]{0};
    sprintf(summary,
            "        src=%u, dst=%u, seq=%u, ack=%u, dataOffset=%u\n"
            "        NS=%u, CWR=%u, ECE=%u, URG=%u, ACK=%u, PSH=%u, RST=%u, SYN=%u, FIN=%u\n"
            "        windowSize=%u, checksum=%u, urgentPointer=%u\n",
            src, dst, seq, ack, dataOffset,
            NS, CWR, ECE, URG, ACK, PSH, RST, SYN, FIN,
            windowSize, checksum, urgentPointer);
    return summary;
}


unsigned short tcp::getSrc() const {
    return src;
}

unsigned short tcp::getDst() const {
    return dst;
}

unsigned int tcp::getSeq() const {
    return seq;
}

unsigned int tcp::getAck() const {
    return ack;
}

unsigned char tcp::getDataOffset() const {
    return dataOffset;
}

bool tcp::isNS() const {
    return NS;
}

bool tcp::isCWR() const {
    return CWR;
}

bool tcp::isECE() const {
    return ECE;
}

bool tcp::isURG() const {
    return URG;
}

bool tcp::isACK() const {
    return ACK;
}

bool tcp::isPSH() const {
    return PSH;
}

bool tcp::isRST() const {
    return RST;
}

bool tcp::isSYN() const {
    return SYN;
}

bool tcp::isFIN() const {
    return FIN;
}

unsigned short tcp::getWindowSize() const {
    return windowSize;
}

unsigned short tcp::getChecksum() const {
    return checksum;
}

unsigned short tcp::getUrgentPointer() const {
    return urgentPointer;
}


void tcp::setSrc(unsigned short src) {
    tcp::src = src;
}

void tcp::setDst(unsigned short dst) {
    tcp::dst = dst;
}

void tcp::setSeq(unsigned int seq) {
    tcp::seq = seq;
}

void tcp::setAck(unsigned int ack) {
    tcp::ack = ack;
}

void tcp::setDataOffset(unsigned char dataOffset) {
    tcp::dataOffset = dataOffset;
}

void tcp::setNS(bool NS) {
    tcp::NS = NS;
}

void tcp::setCWR(bool CWR) {
    tcp::CWR = CWR;
}

void tcp::setECE(bool ECE) {
    tcp::ECE = ECE;
}

void tcp::setURG(bool URG) {
    tcp::URG = URG;
}

void tcp::setACK(bool ACK) {
    tcp::ACK = ACK;
}

void tcp::setPSH(bool PSH) {
    tcp::PSH = PSH;
}

void tcp::setRST(bool RST) {
    tcp::RST = RST;
}

void tcp::setSYN(bool SYN) {
    tcp::SYN = SYN;
}

void tcp::setFIN(bool FIN) {
    tcp::FIN = FIN;
}

void tcp::setWindowSize(unsigned short windowSize) {
    tcp::windowSize = windowSize;
}

void tcp::setChecksum(unsigned short checksum) {
    tcp::checksum = checksum;
}

void tcp::setUrgentPointer(unsigned short urgentPointer) {
    tcp::urgentPointer = urgentPointer;
}



