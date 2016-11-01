#include "TCPConnector.h"

using namespace std;

int main(void) {
    TCPConnector socket;
    TCPStream *tcpStream = socket.connect("127.0.0.1", 8080);
    return 0;
}
