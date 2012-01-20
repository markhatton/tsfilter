/*
 * PSI_PMT.h
 *
 *  Created on: 23 Jan 2011
 *      Author: purple
 */

#ifndef LIBTS_PSI_PMT_H_
#define LIBTS_PSI_PMT_H_

#include "Packet.h"

#include <iostream>
#include <vector>
#include <stdint.h>
#include <machine/endian.h>

namespace libts
{

class PMT
{
public:
    PMT() :
        good(false)
    {
    }

    class Stream
    {
    public:
        friend class PMT;
        enum StreamType
        {
            MPEG_1_VIDEO = 0x01,
            MPEG_2_VIDEO = 0x02,
            MPEG_1_AUDIO = 0x03,
            MPEG_2_AUDIO = 0x04,
        };

        inline StreamType getStreamType() const
        {
            return static_cast<StreamType> (stream_type);
        }

        inline uint16_t getElementaryPid() const
        {
            return (elementary_pid1 << 8) | elementary_pid2;
        }

    private:
        uint8_t stream_type;
        uint8_t elementary_pid1 :5;
        uint8_t reserved1 :3;
        uint8_t elementary_pid2;
        uint8_t es_info_length1 :2;
        uint8_t reserved2 :6;
        uint8_t es_info_length2;
        // FIXME no ES descriptor
    };

    // FIXME handle pointer field

    friend PMT& operator<<(PMT& pmt, Packet& packet)
    {
        const char* payload;
        packet.getPayload(payload);
        pmt = *reinterpret_cast<const PMT*> (payload);

        if (pmt.table_id == TABLE_ID_PMT)
        {
            pmt.good = true;
        }

        return pmt;
    }

    inline uint16_t getProgramNumber() const
    {
        return htons(program_number);
    }

    inline uint16_t getSectionLength() const
    {
        return (section_length1 << 8) | section_length2;
    }

    std::vector<PMT::Stream> getStreams() const
    {
        std::vector<PMT::Stream> streams;

        for (const uint8_t* off = data; off < data + getSectionLength()
                - sizeof(CRC32) - (data - &section_length2); off
                += sizeof(Stream))
        {
            Stream stream = *reinterpret_cast<const Stream*> (off);
            off += (stream.es_info_length1 << 8) | stream.es_info_length2;
            streams.push_back(stream);
        }
        return streams;
    }

    const static int PMT_HEADER_SIZE = 13;

    uint8_t pointer_field;
    uint8_t table_id;
    uint8_t section_length1 :2;
    uint8_t reserved1 :3;
    uint8_t section_syntax_indicator :1;
    uint8_t section_length2;
    uint16_t program_number;
    uint8_t current_next_indicator :1;
    uint8_t version_number :5;
    uint8_t reserved2 :2;
    uint8_t section_number;
    uint8_t last_section_number;
    uint8_t pcr_pid1 :5;
    uint8_t reserved3 :3;
    uint8_t pcr_pid2;
    uint8_t program_info_length1 :4; /* not reliable? */
    uint8_t reserved4 :4;
    uint8_t program_info_length2;
    uint8_t data[Packet::PACKET_SIZE - Packet::PACKET_HEADER_SIZE
            - PMT_HEADER_SIZE - sizeof(CRC32)];
    CRC32 crc;

public:
    bool good;
};

} // namespace

#endif /* LIBTS_PSI_PMT_H_ */
