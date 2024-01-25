module;

#include <array>
#include <vector>
#include <stdio.h>

export module Handler;

//export module Handler;
//import std.compat;


using ScrambleGuidArray = std::array<uint8_t, 8>;

export class Packet
{
public:
    Packet() { }

    ScrambleGuidArray ScrambleGuid(uint64_t& p_Guid);
private:
};

export ScrambleGuidArray Packet::ScrambleGuid(uint64_t& p_Guid)
{
    uint64_t l_ScrambledGuid = 0;
    ScrambleGuidArray l_Bytes = { 0, 1, 2, 3, 4, 5, 6, 7 };

    // scramble array and fill guid based on current byte
    for (uint8_t l_Idx = 0; l_Idx < 8; ++l_Idx)
    {
        uint8_t* l_CurrentByte = &l_Bytes.at(l_Idx);

        // rand is limited to interaction only with elements ahead of current
        std::swap(*l_CurrentByte, l_Bytes.at((rand() % (8 - l_Idx)) + l_Idx));

        // get sole byte required
        uint8_t l_ByteSection = p_Guid >> (l_Idx * 8) & 0xFF;

        // shift accordingly however many bits necessary
        uint64_t l_AdvancedByte = l_ByteSection << (*l_CurrentByte * 8);

        // append to final guid
        l_ScrambledGuid |= std::move(l_AdvancedByte);
    }

    p_Guid = l_ScrambledGuid;
    return l_Bytes;
}
