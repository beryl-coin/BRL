
Debian
====================
This directory contains files used to package beryld/beryl-qt
for Debian-based Linux systems. If you compile beryld/beryl-qt yourself, there are some useful files here.

## beryl: URI support ##


beryl-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install beryl-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your beryl-qt binary to `/usr/bin`
and the `../../share/pixmaps/beryl128.png` to `/usr/share/pixmaps`

beryl-qt.protocol (KDE)

