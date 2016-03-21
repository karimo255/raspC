"#Ras9C"

Ras9C is a monitoring tool for the Raspberry Pi based on websockets

#features
	-realtime
	-lightweight
	-cross-over client support (web brwoser)
	
	
#download

	git clone https://github.com/karimo255/raspC

#insatll 

	cd raspC
	sudo ./configure
	sudo make
	sudo make install
	sudo make clean

	after installation type on a browser [your-ip or hostname]:7681 

	user/pass
		user : admin
		pass : admin

#paths description

| Path | Description |
|------|-------------|
| /| Display global Information about system |
| /home.html  | like / |
| /details.html | Display information about hardware,storage,network... |
| /gpio.html | Display the status and modifing the gpio-pins  |
| /services.html  | Display and start/stop all installed daemons |		
| /auth.html  | It be will automaticly called if no session running (not logged in) |	

#uninstall

	sudo make uninstall


#start/stop server

	-start
		sudo service mein_server start
	or
		sudo /etc/init.d/mein_server start

	-stop
        sudo service mein_server stop
        or
        sudo /etc/init.d/mein_server stop

	-status
        sudo service mein_server status
        or
        sudo /etc/init.d/mein_server status

