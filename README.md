<img width="490" alt="Screenshot 2025-06-26 at 01 04 33" src="https://github.com/user-attachments/assets/a7a343b6-fb3a-43b2-b68b-f8a2b72258ad" />

Building the Plugin

Clone this repository

git clone https://github.com/dogukanunlu/Simple3BandEQ.git
cd Simple3BandEQ

Open the Projucer project

Launch Projucer and open simple3bandeq.jucer.

In the Project Settings panel, ensure VST3 is enabled under Plugin Formats.

Save and export

Click Save Project and Open in IDE (choose Xcode or Visual Studio).

Build the VST3

In your IDE, select the VST3 build configuration (e.g., Release target).

Build the project. The compiled plugin will appear in the Builds folder:

macOS: Builds/MacOSX/build/Release/Simple3BandEQ.vst3

Windows: Builds/Windows/build/Release/Simple3BandEQ.vst3

Install the plugin

Copy the .vst3 file to your system's VST3 directory:

macOS: ~/Library/Audio/Plug-Ins/VST3/

Windows: C:\Program Files\Common Files\VST3\

Launch your DAW

Scan for new plugins and load Simple3BandEQ in your track.
