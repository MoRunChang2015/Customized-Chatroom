#include <cstring>

#include "TCPSegment.h"

TCPSegment::TCPSegment() : data(nullptr), header(nullptr) {}

TCPSegment::TCPSegment(void *buffer) { setBuffer(buffer); }

void TCPSegment::setBuffer(void *buffer) {
    header = (TCPHeader *)buffer;
    data = (char *)buffer + sizeof(header);
}

unsigned short TCPSegment::getSrcPort() { return htons(header->srcPort); }
void TCPSegment::setSrcPort(unsigned short srcPort) {
    header->srcPort = htons(srcPort);
}
unsigned short TCPSegment::getDestPort() { return htons(header->destPort); }
void TCPSegment::setDestPort(unsigned short destPort) {
    header->destPort = htons(destPort);
}

void TCPSegment::addSeqNum(unsigned int offset) {
    header->seqNum = htonl(htonl(header->seqNum) + offset);
}

void TCPSegment::addAckNum(unsigned int offset) {
    header->ackNum = htonl(htonl(header->ackNum) + offset);
}

bool TCPSegment::isACK() { return htons(header->length_flag) & 0x0010; }

bool TCPSegment::isSYN() { return htons(header->length_flag) & 0x0002; }

bool TCPSegment::isFIN() { return htons(header->length_flag) & 0x0001; }

void TCPSegment::setACK(bool flag) {
    header->length_flag = htons(header->length_flag);
    if (flag) {
        header->length_flag |= 0x0010;
    } else {
        header->length_flag &= 0xFFEF;
    }
    header->length_flag = htons(header->length_flag);
}

void TCPSegment::setSYN(bool flag) {
    header->length_flag = htons(header->length_flag);
    if (flag) {
        header->length_flag |= 0x0002;
    } else {
        header->length_flag &= 0xFFFD;
    }
    header->length_flag = htons(header->length_flag);
}

void TCPSegment::setFIN(bool flag) {
    header->length_flag = htons(header->length_flag);
    if (flag) {
        header->length_flag |= 0x0001;
    } else {
        header->length_flag &= 0xFFFE;
    }
    header->length_flag = htons(header->length_flag);
}
