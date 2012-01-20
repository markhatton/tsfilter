/*
 * testPSI.cpp
 *
 *  Created on: 22 Jan 2011
 *      Author: purple
 */

#include "../include/Packet.h"
#include "../include/PSI.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdint.h>

using namespace libts;
using namespace std;

int main()
{
    stringstream ss;

    // PAT
    ss << (uint8_t) 0x47 << (uint8_t) 0x40 << (uint8_t) 0x00 << (uint8_t) 0x14
            << (uint8_t) 0x00 << (uint8_t) 0x00 << (uint8_t) 0x80
            << (uint8_t) 0x11 << (uint8_t) 0x10 << (uint8_t) 0x01
            << (uint8_t) 0x09 << (uint8_t) 0x00 << (uint8_t) 0x00
            << (uint8_t) 0x00 << (uint8_t) 0x00 << (uint8_t) 0x00
            << (uint8_t) 0x10 << (uint8_t) 0x10 << (uint8_t) 0x44
            << (uint8_t) 0x10 << (uint8_t) 0x44 << (uint8_t) 0xc0
            << (uint8_t) 0x97 << (uint8_t) 0x4f << (uint8_t) 0x54;
    for (int i = 25; i < 188; i++)
        ss << (uint8_t) 0xff;

    // PMT
    ss << (uint8_t) 0x47 << (uint8_t) 0x50 << (uint8_t) 0x44 << (uint8_t) 0x15
            << (uint8_t) 0x00 << (uint8_t) 0x02 << (uint8_t) 0xb0
            << (uint8_t) 0x82 << (uint8_t) 0x10 << (uint8_t) 0x44
            << (uint8_t) 0xef << (uint8_t) 0x00 << (uint8_t) 0x00
            << (uint8_t) 0xe2 << (uint8_t) 0x58 << (uint8_t) 0xf0
            << (uint8_t) 0x00 << (uint8_t) 0x02 << (uint8_t) 0xe2
            << (uint8_t) 0x58 << (uint8_t) 0xf0 << (uint8_t) 0x03
            << (uint8_t) 0x52 << (uint8_t) 0x01 << (uint8_t) 0x01
            << (uint8_t) 0x03 << (uint8_t) 0xe2 << (uint8_t) 0x59
            << (uint8_t) 0xf0 << (uint8_t) 0x09 << (uint8_t) 0x0a
            << (uint8_t) 0x04 << (uint8_t) 0x65 << (uint8_t) 0x6e
            << (uint8_t) 0x67 << (uint8_t) 0x00 << (uint8_t) 0x52
            << (uint8_t) 0x01 << (uint8_t) 0x02 << (uint8_t) 0x06
            << (uint8_t) 0xe2 << (uint8_t) 0x5b << (uint8_t) 0xf0
            << (uint8_t) 0x0d << (uint8_t) 0x52 << (uint8_t) 0x01
            << (uint8_t) 0x05 << (uint8_t) 0x59 << (uint8_t) 0x08
            << (uint8_t) 0x65 << (uint8_t) 0x6e << (uint8_t) 0x67
            << (uint8_t) 0x10 << (uint8_t) 0x00 << (uint8_t) 0x01
            << (uint8_t) 0x00 << (uint8_t) 0x01 << (uint8_t) 0x03
            << (uint8_t) 0xe2 << (uint8_t) 0x5a << (uint8_t) 0xf0
            << (uint8_t) 0x09 << (uint8_t) 0x52 << (uint8_t) 0x01
            << (uint8_t) 0x06 << (uint8_t) 0x0a << (uint8_t) 0x04
            << (uint8_t) 0x65 << (uint8_t) 0x6e << (uint8_t) 0x67
            << (uint8_t) 0x03 << (uint8_t) 0x0b << (uint8_t) 0xe2
            << (uint8_t) 0x8a << (uint8_t) 0xf0 << (uint8_t) 0x03
            << (uint8_t) 0x52 << (uint8_t) 0x01 << (uint8_t) 0x65
            << (uint8_t) 0x0b << (uint8_t) 0xe2 << (uint8_t) 0x8b
            << (uint8_t) 0xf0 << (uint8_t) 0x03 << (uint8_t) 0x52
            << (uint8_t) 0x01 << (uint8_t) 0x66 << (uint8_t) 0x0b
            << (uint8_t) 0xe2 << (uint8_t) 0x8c << (uint8_t) 0xf0
            << (uint8_t) 0x03 << (uint8_t) 0x52 << (uint8_t) 0x01
            << (uint8_t) 0x67 << (uint8_t) 0x0b << (uint8_t) 0xe3
            << (uint8_t) 0xed << (uint8_t) 0xf0 << (uint8_t) 0x12
            << (uint8_t) 0x52 << (uint8_t) 0x01 << (uint8_t) 0x6e
            << (uint8_t) 0x13 << (uint8_t) 0x05 << (uint8_t) 0x00
            << (uint8_t) 0x00 << (uint8_t) 0x00 << (uint8_t) 0x01
            << (uint8_t) 0x00 << (uint8_t) 0x66 << (uint8_t) 0x06
            << (uint8_t) 0x01 << (uint8_t) 0x06 << (uint8_t) 0x01
            << (uint8_t) 0x01 << (uint8_t) 0x00 << (uint8_t) 0x00
            << (uint8_t) 0x0b << (uint8_t) 0xe3 << (uint8_t) 0xee
            << (uint8_t) 0xf0 << (uint8_t) 0x03 << (uint8_t) 0x52
            << (uint8_t) 0x01 << (uint8_t) 0x6f << (uint8_t) 0x0b
            << (uint8_t) 0xe3 << (uint8_t) 0xef << (uint8_t) 0xf0
            << (uint8_t) 0x03 << (uint8_t) 0x52 << (uint8_t) 0x01
            << (uint8_t) 0x70 << (uint8_t) 0x97 << (uint8_t) 0xc2
            << (uint8_t) 0xb4 << (uint8_t) 0x79;
    for (int i = 46 * 3; i < 188; i++)
        ss << (uint8_t) 0xff;

    Packet packet;
    ss >> packet;

    PAT pat;

    pat << packet;

    cerr << "Packet pid: " << packet.getPid() << endl;
    cerr << "PAT programs:\n";
    vector<PAT::Program> programs = pat.getPrograms();
    for (vector<PAT::Program>::iterator it = programs.begin(); it
            < programs.end(); it++)
    {
        cerr << "  " << (*it).getProgramNumber() << "  " << (*it).getPid()
                << endl;
    }

    ss >> packet;
    PMT pmt;
    pmt << packet;
    cerr << "PMT Program Number: " << pmt.getProgramNumber() << endl;
    cerr << "PMT Section Length:" << pmt.getSectionLength() << endl;
    cerr << "PMT Streams:\n";
    vector<PMT::Stream> streams = pmt.getStreams();
    for (vector<PMT::Stream>::iterator it = streams.begin(); it < streams.end(); it++)
    {
        cerr << "  " << (*it).getStreamType() << "  "
                << (*it).getElementaryPid() << endl;
    }

    return 0;
}
