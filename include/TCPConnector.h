#ifndef TCPCONNECTOR_H
#define TCPCONNECTOR_H

#include <string>
#include <vector>

#include "TCPStream.h"
#include "SegmentLoader.h"

#define START_PORT 50000
#define LOCALHOST "127.0.0.1"

using namespace std;

class TCPConnector {
public:
    TCPStream *connect(const string &server, unsigned short port);

private:
    //  bind() is not available
    //  the connector must manage ports that it allocated
    static vector<unsigned short> usedPort;
};


#endif /* TCPCONNECTOR_H */
