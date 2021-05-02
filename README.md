
# Tracker

TODO

## Setup

Install latest version of [Arduino](https://www.arduino.cc/en/software).  
Download [arduino-cli](https://github.com/arduino/arduino-cli/releases) and make sure that it can be run at the base of the project folder.  
Install Arduino extension by Microsoft for VS Code.  
Add this line to **settings.json** (ctrl+p Preferences: Open settings (JSON)):  
"arduino.additionalUrls": "https://dl.espressif.com/dl/package_esp32_index.json"  
Open **Board Manger** (ctrl+p Arduino: Board Manager)  
From **Board Manager** install esp32 package.  
Initialize the Arduino extension from (ctrl-p Arduino: Initialize) and select ESP DEV board.  
Try to run program. It should now have created **c_cpp_properties.json**.  

## Compiling

To compile **box** or **tracker** run compile.sh \<box|tracker> \<port>
