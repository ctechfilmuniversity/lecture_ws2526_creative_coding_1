# FINAL PROJECT CC1
# FM Drone Synth (RNBO + C++ + Custom GUI)

## Project Overview

This project is a simple **FM drone synthesizer** originally sketched in Max and exported to C++ using RNBO.  
The exported DSP engine is integrated into a standalone application along with a custom graphical user interface.

The application runs as a standalone executable:

**Executable:**  
`RNBO App Example.exe`

---

## Repository

Full source code is available here:

👉 https://github.com/lenappss/rnbvst/

---

## Project Architecture

The system consists of three main layers:

---

## 1. Synth Design (Max + RNBO)

- The FM drone synth was prototyped inside Max using RNBO objects.
- RNBO was used to export the patch as C++ source code.

**Export output includes:**

- `rnbo_source.cpp`
- RNBO runtime support files

---

## 2. Audio Engine (C++ / RNBO Export)

The core synth logic lives in:


rnbo_source.cpp


This file contains:

- Generated DSP processing code  
- Parameter handling  
- Audio signal flow for the FM drone  

It is automatically produced by RNBO whenever the patch is re-exported.

---

## 3. Custom GUI (C++)

A custom interface was written in C++ to control the drone synth.

**GUI files:**


DroneSynthGUI.cpp
DroneSynthGUI.h


The GUI provides:

- Control for FM parameters  
- Drone sound manipulation  (ADSR)
- Metro  

---

## Folder Structure (Key Parts)


export/
rnbo_source.cpp → RNBO-generated DSP engine

src/
Application source code

ui/
DroneSynthGUI.cpp
DroneSynthGUI.h → Custom GUI implementation

build/
Contains compiled binaries


RNBO exports are placed inside the `export/` directory and integrated into the application during build.

---

## Build System

The project uses:

- CMake for builds  
- RNBO C++ export for DSP  
- A C++ framework for audio and UI  

### Basic Build Steps

1. Export RNBO patch into `/export`
2. Run CMake:


cmake ..


3. Build:


cmake --build .


The compiled executable will appear in:


build/RNBOApp_artefacts/


---

## How It Works (Signal Flow)


Max Patch → RNBO Export → C++ DSP Engine → Application → GUI Controls


1. The FM drone is designed in Max.
2. RNBO converts the patch into C++ DSP code.
3. The application hosts the DSP engine.
4. The GUI sends parameter updates to the synth.

---

## Features

- Simple FM drone synthesis  
- Custom GUI controls  
- Standalone desktop application  
- Separation of DSP and UI logic  

---

## Notes

- Any change in the Max patch requires re-exporting RNBO code.
- GUI modifications do not require RNBO export.
- The executable is intended as a standalone test application.

---

## Possible Future Improvements

- Preset management  
- MIDI support  
- Effects processing  
- Plugin build (VST3/AU)  
- Visual feedback (waveform/spectrum)  

---
