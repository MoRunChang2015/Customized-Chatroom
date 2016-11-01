#ifndef TCPSEGMENT_H
#define TCPSEGMENT_H

#include <arpa/inet.h>

typedef struct TCPHeader {
    unsigned short srcPort;
    unsigned short destPort;
    unsigned int seqNum;
    unsigned int ackNum;
    unsigned short length_flag;
    unsigned short recvWindow;
    unsigned short checksum;
    unsigned short urgPointer;
} TCPHeader;


class TCPSegment {
public:
    TCPSegment();
    TCPSegment(void *buffer);

    void setBuffer(void *buffer);

    unsigned short getSrcPort();
    void setSrcPort(unsigned short srcPort);
    unsigned short getDestPort();
    void setDestPort(unsigned short destPort);

    void addSeqNum(unsigned int offset);
    void addAckNum(unsigned int offset);

    bool isACK();
    bool isSYN();
    bool isFIN();

    void setACK(bool flag);
    void setSYN(bool flag);
    void setFIN(bool flag);

    TCPHeader *header;
    void *data;
};


#endif /* TCPSEGMENT_H */
