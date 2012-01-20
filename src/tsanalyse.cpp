/*
 * tsanalyse.cpp
 *
 * Copyright (C) 2011-2012 Mark Hatton
 *
 *  Created on: 17 Jan 2011
 *      Author: hatton.mark@gmail.com
 */

#include "../include/Packet.h"
#include "../include/PSI.h"

#include <iostream>

using namespace std;
using namespace libts;

int main()
{
    bool foundPAT = false;
    bool foundPMT = false;
    int pmtPID = -1;

    Packet packet;
    while (true)
    {
        cin >> packet;

        if (packet.good)
        {
            if (packet.getPid() == 0 && packet.getPayloadStart())
            {
                PAT pat;
                pat << packet;

                if (pat.good)
                {
                    if (!foundPAT)
                    {
                        cout << "--- Found PAT (pid: " << packet.getPid() << ")\n";
                        foundPAT = true;
                    }

                    vector<PAT::Program> programs = pat.getPrograms();
                    for (vector<PAT::Program>::iterator it = programs.begin(); it
                            < programs.end(); it++)
                    {
                        cout << "    Program Number: "
                                << (*it).getProgramNumber() << ", PID: "
                                << (*it).getPid() << endl;
                        if ((*it).getProgramNumber() != 0)
                        {
                            // ignore NIT
                            pmtPID = (*it).getPid();
                        }
                    }
                }
            }
            else if (packet.getPid() == pmtPID && packet.getPayloadStart())
            {
                PMT pmt;
                pmt << packet;
                if (pmt.good)
                {
                    if (!foundPMT)
                    {
                        cout << "--- Found PMT (pid: " << packet.getPid() << ")\n";
                        foundPMT = true;

                        vector<PMT::Stream> streams = pmt.getStreams();
                        for (vector<PMT::Stream>::iterator it = streams.begin(); it
                                < streams.end(); it++)
                        {
                            cout << "    Stream type: "
                                    << (*it).getStreamType() << ", PID: "
                                    << (*it).getElementaryPid() << endl;
                        }
                        break;
                    }
                }
            }
        }
        else if (cin.fail())
        {
            break;
        }
        else
        {
            //            cerr << "WARN: sync not implemented yet!" << endl;
        }
    }
    cout.flush();
}
