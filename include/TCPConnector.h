#ifndef TCPCONNECTOR_H
#define TCPCONNECTOR_H

#include <string>

using namespace std;

class TCPConnector {
public:
    TCPStream *connect(const string &server, int port);

    TCPConnector();
    ~TCPConnector();
};


#endif /* TCPCONNECTOR_H */
