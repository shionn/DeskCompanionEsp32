#!/bin/bash

setShortCut() {
	echo "add $1 $2 $3 $4" 
	
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom$1/ name "$2"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom$1/ command "$3"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom$1/ binding "$4"

}

setShortCut 0 'Homer' 'firefox http://homer/' '<Control>F0'
setShortCut 1 'Firefox' 'firefox' '<Control>F1'
setShortCut 2 'TODO' '' '<Control>F2'
setShortCut 3 'Discord' 'discord' '<Control>F3'

setShortCut 4 'Terminal' 'x-terminal-emulator' '<Control>F4'
setShortCut 5 'TODO' '' '<Control>F5'
setShortCut 6 'Eclmipse' 'eclipse' '<Control>F6'
setShortCut 7 'VsCode' 'code' '<Control>F7'

setShortCut 8 'TODO' '' '<Control>F8'
setShortCut 9 'TODO' '' '<Control>F9'
setShortCut 10 'TODO' '' '<Control>F10'
setShortCut 11 'TODO' '' '<Control>F11'

setShortCut 12 'Openscad' 'openscad' '<Control>F12'
setShortCut 13 'Cura' 'cura' '<Control>F13'
setShortCut 14 'TODO' '' '<Control>F14'
setShortCut 15 'Gimp' 'gimp' '<Control>F15'

setShortCut 16 'Steam' 'steam' '<Control>F16'
setShortCut 17 'Heroic' 'heroic' '<Control>F17'
setShortCut 18 'Lutric' 'lutric' '<Control>F18'
setShortCut 19 'Minecraft' 'minecraft-launcher' '<Control>F19'
