cmake_minimum_required(VERSION 3.10)
project(mao_protocol_stack)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-pthread)

add_executable(mao_protocol_stack main.cpp mao_protocol_stack/protocol/ethernet.cpp mao_protocol_stack/protocol/ethernet.h mao_protocol_stack/protocol/ipv4.cpp mao_protocol_stack/protocol/ipv4.h mao_protocol_stack/protocol/tcp.cpp mao_protocol_stack/protocol/tcp.h mao_protocol_stack/protocol/udp.cpp mao_protocol_stack/protocol/udp.h mao_protocol_stack/protocol/arp.cpp mao_protocol_stack/protocol/arp.h mao_protocol_stack/packet.cpp mao_protocol_stack/packet.h mao_protocol_stack/lib/L2type.h mao_protocol_stack/lib/L3type.h mao_protocol_stack/lib/L4type.h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(mao_protocol_stack Threads::Threads)
