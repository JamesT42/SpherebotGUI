SpherebotGUI
============

There is no spoon.

I found that the hostapp included in https://github.com/thunderbug1/Spherebot-Host-GUI was a bit disappointing. 

It required the gcode to be split in one file per layer(color).
But the Inkscape plugin had them in the same gcode file,
with added "M1 (Layer 3 Red)" between each layer.
That seemed to be a good command to use, so this program will prompt You with a dialog to change pen and then continue printing.

Serialsettings are hardcoded in the source.

####Links
http://www.open-electronics.org/spherebot-reloaded-customize-your-xmas/
http://www.thingiverse.com/thing:20398
http://wiki.evilmadscientist.com/The_Original_Egg-Bot_Kit

All-in-one with Arduino code, and Inkscape (in German)
chagne "LANG=de" to "LANG=en" in InkscapePortable/Data/settings/InkscapePortableSettings.ini

https://github.com/thunderbug1/Spherebot-Host-GUI
