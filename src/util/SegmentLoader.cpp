#include "SegmentLoader.h"

typedef struct _iphdr {
    unsigned char ver_header; //4位首部长度+4位IP版本号 
    unsigned char tos; //8位服务类型TOS 
    unsigned short datagramLength; //16位总长度（字节） 
    unsigned short identifier; //16位标识 
    unsigned short frag_and_flags; //3位标志位 
    unsigned char ttl; //8位生存时间 TTL 
    unsigned char protocol; //8位协议 (TCP, UDP 或其他) 
    unsigned short checksum; //16位IP首部校验和 
    unsigned int srcIP; //32位源IP地址 
    unsigned int destIP; //32位目的IP地址 
} IPHeader;

char SegmentLoader::buffer[BUFFER_SIZE] = {0};

ssize_t SegmentLoader::catchSegment(int socketDescriptor, void *segment,
                                    unsigned short destPort, unsigned int destIP,
                                    unsigned short srcPort, unsigned int srcIP) {

    while (true) {
        ssize_t size = recv(socketDescriptor, buffer, BUFFER_SIZE, 0);
        if (size == -1) {
            return size;
        }

        IPHeader *ip = (IPHeader *)buffer;

        if (srcIP != 0) {
            if (ip->srcIP != srcIP || ip->destIP != destIP) continue;
        } else {
            if (ip->destIP != destIP) continue;
        }


        size_t IPHeaderLength = (ip->ver_header & 0x0f) * 4;
        TCPHeader *tcp = (TCPHeader *)(buffer + IPHeaderLength);

        if (srcPort != 0) {
            if (tcp->srcPort != srcPort || tcp->destPort != destPort) continue;
        } else {
            if (tcp->destPort != destPort) continue;
        }

        size_t segmentLength = htons(ip->datagramLength) - IPHeaderLength;
        memcpy(segment, tcp, segmentLength);
        return segmentLength;

    }
}

bool SegmentLoader::sendSegment(int socketDescriptor, unsigned int destIP, void *tcpSegment, int size) {
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(((TCPHeader *)tcpSegment)->destPort);
    sin.sin_addr.s_addr = destIP;

    return sendto(socketDescriptor, tcpSegment, size + 20, 0, (struct sockaddr *)&sin, sizeof(sin)) < 0;
}
