# TCC
Time Complexity Calculator



## Setup -- Windows

Commands are for **PowerShell**.
The examples install everything under `C:\dev`; any location works as long as
you use the same paths in step 6.

### 1. Install the base tools

1. **Git:** download and run the installer from
   [git-scm.com/downloads/win](https://git-scm.com/downloads/win). The default
   options are fine.
2. **CMake (3.25 or newer):** download the Windows x64 `.msi` installer from
   [cmake.org/download](https://cmake.org/download/). During installation,
   select **Add CMake to the system PATH**.
3. **Ninja:** download `ninja-win.zip` from
   [github.com/ninja-build/ninja/releases](https://github.com/ninja-build/ninja/releases).
   Ninja is a single `ninja.exe` with no installer. Extract it to `C:\dev\ninja`
   and add that folder to your PATH:

   ```powershell
   mkdir C:\dev\ninja -Force
   Expand-Archive "$env:USERPROFILE\Downloads\ninja-win.zip" -DestinationPath C:\dev\ninja
   [Environment]::SetEnvironmentVariable("Path", [Environment]::GetEnvironmentVariable("Path", "User") + ";C:\dev\ninja", "User")
   ```

   (If you'd rather not change your PATH, skip the last line and instead set
   `CMAKE_MAKE_PROGRAM` to `C:/dev/ninja/ninja.exe` in step 6.)

Close and reopen PowerShell so the PATH changes take effect, then check:

```powershell
git --version
cmake --version   # must be 3.25 or newer
ninja --version
```

### 2. Install the Visual Studio C++ Build Tools

Clang on Windows uses Microsoft's C++ standard library and the Windows SDK, so
these are required even though you won't compile with MSVC.

1. Go to [visualstudio.microsoft.com/downloads](https://visualstudio.microsoft.com/downloads/),
   scroll to **Tools for Visual Studio**, and download **Build Tools for Visual Studio**.
   (If you already have Visual Studio Community/Professional installed, you can
   skip the download and open the **Visual Studio Installer** instead.)
2. Run the installer and select the **Desktop development with C++** workload.
   Keep the default components; they include the MSVC toolset and Windows SDK.
3. Click **Install**. No PATH changes are needed; Clang finds these
   automatically.

> **Optional shortcut:** if you use winget, steps 1 and 2 can instead be done with:
>
> ```powershell
> winget install --id Git.Git -e
> winget install --id Kitware.CMake -e
> winget install --id Ninja-build.Ninja -e
> winget install --id Microsoft.VisualStudio.2022.BuildTools -e --override "--wait --passive --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended"
> ```

### 3. Install LLVM/Clang **with development files**

The regular LLVM installer (`LLVM-x.y.z-win64.exe`) only ships the compiler.
This project links against Clang's libraries, so you need the full package
that includes `lib\cmake\clang`.

1. Go to the [LLVM releases page](https://github.com/llvm/llvm-project/releases/tag/llvmorg-22.1.4)
   and download `clang+llvm-22.1.4-x86_64-pc-windows-msvc.tar.xz`.
2. Extract it and rename the folder to `C:\dev\llvm`:

   ```powershell
   mkdir C:\dev -Force
   tar -xf "$env:USERPROFILE\Downloads\clang+llvm-22.1.4-x86_64-pc-windows-msvc.tar.xz" -C C:\dev
   Rename-Item "C:\dev\clang+llvm-22.1.4-x86_64-pc-windows-msvc" llvm
   ```

3. Confirm these exist:
   - `C:\dev\llvm\bin\clang++.exe`
   - `C:\dev\llvm\lib\cmake\clang\ClangConfig.cmake`

> **Important:** the LLVM package must be a **Release** build using the
> **static** MSVC runtime (`/MT`). That is what this project is configured for;
> a package built differently will fail at link time. Debug builds of TCC are
> not supported for the same reason.

### 4. Install vcpkg and zlib

LLVM's support library depends on zlib, which is provided through vcpkg:

```powershell
git clone https://github.com/microsoft/vcpkg C:\dev\vcpkg
C:\dev\vcpkg\bootstrap-vcpkg.bat
C:\dev\vcpkg\vcpkg install zlib:x64-windows
```

### 5. Clone this repository

```powershell
git clone https://github.com/maddoxreed9175-png/TCC.git C:\dev\TCC
cd C:\dev\TCC
```

### 6. Create your local CMake presets

Machine-specific paths live in `CMakeUserPresets.json`, which is gitignored.
Start from the example:

```powershell
Copy-Item CMakeUserPresets.example.json CMakeUserPresets.json
```

Open `CMakeUserPresets.json` and replace the placeholder paths. With the
locations used above it looks like this (use forward slashes):

```json
"toolchainFile": "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake",
"cacheVariables": {
  "Clang_DIR": "C:/dev/llvm/lib/cmake/clang",
  "LLVM_DIR": "C:/dev/llvm/lib/cmake/llvm",
  "CMAKE_C_COMPILER": "C:/dev/llvm/bin/clang.exe",
  "CMAKE_CXX_COMPILER": "C:/dev/llvm/bin/clang++.exe"
}
```

Setting the compilers explicitly makes sure the build uses the same Clang
version as the libraries, even if another `clang` is on your PATH.

### 7. Configure and build

```powershell
cmake --preset dev-release
cmake --build --preset dev-release
```

The first command only needs to run once (and again after changing
`CMakeUserPresets.json`, using `cmake --preset dev-release --fresh`). After
that, just rerun the build command whenever you change the code.

The program is written to `build\release\tcc.exe`.

## Usage

```powershell
.\build\release\tcc.exe path\to\file.cpp --
```

The trailing `--` tells the tool there is no `compile_commands.json` for the
input file, so default compiler flags are used. Use small, self-contained test
files; files that include third-party headers will produce errors because the
tool doesn't know their include paths.

## Build presets

| Preset | Build type | Output folder |
|---|---|---|
| `dev-release` | Release | `build/release` |
| `dev-relwithdebinfo` | Release with debug symbols | `build/relwithdebinfo` |

`dev-*` presets come from your `CMakeUserPresets.json` and inherit the shared
settings (Ninja, Clang, C++17, static runtime) from `CMakePresets.json`.

## Editor support

- **clangd (Zed, VS Code, Neovim, ...):** the committed `.clangd` file points at
  `build/release/compile_commands.json`, so code completion works after you
  configure the `dev-release` preset once.
- **VS Code (CMake Tools), CLion, Visual Studio 2022:** these read the presets
  automatically; select `dev-release` in the IDE.

## Troubleshooting

| Problem | Fix |
|---|---|
| `Could not find a package configuration file provided by "Clang"` | `Clang_DIR` in `CMakeUserPresets.json` is wrong, or you installed the compiler-only LLVM package (see step 3). |
| `no template named 'optional' in namespace 'std'` | C++17 isn't enabled; make sure your presets inherit from `clang-release`. |
| `Could NOT find ZLIB` or unresolved `compress2`/`uncompress` symbols | vcpkg toolchain path is wrong, or zlib isn't installed (step 4). |
| Linker errors mentioning `RuntimeLibrary` or `_ITERATOR_DEBUG_LEVEL` mismatch | You're building Debug, or your LLVM package wasn't built with the static Release runtime. |
| `CMAKE_MAKE_PROGRAM is not set` / Ninja not found | Reopen PowerShell after installing Ninja, or set `CMAKE_MAKE_PROGRAM` to the full path of `ninja.exe` in `CMakeUserPresets.json`. |
| Settings changes have no effect | Reconfigure from scratch: `cmake --preset dev-release --fresh`. |
