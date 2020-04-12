# Handwash_Dispenser

Contact free hand wash dispenser with voice assistance.

The project is based on Arduino pro mini, DFPlayer and DS1307 RTC

The smart handwash dispenser calls out(reminds) user with a message after every 2 hours to wash there hand.
Then the dispenser discharge the sanitizer once the IR sensor is triggered with a message.
Finally it thanks the user for washing there hand with a sweet little message.

Pro mini controls the servo for the actuator.
DFPlayer plays the audio for the SD card.
IR sensor detects the motion to trigger the servo.
DS1307 RTC to trigger the servo every 2 hours with the help of pro mini and also to disable the call out feature in night.

YouTube channel link: https://www.youtube.com/Neutrino1
