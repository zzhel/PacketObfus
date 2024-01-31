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
    Packet(uint64_t p_ObjGuid)
    {
        m_ObjGuid = p_ObjGuid;
    }

    ScrambleGuidArray ScrambleObjectGuid();

private:
    uint64_t m_ObjGuid;
};

export ScrambleGuidArray Packet::ScrambleObjectGuid()
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
        uint8_t l_ByteSection = m_ObjGuid >> (l_Idx * 8) & 0xFF;

        // shift accordingly however many bits necessary
        uint64_t l_AdvancedByte = (uint64_t)l_ByteSection << (*l_CurrentByte * 8);

        // append to final guid
        l_ScrambledGuid |= std::move(l_AdvancedByte);
    }

    m_ObjGuid = l_ScrambledGuid;
    return l_Bytes;
}
