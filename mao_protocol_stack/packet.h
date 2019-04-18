//
// Created by root on 19-4-17.
//

#ifndef MAO_SOCKET_RAW_PACKET_H
#define MAO_SOCKET_RAW_PACKET_H


#include "lib/L2type.h"
#include "lib/L3type.h"
#include "lib/L4type.h"
#include "protocol/ethernet.h"
#include "protocol/arp.h"
#include "protocol/ipv4.h"
#include "protocol/tcp.h"
#include "protocol/udp.h"

class packet {

public:
    static packet *parsePacket(unsigned char *pkt, unsigned int totalLen);

    ~packet();

public:
    char *toString();

private:
    packet(L2type l2type, L3type l3type, L4type l4type, void *l2, void *l3, void *l4, unsigned char *rawData, unsigned int dataLen);

public:
    L2type getL2type() const;

    L3type getL3type() const;

    L4type getL4type() const;


    ethernet *getEthernetLayer();

    arp *getArpLayer();

    ipv4 *getIpv4Layer();

    tcp *getTcpLayer();

    udp *getUdpLayer();

    unsigned char *getRawFrame() const;

    unsigned int getRawLen() const;


private:
    L2type l2type;
    L3type l3type;
    L4type l4type;

    void *l2;
    void *l3;
    void *l4;

    unsigned char *rawFrame;
    unsigned int rawLen;
};


#endif //MAO_SOCKET_RAW_PACKET_H
