Teeworlds
=========

A retro multiplayer shooter
---------------------------

Teeworlds is a free online multiplayer game, available for all major
operating systems. Battle with up to 16 players in a variety of game
modes, including Team Deathmatch and Capture The Flag. You can even
design your own maps!

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software. See license.txt for full license
text including copyright information.

Please visit https://www.teeworlds.com/ for up-to-date information about
the game, including new versions, custom maps and much more.

Originally written by Magnus Auvinen.


---------------------------

##NetGUI Modification
#####by Henritees

The NetGUI project is a universal and easy to implement modification for Teeworlds. It gives the ability to the server to send custom GUIs to the client which build upon the existing menus.

You can embed it into your own mod by simply adding it's files and a few lines of copy-paste code to the game. Remember to replace ```datasrc/network.py``` with my one, or, if you also edited it, add the labelled lines at the bottom to the file.

Both, client and server, need to support this feature. To play on servers which use it, you can use the client provided within this repo.


Licence: You are free to use this in your mod (non-commercial aswell as commercial) without asking, as long as you give credit to me. Thanks.
