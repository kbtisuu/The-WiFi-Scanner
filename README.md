# WiFi Scanner

This is a simple C program that uses the WinPcap library to scan for nearby wireless access points and print information about them to the console. It has been tested on Windows 10 using MinGW.

## Requirements

- Windows operating system
- WinPcap library
- C compiler (e.g. MinGW)

## Installation

1. Download and install the WinPcap library from https://www.winpcap.org/install/default.htm

2. Clone or download this repository to your local machine.

3. Compile the program using the following command:

gcc -o wifi-scan wifi-scan.c -lwpcap

This will create an executable file called `wifi-scan.exe`.

## Usage

To run the program, open a command prompt window, navigate to the directory where the `wifi-scan.exe` file is located, and run the command:

wifi-scan.exe


The program will start capturing packets from the network device and printing information about nearby access points to the console.

Note that you may need to run the command prompt as an administrator in order to capture packets from the network device. Also, be aware that scanning for nearby wireless access points without permission may be illegal in some jurisdictions, so make sure you have the necessary permissions before running this program.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
