#ifndef TCPSTREAM_H
#define TCPSTREAM_H

#include <string>

#include "SegmentLoader.h"

using namespace std;


class TCPStream {
    friend class TCPConnector;
    friend class TCPAcceptor;

public:
    ~TCPStream();

    ssize_t send(const string &buffer);
    ssize_t read(string &buffer, size_t len);

private:
    TCPStream(int socketDescriptor, unsigned short destPort, char *buffer);
    TCPStream(const TCPStream &);

    char *buffer;

    int socketDescriptor;
    unsigned short destPort;
};


#endif /* TCPSTREAM_H */
