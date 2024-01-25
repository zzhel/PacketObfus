// PacketObfus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Handler;

#include <windows.h>

int main()
{
    Packet* l_Packet = new Packet();
    uint64_t l_Guid = 1337 | (0xFFFFFFFFULL << 32);
    auto l_Seq = l_Packet->ScrambleGuid(l_Guid);
}
