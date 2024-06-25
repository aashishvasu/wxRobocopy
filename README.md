# wxRobocopy

GUI for Microsoft's [robocopy](https://learn.microsoft.com/en-us/windows-server/administration/windows-commands/robocopy), written in C++ with wxWidgets. Robocopy can speed up copying/syncing/moving by a lot over regular copy operations.

It's meant for people are not familiar or comfortable with the command line, and only exposes the most used functionality of robocopy to the UI.

## Features

- **Intuitive UI**: User-friendly interface for easy configuration of robocopy commands.
- **Real-time Output Monitoring**: Monitor the output of robocopy operations in real time.
- **Customizable Options**: Various flags and options to tailor robocopy operations to specific needs.

## Usage

1. Download the [latest release](https://github.com/aashishvasu/wxRobocopy/releases/latest).
2. Launch `wxRobocopy.exe`.
3. Select source and target folders.
4. Configure any necessary options such as copy type, filters, flags, CPU threads, and logging preferences. The default options work just fine as well!
5. Click on "Run Robocopy" to start the operation.
6. Monitor progress in the output window.

## Development

### Prerequisites

- **Windows** operating system
- **CMake** 3.10 or higher
- **wxWidgets** library
- **Git**

### Building wxRobocopy

To build wxRobocopy, follow these steps:

1. Clone the repository:

```sh
git clone https://github.com/aashishvasu/wxRobocopy.git
cd wxRobocopy
```

1. Run the provided PowerShell script to build both x64 and Win32 versions:

```ps
./build_release.ps1
```

### Running wxRobocopy

After building, you can find the executables in the `Binaries` directory under `x64` and `Win32` folders.

1. Navigate to the appropriate directory depending on your architecture (e.g., `Binaries/x64/wxRobocopy`).
2. Run `wxRobocopy.exe`.

### Packaging wxRobocopy

To package the application into zip files for distribution:

1. Ensure you have built both x64 and Win32 versions as described above.
2. Run the packaging script:

```ps
./package_release.ps1
```

This will create zip files named like `wxRobocopy-v1.0-x64.zip` and `wxRobocopy-v1.0-Win32.zip` in the project root directory.

## Contributing

Contributions are welcome! Please fork this repository and submit pull requests. Ensure your changes are against the [dev](/aashishvasu/wxRobocopy/tree/dev) branch.

## License

This project is licensed under the Creative Commons Attribution-NonCommercial (CC BY-NC) license.
