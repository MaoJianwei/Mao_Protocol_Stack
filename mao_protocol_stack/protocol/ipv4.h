//
// Created by mao on 19-4-16.
//

#ifndef MAO_SOCKET_RAW_IPV4_H
#define MAO_SOCKET_RAW_IPV4_H


class ipv4 {

public:
    static const int HEADER_LENGTH = 20; // bytes

    ipv4(unsigned char *packet);

public:
    char *getDstAddr();

    char *getSrcAddr();

    char *toString();

private:
    void generateChecksum();

public:
    unsigned char getVer() const;

    unsigned char getIhl() const;

    unsigned char getDscp() const;

    unsigned char getEcn() const;

    unsigned short getTotalLength() const;

    unsigned short getIdentification() const;

    bool isDF() const;

    bool isMF() const;

    unsigned short getFragmentOffset() const;

    unsigned char getTtl() const;

    unsigned char getIpProtocol() const;

    unsigned short getChecksum() const;

    const unsigned char *getDst() const;

    const unsigned char *getSrc() const;

public:
    void setVer(unsigned char ver);

    void setIhl(unsigned char ihl);

    void setDscp(unsigned char dscp);

    void setEcn(unsigned char ecn);

    void setTotalLength(unsigned short totalLength);

    void setIdentification(unsigned short identification);

    void setDF(bool DF);

    void setMF(bool MF);

    void setFragmentOffset(unsigned short fragmentOffset);

    void setTtl(unsigned char ttl);

    void setIpProtocol(unsigned char ipProtocol);

    void setChecksum(unsigned short checksum);


private:
    unsigned char ver;
    unsigned char ihl;
    unsigned char dscp;
    unsigned char ecn;
    unsigned short totalLength;

    unsigned short identification;
    bool DF;
    bool MF;
    unsigned short fragmentOffset;

    unsigned char ttl;
    unsigned char ipProtocol;
    unsigned short checksum;

    unsigned char dst[4];
    unsigned char src[4];
};


#endif //MAO_SOCKET_RAW_IPV4_H
