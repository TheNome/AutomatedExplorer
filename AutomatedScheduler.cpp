


#include <stdio.h>
#include <sstream>
#include <iostream>
#include <string>
#include <time.h>

#define EST (-5)
#define CDT (-6)
#define MDT (-7)
#define PDT (-8)
#define AKDT (-9)
#define HST (-11)


using namespace std;

int main()
{
	double timeUntilRestart = 86400;
		//The time until the computer restarts.  This gets passed to the shutdown command from Windows as a value in seconds.
		//For now, using 24 hours as the passed time (60*60*24)
	string statusMessage = "Begin shutdown in: ";
		//The status message that will be displayed when the program is run.  Should relate to when the computer will restart.
	string websiteLink = "reddit.com";
		//The website that you wish to automatically open when this programm runs.
	string websiteArgs = "--incognito --start-fullscreen";
		//The arguments for chrome's command line.  This starts the page incognito and fullscreen.
	time_t currentTime = time(&currentTime); 
		//Current time, using to find out the current hour and second so we can find how long we need to add to get to 2300
	struct tm restartTime;
	localtime_s(&restartTime, &currentTime);
		//Struct to set Hour/Min/Sec for what time to start at today
	restartTime.tm_hour = 23;
	restartTime.tm_min = 0;
	restartTime.tm_sec = 0;
		//Set the restart time to 23:00:00
	timeUntilRestart = difftime(mktime(&restartTime), currentTime);
		//Set the time until the restart long to the difference between our current time and the converted and assigned restart time.
		//This runs only if we have already passed 2300 today and have gotten a negative result.
	if (timeUntilRestart < 0)
	{
		restartTime.tm_mday = restartTime.tm_mday + 1;
			//Change the current day for our restart time to the next day
		timeUntilRestart = difftime(mktime(&restartTime), currentTime);
			//Rerun the calculation for how long until the next restart, changing it back to a positive number of seconds.
	}

	stringstream ss;
	stringstream s2;
	ss << "C:\\windows\\system32\\shutdown /r /t " << timeUntilRestart;
		//Parse the shutdown command line with restart and time.  The constant is determined by how long until 2300 that evening.
	s2 << "\"\"C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe\"\"" << " " << websiteLink << " " << websiteArgs;
		//Parse the chrome command and pass it 2 arguments; the website URL and the arguments to launch chrome (incognito and fullscreen)
	system(ss.str().c_str());
		//Run the shutdown command sequence
	system(s2.str().c_str());
		//Run the chrome command
	//cout << statusMessage << timeUntilRestart << " seconds.\n\n";
		//output custom status message

	return 0;
}