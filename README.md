# Peapod_Project

-------------------------------------------------------------------------------------------------------------------------------
SETUP OF PROGRAMMING ENVIRONMENT (Arduino IDE for ESP8266)

    https://learn.adafruit.com/adafruit-huzzah-esp8266-breakout/using-arduino-ide

1. Install Arduino ide using sudo dnf install arduino
2. Once Arduino has been installed go to File then preferences and enter http://arduino.esp8266.com/stable/package_esp8266com_index.json in the Additional Boards Manager URLs section
3. Go to Tools then Board and then using the board manager install the corresponding file for the ESP8266
4. Now that all the necessary tools for programming the ESP8266 are installed select the HUZZAH board and leave all the other settings as default
5. Connect the FTDI cable to the board and make sure RX on the cable goes to TX on the board and the TX on the cable goes to RX

-------------------------------------------------------------------------------------------------------------------------------
INSTALL APACHE

1. Install Apache
    - dnf install httpd -y
2. Ensure httpd service starts at boot
    - systemctl enable httpd
3. Start httpd service
    - systemctl start httpd

SETUP OF MYSQL DATABASE
1. Ensure existing packages are updated
    - dnf -y update
2. Install MariaDB
    - dnf install mariadb mariadb-server -y
3. Ensure MySQL/ Mariadb starts at boot
    - systemctl enable mariadb
4. Start MySQL/ Mariadb
    - systemctl start mariadb
5. Set root password
    - mysql_secure_installation

-------------------------------------------------------------------------------------------------------------------------------
INSTALL PHP

1. Install PHP
    - dnf install php -y
2. Install PHP modules
    - dnf install php-mysql -y
3. Install phpMyAdmin
    - dnf install phpmyadmin -y
4. Configure phpMyAdmin
    - Edit Apache Virtual Host File
        - vim /etc/httpd/conf.d/phpMyAdmin.conf
    - Change the following 4 instances of “127.0.0.1” to your IP address in the file 
        - Require ip 127.0.0.1
        - Allow from 127.0.0.1
        - Require ip 127.0.0.1
        - Allow from 127.0.0.1
    - Save and exit 
        - :wq
5. Restart Apache
    - systemctl restart httpd
6. Access login page by entering the following into your address bar
    - localhost/phpMyAdmin

-------------------------------------------------------------------------------------------------------------------------------
INSTALL FLASK
1. Installation for Python 2
    - dnf install python-flask
