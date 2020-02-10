This is a synth program for sinusoidal sounds (electric organ) with the ability to add harmonics.
The sound wave is obtained by adding sinuses of different amplitudes and frequencies.
Via a virtual MIDI cable, it can be controlled by a sequencer (for example, Cubase).
Audio output is performed with minimal delay via the ASIO library (used additionally by bassasio.dll bass.dll) 
The program is based on the BASS library.
The project was created in Visual Studio 6.0.

***********************************************************************
How to download and run.

Click the green Clone or Download button, then download *.zip-archive, 
unzip it and run ASIOSynthesizer_release.exe

***********************************************************************


Block of sliders inside with labels -6, -5, -4, -3, -2, -1, base, 1, 2, 3, 4, 5, 6 this is the equalizer of the received wave, 
base - the amplitude of the base frequency, and the rest are harmonics.  If there are no harmonics, the Actual Freq field displays the actual frequency of the sound being played. 

The WaveLen field displays the length of the physically received sound wave in meters from the calculation of 330 meters per second. Why did I do this? To understand why in different parts of the small room I am in, the sounds played from the synthesizer in lower case are different.
Now, for example, I'm testing a single bass speaker, I'm clipping a 110 Hz Signal, the wavelength is 3 meters, and the volume of the resulting sound is different in different parts of the room due to the phenomenon of interference, i.e. the total addition of amplitudes in space. The wave is reflected from all surfaces and a different amplitude is obtained at each point of the three-dimensional space. 

To the right of the sliders, information received from the MIDI keyboard, for example, from an image, is displayed, 
9 is the keystroke code, 17 is the number (FA, F) of the MIDI key, 102 is a parameter related to the velocity of the keystroke, or simply the conditional amplitude of the keystroke. When the key is released, the same is sent with an amplitude of 0.

The Release sound block contains a slider that affects the attenuation of the wave after releasing the key.

The a(La)_Note field contains the base frequency of the La note, usually 440 Hertz, but you can change the pitch.

After Scale 12 sets the scale as evenly tempered, the octave is divided into 12 equal parts. You can change it to 24, for example, and experiment.

If there is no MIDI keyboard, you can play on the letter keys from the QWERTYUIOP series and the number keys, the left and right arrows change the binding to the General piano roll.

You can only change parameter values after clicking the "Stop Generate Mode" button. Then you need to start the sound generation again with the "Generate Sound Mode" button.

