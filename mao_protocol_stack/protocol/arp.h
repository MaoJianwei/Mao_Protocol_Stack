//
// Created by root on 19-4-17.
//

#ifndef MAO_SOCKET_RAW_ARP_H
#define MAO_SOCKET_RAW_ARP_H


class arp {

public:
    static const int HEADER_LENGTH = 28; // bytes

    arp(unsigned char *packet);

public:
    char *toString();

public:
    void setHwType(unsigned short hwType);

    void setPtType(unsigned short ptType);

    void setHwLen(unsigned char hwLen);

    void setPtLen(unsigned char ptLen);

    void setOperation(unsigned short operation);

public:
    unsigned short getHwType() const;

    unsigned short getPtType() const;

    unsigned char getHwLen() const;

    unsigned char getPtLen() const;

    unsigned short getOperation() const;

    const unsigned char *getSenderHwAddr() const;

    const unsigned char *getSenderPtAddr() const;

    const unsigned char *getTargetHwAddr() const;

    const unsigned char *getTargetPtAddr() const;

private:
    unsigned short hwType;
    unsigned short ptType;
    unsigned char hwLen;
    unsigned char ptLen;

    unsigned short operation;

    unsigned char senderHwAddr[6];
    unsigned char senderPtAddr[4];

    unsigned char targetHwAddr[6];
    unsigned char targetPtAddr[4];
};


#endif //MAO_SOCKET_RAW_ARP_H
