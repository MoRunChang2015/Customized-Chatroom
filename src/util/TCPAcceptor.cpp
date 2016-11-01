#include "TCPAcceptor.h"

TCPAcceptor::TCPAcceptor(int port, const string &address)
    : port(port), address(address), bound(false) {
    socketDescriptor = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    _le_port = htons(port);
    _le_address = inet_addr(address.c_str());
}

TCPStream *TCPAcceptor::accept() {
    char *buffer = new char[BUFFER_SIZE];

    while (true) {

        unsigned short srcPort = 0;
        unsigned int srcIP = 0;


        //  await the first handshake
        ssize_t segmentSize = SegmentLoader::catchSegment(socketDescriptor, buffer,
                                                          _le_port, _le_address,
                                                          srcPort, srcIP);
        if (segmentSize == -1) {
            delete buffer;
            return nullptr;
        }

        TCPSegment segment(buffer);
        if (!(!segment.isACK() && segment.isSYN() && !segment.isFIN())) continue;

        //  send the second handshake
        segment.setACK(true);
        segment.header->srcPort = segment.header->destPort;
        segment.header->destPort = srcPort;
        segment.addAckNum(1);
        segmentSize = SegmentLoader::sendSegment(socketDescriptor, srcIP, buffer, sizeof(TCPHeader));

        //  await the thrid handshake
        segmentSize = SegmentLoader::catchSegment(socketDescriptor, buffer,
                                                  _le_port, _le_address,
                                                  srcPort, srcIP);

        segment.setBuffer(buffer);
        if (!(segment.isACK() && !segment.isSYN() && !segment.isFIN())) continue;

        TCPStream * tcpStream = new TCPStream(socketDescriptor, srcPort, buffer);
        return tcpStream;

    }
}
