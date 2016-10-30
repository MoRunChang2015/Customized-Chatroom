#include <iostream>

#include "TCPAcceptor.h"
#include "TCPStream.h"

int main(void) {
    TCPAcceptor socket = TCPAcceptor(8080);
    TCPStream *stream = socket.accept();
    delete stream;
    return 0;
}
