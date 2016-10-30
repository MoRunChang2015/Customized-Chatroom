#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>

#include "SegmentLoader.h"

using namespace std;

int main(void) {
    char buffer[10240] = {0};

    int s = socket (PF_INET, SOCK_RAW, IPPROTO_TCP);
    cout << "sd " << s << endl;

    cout << SegmentLoader::catchSegment(s, buffer, htons(8080), inet_addr("127.0.0.1"), htons(8000)) << endl;

    cout << ((char *)buffer + 20) << endl;

    close(s);

    return 0;
}
