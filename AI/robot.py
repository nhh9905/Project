# created by nhh
import pyttsx3
from datetime import date, datetime
import requests
import webbrowser as wb
import time
import os

robot_mouth = pyttsx3.init()
robot_brain = ""

def weather(city_name):
	api_key = ""
	base_url = "http://api.openweathermap.org/data/2.5/weather?"
	complete_url = base_url + "appid=" + api_key + "&q="+ city_name
	response = requests.get(complete_url)
	x = response.json()

	if x["cod"] != "404":
		y = x["main"]
		current_temperature = int(y["temp"] - 273.15)
		current_pressure = y["pressure"]
		current_humidity = y["humidity"]
		z = x["weather"]
		weather_description = z[0]["description"]
		robot_brain = "Currently available " + str(weather_description) + "\nThe temperature is " + str(current_temperature) + " degree C" + "\nHumidity is " + str(current_humidity) + "%"
	else:
		robot_brain = "City name not found"

	return robot_brain

def open_web(website, search):
	url = f"https://www.{website}.com/search?q={search}"
	wb.get().open(url)

voices = robot_mouth.getProperty('voices')
robot_mouth.setProperty('voice', voices[1].id)
robot_mouth.setProperty('volume', 0.5)
count = 0

now = datetime.now()
real_time = int(now.strftime("%H"))
if 5 <= real_time < 11:
	robot_brain = "Good morning, boss"
elif 11 <= real_time <= 18:
	robot_brain = "Good afternoon, boss"
elif 19 <= real_time <= 23:
	robot_brain = "Good evening, boss"
else:
	robot_brain = "Time to sleep"
print("Robot: " + robot_brain)
print("Robot: ...")
robot_mouth.say(robot_brain)
robot_mouth.runAndWait()

while True:
	robot_brain = "How can I help you?"
	print("Robot: " + robot_brain)
	print("Robot: ...")

	if count == 0:
		robot_mouth.say(robot_brain)
		robot_mouth.runAndWait()
	count += 1
	
	you = input("You: ")
	you = you.lower()
	print(you)
	
	if you == "":
		robot_brain = "I can't hear you, try again"

	elif "name" in you:
		robot_brain = "I am Robot, your virtual assistant. Do you need help, boss?"
	
	elif "today" in you:
		today = date.today()
		robot_brain = today.strftime("%A, %B %d, %Y")
	
	elif "time" in you:
		now = datetime.now()
		robot_brain = now.strftime("%H:%M:%S %p")
	
	elif "bye" in you:
		robot_brain = "Goodbye boss. Have a good day!"
		print("Robot: ...")
		print("Robot: " + robot_brain)
		robot_mouth.say(robot_brain)
		robot_mouth.runAndWait()
		break

	elif "weather" in you:
		robot_brain = "Enter your city, boss"
		print("Robot: ...")
		print("Robot: " + robot_brain)
		robot_mouth.say(robot_brain)
		robot_mouth.runAndWait()
		you = input("You: ")
		robot_brain = weather(you)
		if "City name not found" in robot_brain:
			robot_brain = "Enter again, boss"
			print("Robot: ...")
			print("Robot: " + robot_brain)
			robot_mouth.say(robot_brain)
			robot_mouth.runAndWait()
			you = input("You: ")
			robot_brain = weather(you)

	elif "google" or "youtube" or "tiktok" in you:
		website = you
		robot_brain = "What should I search boss?"
		print("Robot: ...")
		print("Robot: " + robot_brain)
		robot_mouth.say(robot_brain)
		robot_mouth.runAndWait()
		you = input("You: ")
		search = you.lower()
		open_web(website, search)
		robot_brain = f'Here is {search} on {website}'

	elif "sleep" in you:
		robot_brain = "Are you sure, boss?"
		print("Robot: ...")
		print("Robot: " + robot_brain)
		robot_mouth.say(robot_brain)
		robot_mouth.runAndWait()
		you = input("You: ")
		you = you.lower()
		if "yes" in you:
			robot_brain = "Input your time: "
			print("Robot: ...")
			print("Robot: " + robot_brain)
			robot_mouth.say(robot_brain)
			robot_mouth.runAndWait()
			you = int(input("You: "))
			time.sleep(you)
		if "no" in you:
			robot_brain = "Ok boss"

	elif "shut down" in you:
		robot_brain = "Are you sure, boss?"
		print("Robot: ...")
		print("Robot: " + robot_brain)
		robot_mouth.say(robot_brain)
		robot_mouth.runAndWait()
		you = input("You: ")
		you = you.lower()
		if "yes" in you:
			os.system('shutdown -s')
		if "no" in you:
			robot_brain = "Ok boss"

	elif "restart" in you:
		robot_brain = "Are you sure, boss?"
		print("Robot: ...")
		print("Robot: " + robot_brain)
		robot_mouth.say(robot_brain)
		robot_mouth.runAndWait()
		you = input("You: ")
		you = you.lower()
		if "yes" in you:
			os.system('shutdown -r')
		if "no" in you:
			robot_brain = "Ok boss"

	else:
		search = you.lower()
		url = f"https://www.google.com/search?q={search}"
		wb.get().open(url)
		robot_brain = f'Here is {search} in google'

	print("Robot: ...")
	print("Robot: " + robot_brain)
	robot_mouth.say(robot_brain)
	robot_mouth.runAndWait()