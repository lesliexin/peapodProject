from flask import Flask, request, render_template
import MySQLdb
from datetime import datetime
import MySQLdb

app = Flask(__name__)

# Connecting to database
db = MySQLdb.connect("localhost","root","lxin2016","test")
cursor = db.cursor()

# Finding the real time
compile_hour = datetime.now().hour;
compile_minute = datetime.now().minute;
time = (compile_hour*100) + compile_minute
print "Compile time: ", time

# Form
@app.route("/")
def hello():
	return render_template('echoform3.php')

# Querying data from database
@app.route("/echo", methods=['GET','POST'])
def echo():
	input_ = request.form['values']
	cursor.execute("INSERT INTO peapod (Time, MAC_Address, Signal_Strength) VALUES (%s,%s,%s)", (time, input_, time))
	db.commit()
	return render_template('echo3.php')

if __name__ == "__main__":
	app.run(host= '0.0.0.0')

db.close()
