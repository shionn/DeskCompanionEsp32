#!/bin/bash

setShortCut() {
	echo "add $1 $2 $3 $4" 
	
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom$1/ name "$2"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom$1/ command "$3"
	gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom$1/ binding "$4"

}

gsettings set org.gnome.settings-daemon.plugins.media-keys custom-keybindings []

setShortCut 0 'Homer' 'firefox http://homer/' '<Control>F1'
setShortCut 1 'Firefox' 'firefox --new-tab "about:blank"' '<Control>F2'
setShortCut 2 'TODO' '' '<Control>F3'
setShortCut 3 'Discord' 'discord' '<Control>F4'

setShortCut 4 'Terminal' 'x-terminal-emulator' '<Control>F5'
setShortCut 5 'TODO' '' '<Control>F6'
setShortCut 6 'Eclipse' 'eclipse' '<Control>F7'
setShortCut 7 'VsCode' 'code' '<Control>F8'

setShortCut 8 'TODO' '' '<Control>F9'
setShortCut 9 'TODO' '' '<Control>F10'
setShortCut 10 'TODO' '' '<Control>F11'
setShortCut 11 'TODO' '' '<Control>F12'

setShortCut 12 'Openscad' 'openscad' '<Control>Tools'
setShortCut 13 'Cura' 'cura' '<Control>Launch5'
setShortCut 14 'TODO' '' '<Control>Launch6'
setShortCut 15 'Gimp' 'gimp' '<Control>Launch7'

setShortCut 16 'Steam' 'steam' '<Control>Launch8'
setShortCut 17 'Heroic' 'heroic' '<Control>Launch9'
setShortCut 18 'Lutris' 'lutris' '<Control>AudioMicMute'
setShortCut 19 'Minecraft' 'minecraft-launcher' '<Control>TouchpadToggle'

gsettings set org.gnome.settings-daemon.plugins.media-keys custom-keybindings "[\
	'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom0/',\
	'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom1/',\
	'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom2/',\
	'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom3/',\
	'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom4/',\
	'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom5/',\
	'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom6/',\
	'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom7/',\
	'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom8/',\
	'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom9/',\
	'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom10/',\
	'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom11/',\
	'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom12/',\
	'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom13/',\
	'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom14/',\
	'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom15/',\
	'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom16/',\
	'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom17/',\
	'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom18/',\
	'/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom19/'\
	]"
