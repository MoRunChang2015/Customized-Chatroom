#ifndef TCPACCEPTOR_H
#define TCPACCEPTOR_H

#include <string>

using namespace std;

class TCPAcceptor {
public:
    TCPAcceptor() = delete;

    TCPAcceptor(int port, const string &address = "");
    ~TCPAcceptor();

    TCPStream *accept();

private:
    int port;
    string address;
    int socketDescriptor;

};


#endif /* TCPACCEPTOR_H */
