/*    
    MPipeClient.exe : Sends text message to a named pipe
    Copyright (C) 2017  Comine.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


//v1.1 copyright Comine.com 20170708S1530
#include "MStdLib.h"
#include "MCommandArg.h"
#include "MLicenseGPL.h"
#include "MWinNamedPipe.h"


//******************************************************
//* Module Elements
//******************************************************
static const char *GApplicationName="MPipeClient";	// Used in Help
static const char *GApplicationVersion="1.1";		// Used in Help

static const int GWaitTime=3000;					// Wait for 3000ms for connection

////////////////////////////////////////////////////
static void GDisplayHelp(void);

////////////////////////////////////////////////////
int main(int argn,const char *argv[])
	{
	MCommandArg args(argn,argv);

	///////////////////////////////////////////////
	if(args.CheckRemoveArg("-gpl")==true)
		{
		MLicenseGPL license(true);
		license.Print();
		return 0;
		}

	if(args.GetArgCount()<3)
		{
		GDisplayHelp();
		return 0;
		}

	if(args.CheckRemoveHelp()==true)
		{
		GDisplayHelp();
		return 0;
		}

	const char *pipename=args.GetArg(1);
	const char *message=args.GetArg(2);
	const int messagelen=MStdStrLen(message);

	MWinNamedPipeClient pipeclient;
	if(pipeclient.Create(pipename,GWaitTime)==false)
		{
		MStdPrintf("**Unable to connect to named pipe %s within %dms\n",pipename,GWaitTime);
		return 1;
		}

	const int writtenlen=pipeclient.Write(message,messagelen+1);
	if(writtenlen!=messagelen+1)
		{
		MStdPrintf("**Unable to send message to pipe\n");
		return 1;
		}

	MStdPrintf("Done...\n");
	return 0;
	}


////////////////////////////////////////////////////
static void GDisplayHelp(void)
	{
	MStdPrintf(	"\n"
				"   usage:  %s [-?|-gpl] <pipename>  <msg> \n"
				"           v%s copyright Comine.com\n"
				"           -gpl displays the GNU public license\n"
				"\n"
				"   Send a string message to a named pipe.  The MPipeServer.exe can be run to\n"
				"   receive string pipe messages.  The pipe name must have a format of the\n"
				"   following:  \\\\.\\pipe\\(Pipe Name)\n"
				"\n"
				,GApplicationName,GApplicationVersion);
	}


