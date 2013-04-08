video-table-interactive
=======================

A video table interactive in Cinder and C++.

<img src="https://raw.github.com/camb416/video-table-interactive/master/screenshot.jpg" width="500" />

The application consists of four user areas that play videos by receiving keypresses or analog sensor signals from the a Phidgets 8/8/8 InterfaceKit.

Sensor data uses the Phidgets-CinderBlock: https://github.com/camb416/Phidgets-CinderBlock

While more buttons can be added by modifying the plist settings files, the default keymapping is below:

<pre>
TOP-LEFT USER AREA
Q............Back / Switch Language
W............Select Button
E............Skip Button

TOP-RIGHT USER AREA
R............Back / Switch Language
T............Select Button
Y............Skip Button

BOTTOM-LEFT USER AREA
A............Back / Switch Language
S............Select Button
D............Skip Button

BOTTOM-RIGHT USER AREA
F............Back / Switch Language
G............Select Button
H............Skip Button

APPLICATION FUNCTIONS:
~............Toggle Fullscreen
SPACE........Cycle Debug States
</pre>

The application is designed and developed for use with Mac OS X 10.7 Lion. A number of data files are required that should be placed in a folder called "videotable" in ~/Documents/AMNH/.

This folder contains the structure indicated below:

<img src="https://raw.github.com/camb416/video-table-interactive/master/doc/data_folder_structure.png" />

The two plist files are included in the doc folder of this repository, while the jpg and mov files in the assets folder will not be tracked.

<h3>TroubleShooting</h3>
- If the touch sensors are not working properly, try unplugging the audio amp as ground-loop interference can wreak havoc on them, especially considering there is no common ground between the Mac Mini and the Gilderfluke (they both get power over IEC-C7 "shotgun" connectors).

- If the touch sensors are not working at all, check the SETTINGS.plist file and make sure "usesensors" is true. Also confirm that the serial numbers match the boards as labeled in the casework. Note that if there are two specified, they BOTH need to be connected or neither will work.

# Adding another language

- in ~/Documents/AMNH/videotable/settings/SETTINGS.plist:

add the key/value pair:
<pre>
Key  	Type	Value
lang2	String	fr
</pre>
to the languages dictionary.


- duplicate the "en" folder in ~/Documents/AMNH/assets.

- rename the folder to "fr"

- update the assets in the "fr" folder to the alternate language.

The table should now support switching languages by pressing the "back" sensor on the first frame of the interaction.

- make sure to add the "change language" button in the first graphic of the recipe assets.


#Credits

-Software 2012 American Museum of Natural History

-Icon Art by VectorLady.com.  http://vectorlady.com/kitchen-icons/
