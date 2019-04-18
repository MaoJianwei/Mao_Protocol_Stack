//
// Created by mao on 19-4-16.
//

#include <cstring>
#include <cstdio>
#include <netinet/in.h>
#include "ipv4.h"
#include "ethernet.h"

ipv4::ipv4(unsigned char *packet) {

    unsigned int first;
    memcpy(&first, packet + ethernet::HEADER_LENGTH, 4);
    first = ntohl(first);
    ver = (first >> 28) & 0x0F;
    ihl = (first >> 24) & 0x0F;
    dscp = (first >> 18) & 0x3F;
    ecn = (first >> 16) & 0x02;
    totalLength = first & 0xFFFF;

    unsigned int second;
    memcpy(&second, packet + ethernet::HEADER_LENGTH + 4, 4);
    second = ntohl(second);
    identification = (second >> 16) & 0xFFFF;
    DF = second & 0x4000; // TODO - debug
    MF = second & 0x2000; // TODO - debug
    fragmentOffset = second & 0x1FFF; // TODO - debug

    unsigned int third;
    memcpy(&third, packet + ethernet::HEADER_LENGTH + 8, 4);
    third = ntohl(third);
    ttl = (third >> 24) & 0xFF;
    ipProtocol = (third >> 16) & 0xFF;
    checksum = third & 0xFFFF; // TODO - debug

    memcpy(src, packet + ethernet::HEADER_LENGTH + 12, 4);
    memcpy(dst, packet + ethernet::HEADER_LENGTH + 16, 4);
}

char *ipv4::getDstAddr() {
    char *dstAddr = new char[16]{0};
    sprintf(dstAddr, "%u.%u.%u.%u", dst[0], dst[1], dst[2], dst[3]);
    return dstAddr;
}

char *ipv4::getSrcAddr() {
    char *srcAddr = new char[16]{0};
    sprintf(srcAddr, "%u.%u.%u.%u", src[0], src[1], src[2], src[3]);
    return srcAddr;
}

char *ipv4::toString() {
    char *summary = new char[1024]{0};
    sprintf(summary,
            "    ver=%u, IHL=%u, dscp=%u, ecn=%u, len=%u\n"
            "    id=%u, DF=%u, MF=%u, offset=%u\n"
            "    ttl=%u, proto=%u, checksum=%.4x\n"
            "    src=%u.%u.%u.%u dst=%u.%u.%u.%u\n",
            ver, ihl, dscp, ecn, totalLength,
            identification, DF, MF, fragmentOffset,
            ttl, ipProtocol, checksum,
            src[0], src[1], src[2], src[3],
            dst[0], dst[1], dst[2], dst[3]);
    return summary;
}


unsigned char ipv4::getVer() const {
    return ver;
}

unsigned char ipv4::getIhl() const {
    return ihl;
}

unsigned char ipv4::getDscp() const {
    return dscp;
}

unsigned char ipv4::getEcn() const {
    return ecn;
}

unsigned short ipv4::getTotalLength() const {
    return totalLength;
}

unsigned short ipv4::getIdentification() const {
    return identification;
}

bool ipv4::isDF() const {
    return DF;
}

bool ipv4::isMF() const {
    return MF;
}

unsigned short ipv4::getFragmentOffset() const {
    return fragmentOffset;
}

unsigned char ipv4::getTtl() const {
    return ttl;
}

unsigned char ipv4::getIpProtocol() const {
    return ipProtocol;
}

unsigned short ipv4::getChecksum() const {
    return checksum;
}

const unsigned char *ipv4::getDst() const {
    return dst;
}

const unsigned char *ipv4::getSrc() const {
    return src;
}


void ipv4::setVer(unsigned char ver) {
    ipv4::ver = ver;
}

void ipv4::setIhl(unsigned char ihl) {
    ipv4::ihl = ihl;
}

void ipv4::setDscp(unsigned char dscp) {
    ipv4::dscp = dscp;
}

void ipv4::setEcn(unsigned char ecn) {
    ipv4::ecn = ecn;
}

void ipv4::setTotalLength(unsigned short totalLength) {
    ipv4::totalLength = totalLength;
}

void ipv4::setIdentification(unsigned short identification) {
    ipv4::identification = identification;
}

void ipv4::setDF(bool DF) {
    ipv4::DF = DF;
}

void ipv4::setMF(bool MF) {
    ipv4::MF = MF;
}

void ipv4::setFragmentOffset(unsigned short fragmentOffset) {
    ipv4::fragmentOffset = fragmentOffset;
}

void ipv4::setTtl(unsigned char ttl) {
    ipv4::ttl = ttl;
}

void ipv4::setIpProtocol(unsigned char ipProtocol) {
    ipv4::ipProtocol = ipProtocol;
}

void ipv4::setChecksum(unsigned short checksum) {
    ipv4::checksum = checksum;
}
