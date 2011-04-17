#include "TitanStableHeader.h"
#include "TiConsoleDebugger.h"
#include "TiException.h"
#include <fcntl.h>
#include <io.h>
#include <Windows.h>

namespace Titan
{

	template<> ConsoleDebugger* Singleton<ConsoleDebugger>::ms_Singleton = 0;

	ConsoleDebugger* ConsoleDebugger::getSingletonPtr()
	{
		return ms_Singleton;
	}
	ConsoleDebugger& ConsoleDebugger::getSingleton()
	{
		assert( ms_Singleton );  return ( *ms_Singleton );
	}
	//-------------------------------------------------------------------------------//
	ConsoleDebugger::ConsoleDebugger()
		:mConsoleEnable(true)
	{
		enableConsole();
	}
	//-------------------------------------------------------------------------------//
	ConsoleDebugger::~ConsoleDebugger()
	{
		disableConsole();
	}
	//-------------------------------------------------------------------------------//
	void ConsoleDebugger::enableConsole()
	{
#if WIN32
		static const WORD MAX_CONSOLE_LINES = 500;
		int hConHandle;
		long lStdHandle;
		CONSOLE_SCREEN_BUFFER_INFO coninfo;
		FILE *fp;
		// allocate a console for this app
		AllocConsole();
		// set the screen buffer to be big enough to let us scroll text
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
		coninfo.dwSize.Y = MAX_CONSOLE_LINES;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),
			coninfo.dwSize);
		// redirect unbuffered STDOUT to the console
		lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		fp = _fdopen( hConHandle, "w" );
		*stdout = *fp;
		setvbuf( stdout, NULL, _IONBF, 0 );
		// redirect unbuffered STDIN to the console
		lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		fp = _fdopen( hConHandle, "r" );
		*stdin = *fp;
		setvbuf( stdin, NULL, _IONBF, 0 );
		// redirect unbuffered STDERR to the console
		lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		fp = _fdopen( hConHandle, "w" );
		*stderr = *fp;
		setvbuf( stderr, NULL, _IONBF, 0 );
		// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
		// point to console as well
		std::ios::sync_with_stdio();
#endif
	}
	//-------------------------------------------------------------------------------//
	void ConsoleDebugger::disableConsole()
	{
		FreeConsole();
	}
	//-------------------------------------------------------------------------------//
	void ConsoleDebugger::outputMessage(const String& message, ConsoleMessageLevel cml, bool outputTime)
	{
		if(mConsoleEnable)
		{
			if(outputTime)
			{
				struct tm *pTime ;
				time_t ctTime; time(&ctTime);
				pTime = localtime(&ctTime );
				std::cout<<std::setw(2) << std::setfill('0') << pTime->tm_hour
					<< ":" << std::setw(2) << std::setfill('0') << pTime->tm_min
					<< ":" << std::setw(2) << std::setfill('0') << pTime->tm_sec
					<< ": ";
			}
			std::cout<< message << std::endl;

		}
	}
	//-------------------------------------------------------------------------------//
	ConsoleDebugger::Stream	ConsoleDebugger::stream(ConsoleMessageLevel cml)
	{
		return Stream(cml);
	}
	
}