#include "IPv4.H"

uint8_t IPv4_Header::getVersion(IPv4_Header_t *h) {
    return ((h->version_headerlen & 0xf0) >> 4);
}

uint8_t IPv4_Header::getHeaderLen(IPv4_Header_t *h) {
    return (h->version_headerlen & 0x0f);
}

uint8_t IPv4_Header::getHeaderLenInBytes(IPv4_Header_t *h) {
    return getHeaderLen(h) * 4;
}

uint8_t IPv4_Header::getFlags(IPv4_Header_t *h) {
    return ((h->flags_fragoffset & 0xE000) >> 13);
}

uint8_t IPv4_Header::getFragmentOffset(IPv4_Header_t *h) {
    return (h->flags_fragoffset & 0x1FFF);
}

bool IPv4_Header::validate_checksum(uint8_t *net_frame) {
    IPv4_Header_t *h = (IPv4_Header_t *) net_frame;
    uint8_t num_blocks_of_16bits = IPv4_Header::getHeaderLenInBytes(h) / 2;
    uint32_t u32_sum = 0;
    uint16_t *p = (uint16_t *) net_frame;
    for (uint8_t i = 0; i < num_blocks_of_16bits; i++)
        u32_sum += p[i];
    uint16_t carry = ((u32_sum & 0x000f0000) >> 16);
    uint16_t u16_sum = (u32_sum & 0x0000ffff);
    uint16_t result = ~(u16_sum + carry);
    if (result != 0) {
        return false;
    }
    else {
        return true;
    }
}

ostream& operator << (ostream& os, IPv4_Header_t &h) {
    os   << "IPv4_Header_t{"
         << "version_headerlen=0x" << hex << (int) h.version_headerlen << dec
         << ",tos=0x"              << hex << (int) h.tos               << dec
         << ",total_len=0x"        << hex << (int) h.total_len         << dec
         << ",id=0x"               << hex << (int) h.id                << dec
         << ",flags_fragoffset=0x" << hex << (int) h.flags_fragoffset  << dec
         << ",ttl=0x"              << hex << (int) h.ttl               << dec
         << ",protocol=0x"         << hex << (int) h.protocol          << dec
         << ",header_checksum=0x"  << hex << (int) h.header_checksum   << dec
         << ",src_addr=0x"         << hex << (int) h.src_addr          << dec
         << ",dst_addr=0x"         << hex << (int) h.dst_addr          << dec
         << "}";
    return os;
}
