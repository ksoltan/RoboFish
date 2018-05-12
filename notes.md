The hinge_control branch contains example sketches exhibiting different attempts at controlling all three joints of the fish which were functional.
Small_fish_control uses different pwm values, and creates a twitching motion because the joints go to their maximum right/left position too fast and do not move in a sinusoidal pattern.

Joint_Test is a suite of tests that can be used to give different pwm and deadzone values for one joint to be able to characterize it.

Fish_Run is the current version of the control, using a set pwm and deadzone value to create a certain amplitude at a frequency. We do not yet have a direct conversion between combinations of these parameters and amplitude, but the fish swims, especially when the tail gets 100% duty.
