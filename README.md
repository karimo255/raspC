"# Ras9C"

Ras9C is a monitoring tool for the Raspberry Pi

#features
	
	
#download

git clone https://github.com/karimo255/raspC

#insatll 

	cd raspC
	sudo ./configure
	sudo make
	sudo make install
	sudo make clean

	after installation type on a browser [your-ip]:7681

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

