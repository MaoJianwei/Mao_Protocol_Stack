//
// Created by mao on 19-4-16.
//

#ifndef MAO_SOCKET_RAW_ETHERNET_H
#define MAO_SOCKET_RAW_ETHERNET_H


class ethernet {

public:
    static const int HEADER_LENGTH = 14; // bytes

    ethernet(unsigned char *packet);


public:
    char *getDstAddr();

    char *getSrcAddr();

    char *toString();

    void setEtherType(unsigned short etherType);

public:
    const unsigned char *getDst() const;

    const unsigned char *getSrc() const;

    unsigned short getEtherType() const;


private:
    unsigned char dst[6];
    unsigned char src[6];
    unsigned short etherType;
};


#endif //MAO_SOCKET_RAW_ETHERNET_H
