# AsterixXXL2_GameHook

This Game Hooker is written for the PC game Asterix & Obelix XXL2.

This tool gives you the ability to move you main character to any place you want. Currently movement is only possible on the z axis. Further research of how xyz locations of characters are stored is needed.

The compiled .exe file needs to be placed in the same folder as the game executable. This is because the game's .exe file on execution looks up the file Gamemodule.elb which contains the actual code of the game. It jumps to it and runs it. The reference to this file is hardcoded and expects it to be in the same folder as the executable. So, if you hook on to the game's .exe from a different folder location, the game will not find the Gamemodule.elb file and the game will not boot. You also can't hook onto the Gamemodule.elb process  as acces is denied. (Might need further research).

Your virus scanner might complain when running this application as it is hooking onto an already running process. So be aware.

To be continued.
