#include "TCPConnector.h"

vector<unsigned short> TCPConnector::usedPort{START_PORT};

TCPStream *TCPConnector::connect(const string &server, unsigned short port) {
    //  create a socket
    int socketDescriptor = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (socketDescriptor == -1) {
        return nullptr;
    }

    char *buffer = new char[BUFFER_SIZE]{0};

    //  destination address
    unsigned int _le_destAddress = inet_addr(server.c_str());
    //  destination port
    unsigned short _le_destPort = htons(port);

    //  allocate local port
    usedPort.push_back(usedPort.back() + 1);
    unsigned short _le_srcPort = htons(usedPort.back());
    TCPHeader tcpHeader{_le_srcPort,    _le_destPort, 0, 0,
                        htons(5 << 12), htons(5000),  0, 0};
    memcpy(buffer, &tcpHeader, sizeof(TCPHeader));
    TCPSegment tcpSegment(buffer);

    tcpSegment.setSYN(true);
    //  send the first handshake
    ssize_t segmentSize = SegmentLoader::sendSegment(
        socketDescriptor, _le_destAddress, buffer, 20);

    //  get the second handshake
    segmentSize = SegmentLoader::catchSegment(socketDescriptor, buffer,
                                              _le_srcPort, inet_addr(LOCALHOST),
                                              _le_destPort, _le_destAddress);

    if (!(tcpSegment.isACK() && tcpSegment.isSYN() && !tcpSegment.isFIN())) {
        delete buffer;
        return nullptr;
    }

    tcpSegment.setSYN(false);
    tcpSegment.header->srcPort = _le_srcPort;
    tcpSegment.header->destPort = _le_destPort;
    tcpSegment.addSeqNum(1);
    //  send the third handshake
    SegmentLoader::sendSegment(socketDescriptor, _le_destAddress, buffer,
                               sizeof(tcpHeader));
    return new TCPStream(socketDescriptor, _le_destPort, buffer);
}
