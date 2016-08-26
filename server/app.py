'''
title           : app.py

description     : The following code creates a Flask web server which
                  handles POST requests sent by the PHP form in the 
                  first route ('/'). The second route ('/echo') then  
                  commits the data to a MySQL database. 

author          : Leslie Xin 

date            : August 2016

python version  : 2.7.12  
=============================================================================='''

from flask import Flask, request, render_template, jsonify
import MySQLdb
from datetime import datetime
import MySQLdb

# Create Flask app
app = Flask(__name__)

# Connecting to MySQL database
db = MySQLdb.connect("localhost","root","lxin2016","test")
cursor = db.cursor()

# Selecting table
sql = "SELECT * FROM peapod"
cursor.execute(sql)

# Finding the real time using python's datetime library
compile_hour = datetime.now().hour;
compile_minute = datetime.now().minute;
time = (compile_hour*100) + compile_minute
print "Compile time: ", time

# Route returns a form which sends a POST request using user input
@app.route("/")
def hello():
	return render_template('echoform3.php')

# Route inserts the data into the MySQL database 
# Then the queried data is displayed in the web page in json format
@app.route("/echo", methods=['GET','POST'])
def echo():
	input_ = request.form['values']
	data = jsonify(data=cursor.fetchall())
	cursor.execute("INSERT INTO peapod (Time, MAC_Address, Signal_Strength) VALUES (%s,%s,%s)", (time, input_, time))
	db.commit()
	return data

# Allows the server to be externally visible
if __name__ == "__main__":
	app.run(host= '0.0.0.0')

db.close()
