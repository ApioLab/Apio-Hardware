Objects
=======

This repository contains libraries and all of configurations to start prototype objects in the APIO system

HOW APIO ENCODING WORKS
=======================

<p>Apio identifies any object (real or virtual) as a set of properties that assume specific values: this kind of encode is not only a “language”, but also a characterization of the object itself. In fact, the pair property:value defines univocally an action of the object, it represents a command. The list of all these pairs defines its Dictionary: that is all the things the object can do. This is what allows you to abstract from the concept of real object relieving the Software developer from the Hardware knowledge and vice versa. It is not important how it carries out these actions nor how they are implemented; what matters is knowing the pair property:value that will generate a specific action. To know the Dictionary of a Friend Object means being able to talk to it.<p>

<p>So if assume that I have created a LED and I want to codify that in APIO, I have a function like this:
<code>onoff(pin, value)</code> that will write on the pin of the LED.</p>
<p>So in the loop of the microcontroller I will write:</p>

```sh
void loop(){
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

<p>And that's all.</p>
<p>Now you have all the knowledge to codify all of your project with APIO.</p>
<h4>What are you waiting for?</h4>
<p>Choose your communication channel, see the EXAMPLE and start create your objects</p>
