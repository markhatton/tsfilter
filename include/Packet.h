/*
 * Packet.h
 *
 * Copyright (C) 2011-2012 Mark Hatton
 *
 *  Created on: 16 Jan 2011
 *      Author: hatton.mark@gmail.com
 */

#ifndef LIBTS_PACKET_H_
#define LIBTS_PACKET_H_

#include <iostream>
#include <stdint.h>

namespace libts
{

class Packet
{
public:
    Packet() :
        good(false)
    {
    }

    inline uint8_t getSync() const
    {
        return sync; /* should be 0x47 */
    }

    inline uint16_t getPid() const
    {
        return (pid1 << 8) | pid2;
    }

    inline bool getPayloadStart() const
    {
        return payload_start;
    }

    inline int getPayload(const char*& payload) const
    {
        // FIXME handle adaptation field
        payload = reinterpret_cast<const char*> (this) + PACKET_HEADER_SIZE;
        return PACKET_SIZE - PACKET_HEADER_SIZE;
    }

    inline std::ostream& writePayload(std::ostream& os) const
    {
        const char* payload;
        int size = getPayload(payload);
        os.write(payload, size);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Packet& packet)
    {
        is.read(reinterpret_cast<char*> (&packet), PACKET_SIZE);
        packet.good
                = (is.gcount() == PACKET_SIZE && packet.sync == PACKET_SYNC);
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, Packet& packet)
    {
        os.write(reinterpret_cast<char*> (&packet), PACKET_SIZE);
        return os;
    }

    const static int PACKET_SIZE = 188;

    const static int PACKET_HEADER_SIZE = 4;

    const static uint8_t PACKET_SYNC = 0x47;

private:
    uint8_t sync; /* sync byte (0x47) */
#ifdef XXX_TBD_BIT_ORDER
    uint8_t tei :1;
    uint8_t payload_start :1;
    uint8_t priority :1;
#endif /* XXX_TBD_BIT_ORDER */
    uint8_t pid1 :5;
#ifndef XXX_TBD_BIT_ORDER
    uint8_t priority :1;
    uint8_t payload_start :1;
    uint8_t tei :1;
#endif /* XXX_TBD_BIT_ORDER */
    uint8_t pid2;
#ifdef XXX_TBD_BIT_ORDER
    uint8_t scrambling_control :2;
    uint8_t adaptation_field_present :2;
#endif /* XXX_TBD_BIT_ORDER */
    uint8_t continuity_counter :4;
#ifndef XXX_TBD_BIT_ORDER
    uint8_t adaptation_field_present :2;
    uint8_t scrambling_control :2;
#endif /* XXX_TBD_BIT_ORDER */
    uint8_t data[184];

public:
    bool good;
};

} // namespace

#endif /* LIBTS_PACKET_H_ */
