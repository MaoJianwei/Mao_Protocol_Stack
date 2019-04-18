//
// Created by root on 19-4-17.
//

#ifndef MAO_SOCKET_RAW_TCP_H
#define MAO_SOCKET_RAW_TCP_H


class tcp {

public:
    tcp(unsigned char *packet);

public:
    char *toString();


public:
    unsigned short getSrc() const;

    unsigned short getDst() const;

    unsigned int getSeq() const;

    unsigned int getAck() const;

    unsigned char getDataOffset() const;

    bool isNS() const;

    bool isCWR() const;

    bool isECE() const;

    bool isURG() const;

    bool isACK() const;

    bool isPSH() const;

    bool isRST() const;

    bool isSYN() const;

    bool isFIN() const;

    unsigned short getWindowSize() const;

    unsigned short getChecksum() const;

    unsigned short getUrgentPointer() const;

public:
    void setSrc(unsigned short src);

    void setDst(unsigned short dst);

    void setSeq(unsigned int seq);

    void setAck(unsigned int ack);

    void setDataOffset(unsigned char dataOffset);

    void setNS(bool NS);

    void setCWR(bool CWR);

    void setECE(bool ECE);

    void setURG(bool URG);

    void setACK(bool ACK);

    void setPSH(bool PSH);

    void setRST(bool RST);

    void setSYN(bool SYN);

    void setFIN(bool FIN);

    void setWindowSize(unsigned short windowSize);

    void setChecksum(unsigned short checksum);

    void setUrgentPointer(unsigned short urgentPointer);

private:
    unsigned short src;
    unsigned short dst;

    unsigned int seq;
    unsigned int ack;

    unsigned char dataOffset; // x 4 bytes
    bool NS;
    bool CWR;
    bool ECE;
    bool URG;
    bool ACK;
    bool PSH;
    bool RST;
    bool SYN;
    bool FIN;
    unsigned short windowSize;

    unsigned short checksum;
    unsigned short urgentPointer;
};


#endif //MAO_SOCKET_RAW_TCP_H
