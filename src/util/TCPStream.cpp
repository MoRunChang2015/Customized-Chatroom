#include "TCPStream.h"

TCPStream::TCPStream(int socketDescriptor, unsigned short destPort,
                     char *buffer) {
    this->socketDescriptor = socketDescriptor;
    this->destPort = destPort;
    this->buffer = buffer;
}

TCPStream::~TCPStream() { delete buffer; }
