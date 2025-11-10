# Personal Typing Analytics Dashboard

A Windows-based keyboard event monitoring application for educational purposes, designed to capture and analyze typing patterns system-wide. This project demonstrates OS-level event handling, Windows API usage, and system programming concepts.

## ⚠️ Important Disclaimer

**This software is for educational and personal use only.** It is designed for:
- Academic learning (Operating Systems course project)
- Personal productivity analytics on your own machine
- Understanding how system-level event monitoring works

**Do NOT use this software to:**
- Monitor other people's computers without explicit consent
- Violate privacy laws or regulations
- Conduct unauthorized surveillance

The authors are not responsible for misuse of this software.

## Features

- **System-wide keyboard monitoring**: Captures keyboard events across all Windows applications
- **Real-time logging**: Writes keystrokes to a local log file (`keylog.txt`)
- **Key mapping**: Properly converts virtual key codes to readable characters
- **Special key handling**: Logs special keys (Backspace, Tab, Shift, Ctrl, Arrow keys, etc.) with readable tags
- **Modular design**: Separate functions for key processing, file I/O, and network communication

## Technical Details

### Technologies Used
- **Language**: C
- **Platform**: Windows (Win32 API)
- **Libraries**: 
  - Windows API (`windows.h`)
  - Winsock2 (`winsock2.h`, `ws2tcpip.h`) for network functionality
  - Standard C libraries (`stdio.h`, `stdlib.h`, `string.h`)

### Key Windows APIs
- `GetAsyncKeyState()` - Detects key presses system-wide
- `ToAscii()` / `MapVirtualKey()` - Converts virtual key codes to characters
- `GetKeyboardState()` - Retrieves keyboard modifier states (Shift, Ctrl, etc.)

## Building the Project

### Prerequisites
- GCC compiler (MinGW on Windows)
- Windows operating system
- Administrator privileges (optional, for advanced features)

### Compilation

**Option 1: Using the build script (Recommended)**
```bash
.\build.bat
```

**Option 2: Manual compilation**
```bash
gcc -Wall -Wextra -o in_app_input_logger.exe in_app_input_logger.c -lws2_32
```

**Compiler Flags Explained:**
- `-Wall`: Enables common compiler warnings
- `-Wextra`: Enables additional warnings for better code quality
- `-lws2_32`: Links the Winsock2 library for network functionality

## Usage

### Basic Usage

1. **Compile the project** (see Building section above)

2. **Run the executable:**
   ```bash
   .\in_app_input_logger.exe
   ```

3. **The program will:**
   - Display: "Keylogger started. Press ESC to exit."
   - Display: "Logging to keylog.txt"
   - Start monitoring keyboard input system-wide
   - Write captured keystrokes to `keylog.txt` in real-time

4. **To exit:**
   - Press the **ESC** key

### Output Format

Keystrokes are logged to `keylog.txt` with the following format:
- Regular characters: Logged as-is (a-z, A-Z, 0-9)
- Special keys: Logged with tags:
  - `[B]` - Backspace
  - `[T]` - Tab
  - `[S]` - Shift
  - `[C]` - Control
  - `[ES]` - Escape
  - `[L]` - Left Arrow
  - `[R]` - Right Arrow
  - `[U]` - Up Arrow
  - `[D]` - Down Arrow
  - `[H]` - Home
  - `[EN]` - End
  - `[KEY:xxx]` - Unrecognized keys (logged with virtual key code)

## Project Structure

```
keylog/
├── in_app_input_logger.c    # Main source code
├── in_app_input_logger.exe  # Compiled executable
├── keylog.txt               # Output log file
├── build.bat                # Build script
└── README.md                # This file
```

## Code Architecture

### Main Components

1. **`main()`**: 
   - Initializes the program
   - Opens log file
   - Main event loop for key detection
   - Handles program exit

2. **`take_n_run()`**: 
   - Processes virtual key codes
   - Converts keys to readable format
   - Handles special keys and character conversion

3. **`send_mail()`**: 
   - SMTP email functionality (currently disabled in debug mode)
   - Can be enabled for remote logging

4. **`get_len()`**: 
   - Utility function for string length calculation

5. **`hideConsole()`**: 
   - Hides console window (disabled in debug mode)

6. **`regApp()`**: 
   - Registry manipulation for startup persistence (disabled in debug mode)

7. **`protectProcess()`**: 
   - Process protection mechanisms (disabled in debug mode)

## Configuration

### Debug Mode (Current)
The program is currently configured for debugging:
- Console window visible
- Logging to local file (`keylog.txt`)
- Registry/startup features disabled
- Process protection disabled

### Production Mode
To enable advanced features, uncomment the following in `main()`:
```c
regApp();        // Register in Windows startup
protectProcess(); // Protect process from termination
hideConsole();    // Hide console window
```

**Note:** These features require administrator privileges.

## Educational Objectives

This project demonstrates:
- **OS Event Handling**: How operating systems handle keyboard input events
- **Windows Hooks**: System-wide event monitoring using Windows API
- **Low-level Programming**: Direct interaction with OS APIs
- **System Programming**: Understanding privilege levels and system access
- **Network Programming**: SMTP protocol implementation (optional)

## Limitations

- **Windows Only**: Designed specifically for Windows OS
- **No GUI**: Command-line interface only
- **Basic Key Mapping**: Some special characters may not be perfectly mapped
- **No Encryption**: Log file is stored in plain text

## Troubleshooting

### Compilation Errors

**Error: "undefined reference to `get_len`"**
- Solution: Ensure the function is not declared as `inline` or is properly defined

**Error: "Permission denied" when compiling**
- Solution: Close any running instances of the program, then recompile

**Error: Missing winsock2.h**
- Solution: Ensure you're using MinGW or a Windows-compatible GCC distribution

### Runtime Issues

**Program exits immediately**
- Check if `keylog.txt` is writable in the current directory
- Ensure you have proper file permissions

**No keys being logged**
- Verify the program is running (check Task Manager)
- Check if `keylog.txt` is being updated
- Ensure you're typing in a window that has focus

## Security Considerations

- **Local Storage Only**: By default, logs are stored locally
- **No Network Transmission**: Email functionality is disabled in debug mode
- **Plain Text Logs**: Log files are not encrypted - handle with care
- **Administrator Rights**: Advanced features require elevated privileges

## Future Enhancements

Potential improvements for the project:
- [ ] Add encryption for log files
- [ ] Implement GUI dashboard for analytics
- [ ] Add typing speed (WPM) calculation
- [ ] Implement pattern analysis (typing rhythm, error rate)
- [ ] Add data visualization features
- [ ] Cross-platform support (Linux/macOS)

## License

This project is for educational purposes only. Use responsibly and in accordance with applicable laws and regulations.

## Contributing

This is an academic project. For educational discussions or improvements, please ensure all contributions maintain the educational and ethical use focus of the project.

## References

- [Windows API Documentation](https://docs.microsoft.com/en-us/windows/win32/api/)
- [GetAsyncKeyState Function](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate)
- [Virtual Key Codes](https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes)

---

**Last Updated**: 2025
**Version**: 1.0
**Author**: Operating Systems Course Project

