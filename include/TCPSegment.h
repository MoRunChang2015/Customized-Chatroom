#ifndef TCPSEGMENT_H
#define TCPSEGMENT_H

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

    void setHeader(TCPHeader &header);


    TCPHeader header;
    void *data;
};


#endif /* TCPSEGMENT_H */
