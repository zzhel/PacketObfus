#include <array>
#include <vector>

export module Handler;

using ScrambleGuidArray = std::array<uint8_t, 8>;

class Packet
{
public:
    Packet() { }

    ScrambleGuidArray ScrambleGuid(uint64_t& p_Guid);
private:
};

export ScrambleGuidArray Packet::ScrambleGuid(uint64_t& p_Guid)
{
    std::vector<uint8_t> l_BytesToPick = { 0, 1, 2, 3, 4, 5, 6, 7 };

    ScrambleGuidArray l_Bytes = { };
    for (uint8_t l_Idx = 0; l_Idx < 8; ++l_Idx)
    {
        // get random element from bytes available
        auto l_Rand = l_BytesToPick.begin();
        std::advance(l_Rand, rand() % l_BytesToPick.size());
        // set byte
        l_Bytes[l_Idx] = *l_Rand;
        // remove used element
        l_BytesToPick.erase(l_Rand);
    }

    uint64_t l_ScrambledGuid = 0;
    for (uint8_t l_Idx = 0; l_Idx < 8; ++l_Idx)
    {
        // get sole byte required
        uint64_t l_ByteSection = p_Guid >> (l_Idx * 8) & 0xFF;
        // move it however bits necessary according to the "map"
        uint64_t l_AdvancedByte = l_ByteSection << (l_Bytes[l_Idx] * 8);
        // append it to final guid
        l_ScrambledGuid |= l_AdvancedByte;
    }

    p_Guid = l_ScrambledGuid;
    return l_Bytes;
}
