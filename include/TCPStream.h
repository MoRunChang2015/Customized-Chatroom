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
    TCPStream();
    TCPStream(const TCPStream &);

    int socketDescriptor;
    int destPort;
};


#endif /* TCPSTREAM_H */
