/*
 * PSI_PAT.h
 *
 * Copyright (C) 2011-2012 Mark Hatton
 *
 *  Created on: 23 Jan 2011
 *      Author: hatton.mark@gmail.com
 */

#ifndef LIBTS_PSI_PAT_H_
#define LIBTS_PSI_PAT_H_

#include "Packet.h"

#include <iostream>
#include <vector>
#include <stdint.h>
#include <machine/endian.h>

namespace libts
{

class PAT
{
public:
    // FIXME handle pointer field
    PAT() :
        good(false)
    {
    }

    class Program
    {
    public:
        inline uint16_t getPid()
        {
            return (pid1 << 8) | pid2;
        }
        inline uint16_t getProgramNumber()
        {
            return htons(program_number);
        }
    private:
        uint16_t program_number;
        uint8_t pid1 :5;
        uint8_t unused :3;
        uint8_t pid2;
    };

    friend PAT& operator<<(PAT& pat, Packet& packet)
    {
        const char* payload;
        packet.getPayload(payload);
        pat = *reinterpret_cast<const PAT*> (payload);

        if (pat.table_id == TABLE_ID_PAT)
        {
            pat.good = true;
        }

        return pat;
    }

    std::vector<PAT::Program> getPrograms() const
    {
        std::vector<PAT::Program> programs;

        for (const uint8_t* off = data; off < data + getSectionLength()
                - sizeof(CRC32) - (data - &section_length2); off
                += sizeof(Program))
        {
            Program program = *reinterpret_cast<const Program*> (off);
            programs.push_back(program);
        }
        return programs;
    }

private:

    inline int16_t getSectionLength() const
    {
        return (section_length1 << 8) | section_length2;
    }

    const static int PAT_HEADER_SIZE = 9;

    uint8_t pointer_field;
    uint8_t table_id;
    uint8_t section_length1 :4;
    uint8_t reserved1 :3;
    uint8_t section_syntax_indicator :1;
    uint8_t section_length2;
    uint16_t stream_id;
    uint8_t current_next_indicator :1;
    uint8_t version_number :5;
    uint8_t reserved2 :2;
    uint8_t section_number;
    uint8_t last_section_number;
    uint8_t data[Packet::PACKET_SIZE - Packet::PACKET_HEADER_SIZE
            - PAT_HEADER_SIZE - sizeof(CRC32)];
    CRC32 crc;

public:
    bool good;
};

} // namespace

#endif /* LIBTS_PSI_PAT_H_ */
