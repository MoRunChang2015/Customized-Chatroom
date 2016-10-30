#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

#include "SegmentLoader.h"
#include "TCPSegment.h"

using namespace std;

int main(void) {
    char buffer[10240] = {0};
    TCPHeader tcp {htons(8000), htons(8080), 0, 0, htons((5 << 12)), htons(5000), 0, 0};
    memcpy(buffer, &tcp, sizeof(TCPHeader));
    memcpy(buffer + sizeof(TCPHeader), "abcd", 5);
    TCPSegment tcpSegment(buffer);

    int s = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    tcpSegment.setSYN(true);
    cout << "1 " <<  tcpSegment.isSYN() << tcpSegment.isACK() << tcpSegment.isFIN() << endl;
    cout << SegmentLoader::sendSegment(s, inet_addr("127.0.0.1"), buffer, 25) << endl;

    unsigned int ip = inet_addr("127.0.0.1");
    unsigned short port = htons(8080);

    SegmentLoader::catchSegment(s, buffer, htons(8000), ip, port, ip);
    cout << "2 " << tcpSegment.isSYN() << tcpSegment.isACK() << tcpSegment.isFIN() << endl;
    tcpSegment.setSYN(false);
    tcpSegment.setACK(true);
    cout << "3 " << tcpSegment.isSYN() << tcpSegment.isACK() << tcpSegment.isFIN() << endl;
    tcpSegment.header->srcPort = htons(8000);
    tcpSegment.header->destPort = htons(8080);
    cout << SegmentLoader::sendSegment(s, ip, buffer, 25) << endl;

    close(s);
    return 0;
}
