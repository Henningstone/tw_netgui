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

The NetGUI project is a universal and easy to embed modification for Teeworlds. It gives the ability to the server to send custom GUIs to the client which build upon the existing menus.

You can implement it into your own mod by simply adding it's files and a few lines of copy-paste code to the game. Remember to replace ```datasrc/network.py``` with my one, or, if you also edited it, add the labelled lines at the bottom to the file.

Both, client and server, need to support this feature. To play on servers which use it, you can use the client provided within this repo.


Licence: You are allowed to embed this into your mod (non-commercial aswell as commercial) without asking, as long as you give credit to me. You are not allowed to re-distribute the code of this mod (NetGUI client and server) as if it were yours, no matter if it is modified or not! "As if it were yours" means, that you are not allowed to remove my name from the files I added. Redistributing the GUIs you make is of cause up to your mind and I don't care about it.
If you want somebody to have the entire source code, give him the link to my github repo (Henningstone/tw_netgui). If you want to participate in NetGUI, you are welcome to make a pull-request. Thanks.
