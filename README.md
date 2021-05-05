# PulseSenor_with_NodeMcu
Using the AP mode of nodemcu to create a web server, and then display the BPM based on pulse sensor signal calculation

This is the first time that I have come into contact with object-oriented language(C++). When I implement and encapsulate it, I refer to various official examples and third-party examples. There must be many shortcomings. I uploaded it to GitHub as my first project and to encourage myself.

## What's include in this?
Here are two header files and their source files. They are the libraries encapsulated by me for nodemcu, which can be uploaded with **Arduino IDE**.
The first one is ***myWebserver.h*** which is used to creat a wifi I called MiaoMiao.And everyone can vistit the webserver contribute by NodeMcu by connecting the MiaoMiao wifi.
The Second one is ***Pulsesensor.h*** which is to achieve the function of pulse test.His algorithm implementation is the same as the official website [pulsesensor.org](https://pulsesensor.com/pages/pulse-sensor-amped-arduino-v1dot1).On this basis, I modified the timer and adapted it for NodeMcu.

There is only one function that about the Pulsesensor but We can add other functions future if we want.

By the way, there are two more things here，They are two .html in the folder called data, You should uplod them to your NodeMcu so that you can visited them on the website.

## Writing for myself
I spent few weeks to implement this, I learned the basic about LOT, C++, html, class and objects and so on. What disturbed me most is the class and objects. I have meet many problems while I were tring to create library files to make .Ino file look more concise. But many problems happened in dealing with the relationship between class and function, class and class. No matter how annoying the process of finding the answer is, it's here now. And I got much.
