#ifndef SEGMENTLOADER_H
#define SEGMENTLOADER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <linux/if_packet.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>



#include "TCPSegment.h"

#define BUFFER_SIZE 10240

class SegmentLoader {
public:
    SegmentLoader();
    ~SegmentLoader();

    static char buffer[BUFFER_SIZE];

    static ssize_t catchSegment(int socketDescriptor, void *segment,
                                unsigned short destPort, unsigned int destIP,
                                unsigned short srcPort = 0, unsigned int srcIP = 0);
    static bool sendSegment(int socketDescriptor, unsigned int destIP, void *tcpSegment, int size);
};


#endif /* SEGMENTLOADER_H */
