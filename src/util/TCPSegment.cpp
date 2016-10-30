#include <cstring>

#include "TCPSegment.h"

TCPSegment::TCPSegment() : data(nullptr) {
    memset(&header, 0, sizeof(header));
}

void TCPSegment::setHeader(TCPHeader &header) {
    this->header = header;
}
