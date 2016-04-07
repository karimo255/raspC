# Description

RaspC is a monitoring tool for the Raspberry Pi based on websockets

# features
	-realtime ( websockets ) 
	-lightweight
	-cross-over client support (web brwoser)
	-no webserver needed	
	
# Screenshots
####Home
![Home](img/home.png?raw=true "Optional Title")
####Details
![Details](img/details.png?raw=true "Optional Title")
####Services
![Services](img/daemons.png?raw=true "Optional Title")
####GPIO
![GPIO](img/gpio.png?raw=true "Optional Title")
####Auth
![Auth](img/auth.png?raw=true "Optional Title")

# todo
	-doc

# download
	git clone https://github.com/karimo255/raspC

# insatll 

	cd raspC
	sudo ./configure
	sudo make
	sudo make install
	sudo make clean 

	after installation type on a browser [your-ip or hostname]:7681 

	user/pass
		user : admin
		pass : admin

# configuration 
	
	 Configuration file is /etc/raspC/config.json
	 
	 You can edit :
	   - the GPIO-pins Directions ( input or output) 
	   - Ip-whiteist ( accepted IPs)
	   
# paths description

| Path | Description |
|------|-------------|
| /| Display global Information about system |
| /home.html  | like / |
| /details.html | Display information about hardware,storage,network... |
| /gpio.html | Display the status and modifing the gpio-pins  |
| /services.html  | Display and start/stop all installed daemons |		
| /auth.html  | It be will automaticly called if no session running (not logged in) |	

# uninstall

	sudo make uninstall


# start/stop server

	-start
		sudo service raspC start
		or
		sudo /etc/init.d/raspC start

	-stop
        sudo service raspC stop
        or
        sudo /etc/init.d/raspC stop

	-force-reload
        sudo service raspC force-reload
        or
        sudo /etc/init.d/raspC force-reload
        or
        sudo kill -HUP `pgrep raspC`

	-restart
        sudo service raspC restart
        or
        sudo /etc/init.d/raspC restart

	-status
        sudo service raspC status
        or
        sudo /etc/init.d/raspC status
