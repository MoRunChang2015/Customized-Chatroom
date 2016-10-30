#ifndef TCPACCEPTOR_H
#define TCPACCEPTOR_H

#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "SegmentLoader.h"
#include "TCPStream.h"

using namespace std;

class TCPAcceptor {
public:
    TCPAcceptor() = delete;

    TCPAcceptor(int port, const string &address = "127.0.0.1");

    TCPStream *accept();

private:
    unsigned short port;
    unsigned int _le_port;

    string address;
    unsigned int _le_address;
    int socketDescriptor;

};


#endif /* TCPACCEPTOR_H */
