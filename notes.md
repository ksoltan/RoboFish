### 10/16/2017: Sean
- Added full_fish_pwm_control to hinge_control branch; it's the fleshed out class-based fish. 

- Fixed up simple_flap a bit so it's simpler and does what we want.

- Tested the three joints with new simple_flap; the tail joint works, the thorax and head joints click but do not move. I'll investigate this some more.

- Tested the code pwm control code with an oscilloscope. For the first 15-20 seconds, it looks like a nice sinusoidal pwm wave; the positive square wave increases and descreases duty cycle smoothly, and the negative does the same with a strange bump (I think that's because I didn't explicitly set the positive pin to 0 duty cycle, so it still has 1 or something. Will fix.) But then after about 20 seconds, the frequency suddenly goes through the roof; it's oscillating wildly back and forth between positve square wave and negative. Seems like a variable overflow. Will investigate.

- Fixed both issues. \_timer variable needs to be an unsigned long, so it can keep track of 46 days of time instead of 32 seconds. And explicitly analogWriting the unused pin to 0 fixed the weird bump I observed.
