video-table-interactive
=======================

A video table interactive in Cinder and C++.

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

Icon Art by VectorLady.com.  http://vectorlady.com/kitchen-icons/
