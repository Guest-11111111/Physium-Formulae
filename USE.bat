@echo off
setlocal enabledelayedexpansion

:: ##########################################################################
:: ##                           CONFIGURATION                            ##
:: ##########################################################################

set "APP_NAME=PhysForm"

:: Directories
set "SOURCEDIR=src"
set "BUILDDIR=obj"
set "OUTDIR=output"

:: Output filenames
set "APP_ELF=%OUTDIR%/%APP_NAME%.elf"
set "APP_BIN=%OUTDIR%/%APP_NAME%.bin"

:: ##########################################################################
:: ##                             TOOLCHAIN                              ##
:: ##########################################################################

:: Define toolchain executables (assuming they are in your system's PATH)
:: If your tools are not in PATH, set full paths here, e.g.:
:: set "AS=C:\toolchain\bin\sh4aeb-elf-gcc.exe"
set "AS=sh4aeb-elf-gcc"
set "CC=sh4aeb-elf-gcc"
set "CXX=sh4aeb-elf-g++"
set "LD=sh4aeb-elf-g++"
set "READELF=sh4aeb-elf-readelf"
set "OBJCOPY=sh4aeb-elf-objcopy"

:: Check if toolchain executables exist
for %%X in ("%AS%", "%CC%", "%CXX%", "%LD%", "%READELF%", "%OBJCOPY%") do (
    where %%~X >nul 2>nul
    if errorlevel 1 (
        echo Error: Toolchain executable "%%~X" not found.
        echo Please ensure your cross-compiler tools are in your system PATH,
        echo or update the script with their full paths.
        exit /b 1
    )
)

:: ##########################################################################
:: ##                             FLAGS                                  ##
:: ##########################################################################

set "APPNAME_DEFINE=-DAPPNAME_STRING=\"%APP_NAME%\""
set "COMMON_FLAGS=-flto -ffunction-sections -fdata-sections -ffreestanding -fshort-wchar -O2"
set "INCLUDES=-I "%SDK_DIR%/include/""
set "WARNINGS=-Wall -Wextra"

set "AS_FLAGS=%APPNAME_DEFINE%"
set "CC_FLAGS=%COMMON_FLAGS% %INCLUDES% %WARNINGS%"
set "CXX_FLAGS=-fno-exceptions -fno-rtti -Wno-write-strings %COMMON_FLAGS% %INCLUDES% %WARNINGS%"
set "LD_FLAGS=-Wl,--gc-sections -Wno-undef"

:: Initialize lists for source and object files
set "AS_SOURCES="
set "CC_SOURCES="
set "CXX_SOURCES="
set "ALL_OBJECTS="

:: ##########################################################################
:: ##                           FUNCTIONS                                ##
:: ##########################################################################

:: Function to create directory if it doesn't exist (like mkdir -p)
:mkdir_p
    if not exist "%~1" (
        echo Creating directory: "%~1"
        mkdir "%~1"
        if errorlevel 1 (
            echo Error: Failed to create directory "%~1". Aborting.
            exit /b 1
        )
    )
    exit /b 0

:: Function to compile Assembly files
:compile_asm
    set "SOURCE_FILE=%~1"
    set "RELATIVE_PATH="
    :: Extract relative path from SOURCEDIR to source file
    for /f "delims=" %%i in ("!SOURCE_FILE:%SOURCEDIR%\=!") do set "RELATIVE_PATH=%%i"
    set "OBJECT_FILE=%BUILDDIR%\!RELATIVE_PATH:.S=.o!"

    call :mkdir_p "%BUILDDIR%\!RELATIVE_PATH:~0,-%~nx1%"

    echo Compiling ASM: "%SOURCE_FILE%" to "!OBJECT_FILE!"...
    "%AS%" -c "%SOURCE_FILE%" -o "!OBJECT_FILE!" %AS_FLAGS%
    if errorlevel 1 (
        echo Error: ASM compilation failed for "%SOURCE_FILE%".
        exit /b 1
    )
    set "ALL_OBJECTS=!ALL_OBJECTS! "!OBJECT_FILE!""
    exit /b 0

:: Function to compile C files
:compile_c
    set "SOURCE_FILE=%~1"
    set "RELATIVE_PATH="
    :: Extract relative path from SOURCEDIR to source file
    for /f "delims=" %%i in ("!SOURCE_FILE:%SOURCEDIR%\=!") do set "RELATIVE_PATH=%%i"
    set "OBJECT_FILE=%BUILDDIR%\!RELATIVE_PATH:.c=.o!"

    call :mkdir_p "%BUILDDIR%\!RELATIVE_PATH:~0,-%~nx1%"

    echo Compiling C: "%SOURCE_FILE%" to "!OBJECT_FILE!"...
    "%CC%" -c "%SOURCE_FILE%" -o "!OBJECT_FILE!" %CC_FLAGS%
    if errorlevel 1 (
        echo Error: C compilation failed for "%SOURCE_FILE%".
        exit /b 1
    )
    set "ALL_OBJECTS=!ALL_OBJECTS! "!OBJECT_FILE!""
    exit /b 0

:: Function to compile C++ files
:compile_cpp
    set "SOURCE_FILE=%~1"
    set "RELATIVE_PATH="
    :: Extract relative path from SOURCEDIR to source file
    for /f "delims=" %%i in ("!SOURCE_FILE:%SOURCEDIR%\=!") do set "RELATIVE_PATH=%%i"
    set "OBJECT_FILE=%BUILDDIR%\!RELATIVE_PATH:.cpp=.o!"

    call :mkdir_p "%BUILDDIR%\!RELATIVE_PATH:~0,-%~nx1%"

    echo Compiling C++: "%SOURCE_FILE%" to "!OBJECT_FILE!"...
    "%CXX%" -c "%SOURCE_FILE%" -o "!OBJECT_FILE!" %CXX_FLAGS%
    if errorlevel 1 (
        echo Error: C++ compilation failed for "%SOURCE_FILE%".
        exit /b 1
    )

    :: Check for global constructors (as per Makefile: readelf -S | grep ".ctors")
    echo Checking for global constructors in "!OBJECT_FILE!"...
    "%READELF%" "!OBJECT_FILE!" -S | findstr /R /C:".ctors" >nul 2>nul
    if !errorlevel! equ 0 (
        echo ERROR: Global constructors aren't supported. Deleting "!OBJECT_FILE!".
        del "!OBJECT_FILE!"
        exit /b 1
    ) else (
        echo No global constructors found.
    )

    set "ALL_OBJECTS=!ALL_OBJECTS! "!OBJECT_FILE!""
    exit /b 0

:: Function to link the ELF executable
:link_elf
    echo Linking ELF executable: "%APP_ELF%"...
    call :mkdir_p "%OUTDIR%"

    :: Check if SDK library exists
    if not exist "%SDK_DIR%\libsdk.a" (
        echo Error: You need to build the SDK before using it.
        echo Run make in the SDK directory, and check the README.md in the SDK directory for more information.
        exit /b 1
    )

    "%LD%" -T linker.ld -Wl,-Map "%APP_ELF%.map" -o "%APP_ELF%" %LD_FLAGS% %ALL_OBJECTS% -L"%SDK_DIR%" -lsdk
    if errorlevel 1 (
        echo Error: ELF linking failed.
        exit /b 1
    )
    echo ELF executable created: "%APP_ELF%"
    exit /b 0

:: Function to create the BIN file from ELF
:create_bin
    echo Creating BIN file: "%APP_BIN%"...
    if not exist "%APP_ELF%" (
        echo Error: ELF file "%APP_ELF%" not found. Please build the ELF first.
        exit /b 1
    )
    call :mkdir_p "%OUTDIR%"
    "%OBJCOPY%" --output-target=binary "%APP_ELF%" "%APP_BIN%"
    if errorlevel 1 (
        echo Error: BIN conversion failed.
        exit /b 1
    )
    echo BIN file created: "%APP_BIN%"
    exit /b 0

:: Function to clean build artifacts
:clean_project
    echo Cleaning project...
    if exist "%BUILDDIR%" (
        echo Removing directory: "%BUILDDIR%"
        rmdir /s /q "%BUILDDIR%"
    ) else (
        echo Build directory "%BUILDDIR%" not found.
    )
    if exist "%OUTDIR%" (
        echo Removing directory: "%OUTDIR%"
        rmdir /s /q "%OUTDIR%"
    ) else (
        echo Output directory "%OUTDIR%" not found.
    )
    echo Clean complete.
    exit /b 0

:: Function to collect all source files
:collect_sources
    echo Collecting source files from "%SOURCEDIR%"...
    set "AS_SOURCES="
    set "CC_SOURCES="
    set "CXX_SOURCES="

    if not exist "%SOURCEDIR%" (
        echo Error: Source directory "%SOURCEDIR%" not found.
        exit /b 1
    )

    for /R "%SOURCEDIR%" %%F in (*.S) do (
        echo Found ASM: "%%F"
        set "AS_SOURCES=!AS_SOURCES! "%%F""
    )
    for /R "%SOURCEDIR%" %%F in (*.c) do (
        echo Found C: "%%F"
        set "CC_SOURCES=!CC_SOURCES! "%%F""
    )
    for /R "%SOURCEDIR%" %%F in (*.cpp) do (
        echo Found C++: "%%F"
        set "CXX_SOURCES=!CXX_SOURCES! "%%F""
    )
    if not defined AS_SOURCES if not defined CC_SOURCES if not defined CXX_SOURCES (
        echo Warning: No source files found in "%SOURCEDIR%".
    )
    exit /b 0

:: Function to compile all collected source files
:compile_all_sources
    echo Compiling all source files...
    call :collect_sources || exit /b 1

    if defined AS_SOURCES (
        for %%S in (!AS_SOURCES!) do call :compile_asm %%S || exit /b 1
    )
    if defined CC_SOURCES (
        for %%S in (!CC_SOURCES!) do call :compile_c %%S || exit /b 1
    )
    if defined CXX_SOURCES (
        for %%S in (!CXX_SOURCES!) do call :compile_cpp %%S || exit /b 1
    )
    echo All source files compiled successfully.
    exit /b 0

:: ##########################################################################
:: ##                              MAIN LOGIC                            ##
:: ##########################################################################

:: Validate SDK_DIR environment variable early
if "%SDK_DIR%"=="" (
    echo Error: You need to define the SDK_DIR environment variable, and point it to the sdk/ folder.
    exit /b 1
)
if not exist "%SDK_DIR%" (
    echo Error: SDK_DIR environment variable points to a non-existent directory: "%SDK_DIR%".
    echo Please verify the path.
    exit /b 1
)
echo SDK_DIR is set to: "%SDK_DIR%"

:: Handle command line arguments
if "%1"=="" goto :all_target
if /i "%1"=="bin" goto :bin_target
if /i "%1"=="hhk" goto :hhk_target
if /i "%1"=="all" goto :all_target
if /i "%1"=="clean" goto :clean_target

echo Invalid argument. Usage: %~nx0 [bin|hhk|all|clean]
exit /b 1

:all_target
    echo --- Building 'all' target: ELF and BIN files ---
    call :compile_all_sources || exit /b 1
    call :link_elf || exit /b 1
    call :create_bin || exit /b 1
    echo --- Build 'all' successful! Executable: "%APP_BIN%" ---
    goto :eof

:bin_target
    echo --- Building 'bin' target: only the BIN file ---
    call :compile_all_sources || exit /b 1
    call :link_elf || exit /b 1
    call :create_bin || exit /b 1
    echo --- Build 'bin' successful! Executable: "%APP_BIN%" ---
    goto :eof

:hhk_target
    echo --- Building 'hhk' target: only the ELF file ---
    call :compile_all_sources || exit /b 1
    call :link_elf || exit /b 1
    echo --- Build 'hhk' successful! Executable: "%APP_ELF%" ---
    goto :eof

:clean_target
    echo --- Cleaning project artifacts ---
    call :clean_project
    echo --- Clean complete ---
    goto :eof

:eof
endlocal
