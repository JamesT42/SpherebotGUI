SpherebotGUI
============

There is no spoon.

I found that the hostapp included in https://github.com/thunderbug1/Spherebot-Host-GUI was a bit disappointing. 

It required the gcode to be split in one file per layer(color).
But the Inkscape plugin had them in the same gcode file,
with added "M1 (Layer 3 Red)" between each layer.
That seemed to be a good command to use, so this program will prompt You with a dialog to change pen and then continue printing.


Serialsettings are hardcoded in the source.
Baudrate    256000
Stopbits    1
Flowcontrol None
Databits    8
Parity      None

Precompiled for Windows x86 with MSVC2010
https://dl.dropboxusercontent.com/u/748397/SpherebotGui/SpherebotGUI.zip


####Links
http://www.open-electronics.org/spherebot-reloaded-customize-your-xmas/
http://www.thingiverse.com/thing:20398
http://wiki.evilmadscientist.com/The_Original_Egg-Bot_Kit

All-in-one with Arduino code, and Inkscape (in German)
change "LANG=de" to "LANG=en" in InkscapePortable/Data/settings/InkscapePortableSettings.ini

https://github.com/thunderbug1/Spherebot-Host-GUI
