Objects
=======

This repository contains libraries and all of configurations to start prototype objects in the APIO system

Apio Dongle and General Arduino Library
==========

This repository contains the hardware folder for Arduino IDE, include coordinator sketch and include an example objects.

# Build and Run

### Prerequisites
You need:
* [Arduino IDE](https://www.arduino.cc/en/Main/Software)

===========
### Install

* `cd /path/to/your/directory`
* `git clone https://github.com/ApioLab/library-arduino.git`
* `copy hardware folder in your Arduino folder(default in Documents folder)`
* `Open Arduino IDE and Select Apio General in Boards menu`
* `Create your first application with Apio SDK [see here](http://www.apio.cc/en/wiki#ch-1-4) `

HOW APIO ENCODING WORKS
=======================

<p>Apio identifies any object (real or virtual) as a set of properties that assume specific values: this kind of encode is not only a “language”, but also a characterization of the object itself. In fact, the pair property:value defines univocally an action of the object, it represents a command. The list of all these pairs defines its Dictionary: that is all the things the object can do. This is what allows you to abstract from the concept of real object relieving the Software developer from the Hardware knowledge and vice versa. It is not important how it carries out these actions nor how they are implemented; what matters is knowing the pair property:value that will generate a specific action. Knowing the Dictionary of a Friend Object means being able to talk to it.<p>

<p>So if assume that I have created a LED and I want to codify that in APIO, I have a function like this:
<code>onoff(pin, value)</code> that will write on the pin of the LED.</p>
<p>So in the loop of the microcontroller I will write:</p>

```sh
void loop(){

	apioLoop();

	if(property=="onoff"){
		if(value=="1") {
			onoff(LED, 1);
		}
		if(value=="0"){
			onoff(LED, 0);
		}
	}
}
```
<p> <code>apioLoop ()</code> allows you to receive messages and select the current pair property:value to be processed in the current main loop. This is because the sketch have the ability to queue multiple commands from the server, but you have to worry only to check the value of variables called 'property' and 'value' because on each loop, the function apioLoop() stores in these varibiabiles an element of the queue (of course only if multiple commands are sent or the main loop has not had time to execute the previous one, before the arrival of subsequent commands)</p>

<p> To send messages to the server you can use  <code>void apioSend(String toSend)</code> . .....<code>apioSend()</code> </p>



<p>And that's all.</p>
<p>Now you have all the knowledge to codify all of your project with APIO.</p>
<h4>What are you waiting for?</h4>
<p>Choose your communication channel, see the EXAMPLE and create your objects</p>
