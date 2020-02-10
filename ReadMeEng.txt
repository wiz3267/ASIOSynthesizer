How to download.
Click Clone or Download, then download the * .ZIP archive, unzip it and run ASIOSynthesizer_release.exe
The project was created in Visual Studio 6.0

This is a sinusoidal sound synthesizer program with the ability to add harmonics.
Via a virtual MIDI cable it can be controlled by a sequencer (for example, Cubase).
Sound output comes with a minimum delay through the ASIO library (additional bass.dll is used)

The block of sliders inside with the inscriptions ... -2, -1, base, 1, 2, ... is like an equalizer, base is the amplitude of the base frequency, and the rest are harmonics.
If there are no harmonics, the Actual Freq field displays the actual frequency of the reproduced sound.
The newer version, which is in the repository, also displays the wavelength obtained at the rate of 330 meters per second. Why did I do this?
Now, for example, I’m testing one bass speaker, clamping La 110 Hertz, wavelength 3 meters, the sound is heard in the room in different parts of different amplitudes due to interference.

To the right of the sliders is displayed information received from a MIDI keyboard, for example, from a picture,
9 is the keypress code, 17 is the number (Фа, F) of the midi key, 102 is a parameter related to the velocity of the velocity key or simply the amplitude of the keystroke. When the key is released the same thing is sent with an amplitude of 0.

A sound wave is obtained by adding sines of different amplitude and frequency.

The Release sound block contains a slider that affects the attenuation of the wave after the key is released.

Field A (La) _Note contains the base frequency of La notes, usually 440 Hertz, but you can change the tuning.

After Scale 12 sets the system as evenly tempered, the octave is divided into 12 equal parts. You can change, for example to 24, to experiment.

If there is no MIDI keyboard, you can play on alphabetic QWERTYUIOP series and number keys, left and right arrows change the binding to the general piano roll.

You can change the parameter values ​​only after pressing the "Stop Generate Mode" button, then start the sound again with the "Generate Sound Mode" button.

