#include <iostream>
#include <sys/socket.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <cstring>
#include <linux/if_packet.h>
#include <net/if.h>
#include <thread>
#include "mao_protocol_stack/packet.h"

using namespace std;


void *startPort(void *portName) {
    // construct socket.
    int sockFd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockFd < 0) {
        cout << "fail." << sockFd << ", " << errno << endl;
        return (void *) -1;
    }

    int rcvbuf = 0;
    setsockopt(sockFd, SOL_SOCKET, SO_RCVBUF, &rcvbuf, sizeof(rcvbuf));

    // get device name.
    size_t deviceLen = strnlen((char *) portName, IFNAMSIZ);
    if (deviceLen >= IFNAMSIZ) {
        cout << "dev name too long." << endl;
        return (void *) -2;
    }

    // bind device
    struct sockaddr_ll device = {0,};
    device.sll_family = AF_PACKET;
    device.sll_ifindex = if_nametoindex((char *) portName);
    device.sll_protocol = htons(ETH_P_ALL);
    int ret = bind(sockFd, (struct sockaddr *) &device, sizeof(device));
    if (ret != 0) {
        cout << "bind fail." << endl;
        return (void *) -3;
    }


    printf("Start %s ...\n", (char *) portName);

    unsigned int count = 0;
    while (1) {
        unsigned char *recvBuf = new unsigned char[2048]{0,};
        sockaddr addr;
        socklen_t socklen;
        size_t size = recvfrom(sockFd, recvBuf, 2048, 0, &addr, &socklen);

        packet *pkt = packet::parsePacket(recvBuf, size);

        size = sendto(sockFd, pkt->getRawFrame(), size, 0, (struct sockaddr *) &device, sizeof(device));

        if (++count % 10 == 0) {
            printf("========= %s ========= %u ========= %u ========= %u =========\n", (char *) portName, count, size, errno);

            char *summary = pkt->toString();
            printf("%s", summary);
            delete[] summary;
        }

        delete pkt;
    }
}

int main(int argc, char *argv[]) {

    ios::sync_with_stdio(false);
    std::cin.tie(0);

    pthread_t thread[10] = {0};

    int ret = 0;
    ret += pthread_create(thread, nullptr, startPort, (void *) "ens160");
//    ret += pthread_create(thread + 1, nullptr, startPort, (void *) "ens192");
//    ret += pthread_create(thread + 2, nullptr, startPort, (void *) "lo");
    if (ret > 0) {
        cout << "Fail to pthread_create..." << endl;
        return -1;
    }

    pthread_exit(nullptr);
//    return 0;
}
