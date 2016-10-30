#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

#include "SegmentLoader.h"
#include "TCPSegment.h"

using namespace std;

int main(void) {
    char buffer[10240] = {0};
    TCPSegment tcpSegment;
    TCPHeader tcp {htons(8000), htons(8080), 0, 0, htons((short)(5 << 12)), htons(5000), 0, 0};
    tcpSegment.setHeader(tcp);
    tcpSegment.data = new char[5] {'a', 'b', 'c', 'd', '\0'};

    int s = socket (PF_INET, SOCK_RAW, IPPROTO_TCP);
    cout << "sd " << s << endl;

    memcpy(buffer, &tcp, sizeof(tcp));
    memcpy(buffer + sizeof(tcp), tcpSegment.data, 5);

    cout << SegmentLoader::sendSegment(s, inet_addr("127.0.0.1"), buffer, 25) << endl;


    delete (char *)tcpSegment.data;
    close(s);
    return 0;
}
