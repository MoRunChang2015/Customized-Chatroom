

#include <sys/socket.h>

#include "TCPAcceptor.h"
#include "TCPStream.h"


TCPAcceptor::TCPAcceptor(int port, const string &address)
    : port(port), address(address) {
    socketDescriptor = socket(PF_PACKET, SOCK_DGRAM, htons(ETH_P_IP));
}

TCPStream *TCPAcceptor::accept() {
    SegmentLoader::catchSegment(socketDescriptor, )
}
