/*
 * tsfilter.cpp
 *
 *  Created on: 16 Jan 2011
 *      Author: hatton.mark@gmail.com
 */

#include "../include/Packet.h"
#include "../include/PSI.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;
using namespace libts;

void usage(string message = "")
{
    if (!message.empty())
        cout << message << endl;

    cout
            << "Usage: tsfilter [OPTION]... [PID]...\n"
                "Filters a transport stream given a set of PIDs to include in the output.\n"
                "If no input/output file names are given stdin and stdout are assumed.\n\n"
                "Options:\n"
                "  -a                         automatically select first a/v streams\n"
                "  -p                         only output the pid numbers in ascii, not ts data\n"
                "  -c                         clean: strip mpegts headers from packets\n"
                "  -i file                    input file to use\n"
                "  -o file                    output file to use\n";
}

bool doAutoFilter(Packet& packet, set<int> &filter_pids);

int main(int argc, char* argv[])
{
    bool pids_only = false;
    bool no_headers = false;
    bool auto_filter = false;
    set<int> filter_pids;
    string infile, outfile;

    // TODO use getopt
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "-p")
        {
            pids_only = true;
        }
        else if (string(argv[i]) == "-c")
        {
            no_headers = true;
        }
        else if (string(argv[i]) == "-a")
        {
            auto_filter = true;
        }
        else if (string(argv[i]) == "-i" || string(argv[i]) == "-o")
        {
            if (i + 1 >= argc)
            {
                usage("tsfilter: missing filename for option -- " + string(
                        argv[i]));
                return 1;
            }
            if (string(argv[i]) == "-i")
                infile = argv[++i];
            else
                outfile = argv[++i];
        }
        else
        {
            int pid;
            istringstream iss(argv[i]);
            iss >> pid;
            if (iss.fail())
            {
                usage("tsfilter: invalid option -- " + string(argv[i]));
                return 1;
            }
            filter_pids.insert(pid);
        }
    }

    istream* istreamp = &cin;
    istream* infilestream = 0;
    ostream* ostreamp = &cout;
    ostream* outfilestream = 0;
    if (!infile.empty())
    {
        istreamp = infilestream
                = new ifstream(infile.c_str(), ifstream::binary);
    }
    if (!outfile.empty())
    {
        ostreamp = outfilestream = new ofstream(outfile.c_str(), ofstream::out
                | ofstream::binary | ofstream::trunc);
    }
    istream& in = *istreamp;
    ostream& out = *ostreamp;

    Packet packet;
    while (true)
    {
        bool keep = false;
        in >> packet;

        if (packet.good)
        {
            if (auto_filter)
            {
                keep = doAutoFilter(packet, filter_pids);
            }
            else if (filter_pids.empty())
            {
                keep = true;
            }
            if (filter_pids.find(packet.getPid()) != filter_pids.end())
            {
                keep = true;
            }
            if (keep)
            {
                if (pids_only)
                {
                    out << packet.getPid() << endl;
                }
                else if (no_headers)
                {
                    packet.writePayload(out);
                }
                else
                {
                    out << packet;
                }
            }
        }
        else if (in.fail())
        {
            break;
        }
        else
        {
            cerr << "WARN: sync not implemented yet!" << endl;
        }
    }
    out.flush();

    // clean up streams
    // TODO use scoped_ptr
    if (infilestream)
        delete infilestream;
    if (outfilestream)
        delete outfilestream;
}

bool doAutoFilter(Packet& packet, set<int> &filter_pids)
{
    bool keep = false;
    static bool foundPAT = false;
    static bool foundPMT = false;
    static int pmtPID = -1;

    if (packet.getPid() == 0)
    {
        keep = true;
        if (!foundPAT && packet.getPayloadStart())
        {
            PAT pat;
            pat << packet;
            if (pat.good)
            {
                foundPAT = true;
                vector<PAT::Program> programs = pat.getPrograms();
                for (vector<PAT::Program>::iterator it = programs.begin(); it
                        < programs.end(); it++)
                {
                    if ((*it).getProgramNumber() != 0) // ignore NIT
                    {
                        pmtPID = (*it).getPid();
                        break;
                    }
                }
            }
        }
    }
    else if (foundPAT && packet.getPid() == pmtPID)
    {
        keep = true;
        PMT pmt;
        pmt << packet;
        if (!foundPMT && pmt.good)
        {
            vector<PMT::Stream> streams = pmt.getStreams();
            for (vector<PMT::Stream>::iterator it = streams.begin(); it
                    < streams.end(); it++)
            {
                if ((*it).getStreamType() == 3)
                {
                    int pid = (*it).getElementaryPid();
                    filter_pids.insert(pid);
                    cerr << "found audio pid:" << pid << endl;
                }
                if (((*it).getStreamType() == 2
                        || (*it).getStreamType() == 27))
                {
                    int pid = (*it).getElementaryPid();
                    filter_pids.insert(pid);
                    cerr << "found video pid:" << pid << endl;
                }
            }
            foundPMT = true;
        }
    }
    return keep;
}
