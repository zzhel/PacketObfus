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

    // use an array with predetermined numbers, so that we can avoid a "while" rand loop that potentially carries on with more than required iterations
    // in essence, the following "for" scrambles the numbers array
    ScrambleGuidArray l_Bytes = { 0, 1, 2, 3, 4, 5, 6, 7 };
    uint8_t l_ByteArraySize = l_Bytes.size();
    for (uint8_t l_Idx = 0; l_Idx < l_ByteArraySize; ++l_Idx)
    {
        uint8_t* l_CurrentByte = &l_Bytes.at(l_Idx);

        // the rand is limited to interaction only with elements ahead of current
        std::swap(*l_CurrentByte, l_Bytes.at((rand() % (l_ByteArraySize - l_Idx)) + l_Idx));

        // get sole byte required
        uint8_t l_ByteSection = p_Guid >> (l_Idx * 8) & 0xFF;

        // move it however bits necessary accordingly
        uint64_t l_AdvancedByte = l_ByteSection << (*l_CurrentByte * 8);

        // append it to final guid
        l_ScrambledGuid |= std::move(l_AdvancedByte);
    }

    return l_Bytes;
}
