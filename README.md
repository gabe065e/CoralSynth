![alt text](https://github.com/gabe065e/CoralSynth/blob/main/demo.png)


This dual oscillator synth has traditional ADSR functionality, as well as gain, noise, and pitch sliders.
Three wavetypes are available: Saw, Sin, Square, and Triangle. The Saw wave is approximated using a summation which can be easily modified from within OscData.cpp.
An additional parameter is available, nicknamed drift. It modifies the frequency of Oscillator 1, creating a dynamic and desynchronized sound no matter what notes are played.
There is also a chorus feature, which modulates the delay of a delay line. Parameters are provided which control the rate and depth of the LFO modulating the delay line, as well as the centre delay, feedback, and mix. 