/*
 * PSI.h
 *
 *  Created on: 16 Jan 2011
 *      Author: purple
 */

#ifndef LIBTS_PSI_H_
#define LIBTS_PSI_H_

namespace libts
{

enum PSIPids
{
    PID_PAT = 0x0, /* Program Access Table */
    PID_CAT = 0x01, /* Conditional Access Table */
    /* 0x02 -> 0x0F reserved */
    PID_NIT = 0x10, /* Network Information Table */
    PID_TDT = 0x14,
/* Time and Date Table (or Time Offset Table) */
};

enum PSITableIds
{
    TABLE_ID_PAT = 0x0,
    TABLE_ID_PMT = 0x02,
};

class CRC32
{
    uint32_t crc;
};

} // namespace

#include "PSI_PAT.h"
#include "PSI_PMT.h"

#endif /* LIBTS_PSI_H_ */
