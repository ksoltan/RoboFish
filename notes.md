### 11/9/2017: Sean
- Hooked head up to ammeter; the current flowing through each pair of coils is almost exactly a third of the total current the power supply is putting out. It looks like our H-bridges don't consume much of our power.

- The new labeled wire set up is very handy!

- Had to re-super-glue ~~one~~ two of the magnets. I don't think the super glue stands up very well to the water and torque. We should think about alternatives at some point. 

- Specced out Hall Effect sensors, cable harnesses, etc.

- Avenue to explore; is our AC reducing the power going through our coils? Is the inductor attenuating our input signal?

### 10/26/2017: Sean
- Researching magnetic fields. [This site](https://www.allaboutcircuits.com/textbook/direct-current/chpt-15/magnetic-fields-and-inductance/) is super helpful to understand inductors.

- [This site](http://dmr-physicsnotes.blogspot.com/2013/01/torque-on-bar-magnet-in-magnetic-field.html) claims the torque τ on a bar magnet in a uniform field is equal to MBsin(θ), so τ ∝ Bsin(θ). Need to do some checking on that result. We know B<sub>coil</sub> ∝ I, so we get τ ∝ Isin(θ). We want either I ∝ θ or V ∝ θ in some respect. So how is τ proportional to θ? Probably depends on the moment of inertia of the magnet. I'm going to go eat.

### 10/16/2017: Sean
- Added full_fish_pwm_control to hinge_control branch; it's the fleshed out class-based fish. 

- Fixed up simple_flap a bit so it's simpler and does what we want.

- Tested the three joints with new simple_flap; the tail joint works, the thorax and head joints click but do not move. I'll investigate this some more.

- Tested the code pwm control code with an oscilloscope. For the first 15-20 seconds, it looks like a nice sinusoidal pwm wave; the positive square wave increases and descreases duty cycle smoothly, and the negative does the same with a strange bump (I think that's because I didn't explicitly set the positive pin to 0 duty cycle, so it still has 1 or something. Will fix.) But then after about 20 seconds, the frequency suddenly goes through the roof; it's oscillating wildly back and forth between positve square wave and negative. Seems like a variable overflow. Will investigate.

- Fixed both issues. \_timer variable needs to be an unsigned long, so it can keep track of 46 days of time instead of 32 seconds. And explicitly analogWriting the unused pin to 0 fixed the weird bump I observed.
