//
// Created by root on 19-4-17.
//

#include <cstdio>
#include <cstring>
#include "packet.h"


packet::packet(L2type l2type, L3type l3type, L4type l4type, void *l2, void *l3, void *l4, unsigned char *rawData, unsigned int dataLen)
        : l2type(l2type), l3type(l3type), l4type(l4type), l2(l2), l3(l3), l4(l4), rawFrame(rawData), rawLen(dataLen) {}

packet::~packet() {
    if (l2) {
        switch (l2type) {
            case ETHERNET:
                delete (ethernet *) l2;
                break;
        }
    }

    if (l3) {
        switch (l3type) {
            case ARP:
                delete (arp *) l3;
                break;
            case IPV4:
                delete (ipv4 *) l3;
                break;
        }
    }

    if (l4) {
        switch (l4type) {
            case TCP:
                delete (tcp *) l4;
                break;
            case UDP:
                delete (udp *) l4;
                break;
        }
    }

    if (rawFrame)
        delete [] rawFrame;
}

packet *packet::parsePacket(unsigned char *pkt, unsigned int totalLen) {

    unsigned char * raw = totalLen > 0 ? pkt : nullptr;

    ethernet *ether = new ethernet(pkt);
    if (ether->getEtherType() == 0x0800) {
        ipv4 *ip4 = new ipv4(pkt);

        if (ip4->getIpProtocol() == 17) { // UDP
            udp *udpLayer = new udp(pkt);
            return new packet(ETHERNET, IPV4, UDP, ether, ip4, udpLayer, raw, totalLen);

        } else if (ip4->getIpProtocol() == 6) { // TCP
            tcp *tcpLayer = new tcp(pkt);
            return new packet(ETHERNET, IPV4, TCP, ether, ip4, tcpLayer, raw, totalLen);
        } else {
            return new packet(ETHERNET, IPV4, NULL_L4, ether, ip4, nullptr, raw, totalLen);
        }
    } else if (ether->getEtherType() == 0x0806) {
        arp *arpLayer = new arp(pkt);
        return new packet(ETHERNET, ARP, NULL_L4, ether, arpLayer, nullptr, raw, totalLen);
    }
    return new packet(ETHERNET, NULL_L3, NULL_L4, ether, nullptr, nullptr, raw, totalLen);
}

char *packet::toString() {
    char *summary = new char[4096]{0};
    char *layersummary = nullptr;
    switch (l2type) {
        case ETHERNET:
            layersummary = getEthernetLayer()->toString();
            strcat(summary, "Ethernet\n");
            strcat(summary, layersummary);
            delete[] layersummary;
            break;
    }
    switch (l3type) {
        case ARP:
            layersummary = getArpLayer()->toString();
            strcat(summary, "    ARP\n");
            strcat(summary, layersummary);
            delete[] layersummary;
            break;
        case IPV4:
            layersummary = getIpv4Layer()->toString();
            strcat(summary, "    IPv4\n");
            strcat(summary, layersummary);
            delete[] layersummary;
            break;
    }
    switch (l4type) {
        case TCP:
            layersummary = getTcpLayer()->toString();
            strcat(summary, "        TCP\n");
            strcat(summary, layersummary);
            delete[] layersummary;
            break;
        case UDP:
            layersummary = getUdpLayer()->toString();
            strcat(summary, "        UDP\n");
            strcat(summary, layersummary);
            delete[] layersummary;
            break;
    }
    return summary;
}


ethernet *packet::getEthernetLayer() {
    return (ethernet *) l2;
}

arp *packet::getArpLayer() {
    return (arp *) l3;
}

ipv4 *packet::getIpv4Layer() {
    return (ipv4 *) l3;
}

tcp *packet::getTcpLayer() {
    return (tcp *) l4;
}

udp *packet::getUdpLayer() {
    return (udp *) l4;
}


L2type packet::getL2type() const {
    return l2type;
}

L3type packet::getL3type() const {
    return l3type;
}

L4type packet::getL4type() const {
    return l4type;
}

unsigned char *packet::getRawFrame() const {
    return rawFrame;
}

unsigned int packet::getRawLen() const {
    return rawLen;
}



