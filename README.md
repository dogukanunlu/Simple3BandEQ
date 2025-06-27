<img width="490" alt="Screenshot 2025-06-26 at 01 04 33" src="https://github.com/user-attachments/assets/a7a343b6-fb3a-43b2-b68b-f8a2b72258ad" />

# Simple3BandEQ VST3 Plugin

A minimal three-band equalizer plugin built with **JUCE**.

## Prerequisites

* **JUCE** (version 6 or later) installed on your system
* **Projucer** (comes with JUCE) for project management
* A C++ compiler and IDE:

  * **macOS:** Xcode
  * **Windows:** Visual Studio 2019 or later

## Building the Plugin

1. **Clone this repository**

   ```bash
   git clone https://github.com/dogukanunlu/Simple3BandEQ.git
   cd Simple3BandEQ
   ```

2. **Open the Projucer project**

   * Launch **Projucer** and open `simple3bandeq.jucer`
   * In the **Project Settings** panel, ensure **VST3** is enabled under **Plugin Formats**

3. **Save and export**

   * Click **Save Project and Open in IDE** (choose **Xcode** or **Visual Studio**)

4. **Build the VST3**

   * In your IDE, select the **Release** configuration with **VST3** enabled
   * Build the project. The compiled plugin will be located in the `Builds` folder:

     * **macOS:**

       ```
       Builds/MacOSX/build/Release/Simple3BandEQ.vst3
       ```
     * **Windows:**

       ```
       Builds/Windows/build/Release/Simple3BandEQ.vst3
       ```

5. **Install the plugin**

   * Copy the `.vst3` file to your system's VST3 directory:

     * **macOS:** `~/Library/Audio/Plug-Ins/VST3/`
     * **Windows:** `C:\Program Files\Common Files\VST3\`

6. **Launch your DAW**

   * Scan for new plugins and load **Simple3BandEQ** on a track

