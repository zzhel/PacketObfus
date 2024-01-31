// PacketObfus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Handler;

#include <windows.h>

int main()
{
    std::unique_ptr<Packet> l_Packet(new Packet(1337 | ((uint64_t)0xABCDEFFF << 32)));
    auto l_Seq = l_Packet->ScrambleObjectGuid();
}
