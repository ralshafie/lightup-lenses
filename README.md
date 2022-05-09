# lightup-lenses

Because we were given so much freedom in designing this project, we did a lot of brainstorming to figure out what the right project for us would be. After tossing around tons of ideas, from dioramas to sculptures of memes, we landed on Light-Up Lenses. After completing a lab in class using neopixel LEDs we knew that we wanted to use those for our final. We were specifically inspired by the LEDs in a circular disk. As soon as we saw those, we immediately knew that we needed to incorporate them into glasses. 

## Materials

Because we were originally envisioning 3D printing the glasses frames, our model was designed in Tinkercad, which was a new technology for us. However, we realized that it would be more efficient to use a laser cutter. Luckily, Tinkercad models can be used for both 3D printing and laser cutting

# Technical Development

In order to program the ESP32, we used an Arduino IDE to program the specific qualifications of the display.  For this project, to make the glasses wireless, we implemented ESPNOW, a mechanisms that allows two ESP32 devices to communicate data to each other. Download the platform from online and see the details below.

## Run a program

For this device to work, you have to run two sets of code for each ESPNOW that is being used. First, run the program that receives the inputted data, which, in this case, is the data from the turning of potentiometers. To do so, run the program that controls the ESP32 that is attached to the wireless glasses. Download the file and click on the arrow `—>` icon at the top left corner. The program should compile and run immediately barring any errors that may occur regarding the set-up of the ESP32 in the Arduino IDE. Ensure that you have the correct port selected. Run the master code, which is connected to the ESP32 that controls the potentiometer that transmits the rgb values. Finally, connect the ESP32 that is in the enclosure to your computer, and the run the Javascript/HTML code in your browser. Click the screen, connect to the port, and control the colors as you wish!

## The code

Because the glasses and the controls involve two ESP32s, there are two sets of code. What is considered to be a “slave” and “master” set of code, Leah and I have renamed it to be the “slayed” and “slayer” sets of code (for obvious reasons, we don’t like these terms).  The slayer is the code that transmits the rgb from the potentiometer to the glasses. The glasses code is considered the slayed. See the breakdown of both sets of code below.  Additionally, see the breakdown of the Javascript to see how the data is received and transmitted to the browser screen. 

### Slayer

The first set of code that we will go over is the slayer code. 

- The first section is dedicated to defining global variables, shortcuts, and invoking certain libraries.
    - Here we specified the specific pins for the LEDs and establish the LEDs as objects within the code.
    
  
    
    - This is also where we created a separate function that we call later in the code that deals with the transmitting of the data and the formatting of the data being sent as a string in order to be parsed on the slayed side of the code.
        
     
        
- `void setup(void)`
    - Initializes the program and registered the peer info for the ESPNOW. It establishes a channel for the ESPNOW communication, as well as other error checking to establish that connection between the slayed and slayer code.
   
    
- `void loop()`
    - This is the main body of the code, where we aim for the potentiometer values to be continuously collected . Additionally, it makes a conditional statement that sends these values to the slayed code once the button is pressed.  When it is pressed, we call the function that we defined earlier (broadcast()) to send that data. Finally, we also want to send the data to our HTML/JavaScript file to reflect the colors on the screen.
    
  
    ```
   
### Slayed

The following code will go over the slayed set of code, which is the code that controls the lights on the ESP32. It receives the data from the slayer regarding the potentiometer values that correspond to the rgb values of the lights. 

- It begins the same way as most other codes, where we define libraries used, and define the pins for each of the data inputs.



- Next, we define a function that receives the data. It creates a buffer to process the string that is transmitted, ensures that it is null terminated, and parses it so that it is able to access each number separately (the way the data is sent from the slayer is that the values is a list of numbers but ini the form of a string, so we had to parse through to access each number individually. For each of the LED pixels, we set the color using the values we just parsed.

- `void setup(void)`
    - Initializes the program and creates a WiFi connection. It establishes the connection for ESPNOW in order to receive any communication.


### Javascript

This code is what essentially controls the browser side of this project. Powered by a simple HTML page that displays the rgb values and a title, the Javascript establishes a WiFi connection to the ESP32 and communicates with the Arduino code to receive the rgb values. 

- First, we prompt the user to select a serial post when you click on the screen.

- The next block of code essentially takes in the value that is being sent from the serializeJSON() function from the Arduino code, and perform a specific function on it. In this case, we are changing the background color according to the values that we are receiving.




