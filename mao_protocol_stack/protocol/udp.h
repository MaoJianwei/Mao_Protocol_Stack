//
// Created by root on 19-4-17.
//

#ifndef MAO_SOCKET_RAW_UDP_H
#define MAO_SOCKET_RAW_UDP_H


class udp {

public:
    udp(unsigned char *packet);

public:
    char *toString();


public:
    void setSrc(unsigned short src);

    void setDst(unsigned short dst);

    void setLength(unsigned short length);

    void setChecksum(unsigned short checksum);


public:
    unsigned short getSrc() const;

    unsigned short getDst() const;

    unsigned short getLength() const;

    unsigned short getChecksum() const;


private:
    unsigned short src;
    unsigned short dst;
    unsigned short length;
    unsigned short checksum;
};


#endif //MAO_SOCKET_RAW_UDP_H
