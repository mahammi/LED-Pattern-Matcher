# LED-Pattern-Matcher

Overview
---------

Pattern matcher is a game created using the STM32 microcontroller, through which the user can get a classic arcade experience. The objective is to press buttons that match up with the correct corresponding LED light patterns. The game tests user's memorization skills, as they are required to remember previous LED sequences, along with new iterations being added to the entire sequence.
![image](https://user-images.githubusercontent.com/50532268/144693007-fcc28f0f-9ae4-40f8-9cf3-56ea3ab9aac7.png)


Program & Game Mechanics
---------------

The lifetime of the code begins with the user turning on the microcontroller and pressing the first button to "start", through which  an array is initialized to hold a randomized combination of LED’s. The lights are then turned on in order, and the user is prompted to click a button that corresponds to the light. This process is repeated through the use of a loop, where each round the user must input one additional index of the array. The loop is broken once the user clicks the incorrect button, and they are then prompted to click the reset button to play again. 
Design Information
-------------------------


**Design Document:** https://docs.google.com/document/d/11t27m5X-pcR5LE7TGt6xsyDWkFaZfMrEQCSz62dFdLQ/edit?usp=sharing

Developed for ECE198 (Project Studio) at the University of Waterloo

Created by Maham Ali and Samantha Grieco
