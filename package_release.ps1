# Define the project root directory
$projectRoot = Split-Path -Parent $MyInvocation.MyCommand.Path

# Get the project name from the CMakeLists.txt
$cmakeListsPath = Join-Path $projectRoot "CMakeLists.txt"
$projectName = Select-String -Path $cmakeListsPath -Pattern "^project\((.*?)\)" | ForEach-Object { $_.Matches[0].Groups[1].Value }

# Get the version number from git
$version = git -C $projectRoot describe --tags --abbrev=0

# Define the folders to package
$architectures = @("x64", "Win32")
$baseFolderToPackage = Join-Path $projectRoot "Binaries"

foreach ($arch in $architectures) {
    $folderToPackage = Join-Path $baseFolderToPackage $arch
    $folderToPackage = Join-Path $folderToPackage $projectName

    # Define the output zip file name
    $zipFile = Join-Path $projectRoot "$projectName-$version-$arch.zip"

    # Check if the folder to package exists
    if (-Not (Test-Path $folderToPackage)) {
        Write-Host "The folder '$folderToPackage' does not exist."
        continue
    }

    # Create the zip file
    Compress-Archive -Path "$folderToPackage\*" -DestinationPath $zipFile

    # Check if the zip file was created
    if (Test-Path $zipFile) {
        Write-Host "Successfully created '$zipFile'"
    } else {
        Write-Host "Failed to create '$zipFile'"
    }
}
