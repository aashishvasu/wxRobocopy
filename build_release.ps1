# Define the project root directory
$projectRoot = Split-Path -Parent $MyInvocation.MyCommand.Path

# Define build directories
$buildDirX64 = Join-Path $projectRoot "build\x64"
$buildDirWin32 = Join-Path $projectRoot "build\Win32"

# Create build directories if they don't exist
if (-Not (Test-Path $buildDirX64)) {
    New-Item -ItemType Directory -Path $buildDirX64
}
if (-Not (Test-Path $buildDirWin32)) {
    New-Item -ItemType Directory -Path $buildDirWin32
}

# Function to configure and build
function ConfigureAndBuild($buildDir, $architecture)
{
    Set-Location -Path $buildDir
    & cmake -A $architecture $projectRoot
    & cmake --build . --config Release
}

# Configure and build x64
ConfigureAndBuild $buildDirX64 "x64"

# Configure and build Win32
ConfigureAndBuild $buildDirWin32 "Win32"

# Return to the original location
Set-Location -Path $projectRoot
