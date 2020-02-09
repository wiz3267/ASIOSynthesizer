How to download.
Click Clone or Download, then download the * .ZIP archive, unzip it and run ASIOSynthesizer_release.exe
The project was created in Visual Studio 6.0

Как скачивать.
Нажимаем Clone or Download, затем скачиваем *.ZIP архив, разархивируем его и запускаем ASIOSynthesizer_release.exe
Проект создавался в Visual Studio 6.0

This is a sinusoidal sound synthesizer program with the ability to add harmonics.
Via a virtual MIDI cable it can be controlled by a sequencer (for example, Cubase).
Sound output comes with a minimum delay through the ASIO library (additional bass.dll is used)

Это программа синтезатор синусоидальных звуков с возможностью добавления гармоник.
Через виртуальный миди-кабель может управляться секвенсером (например, Cubase).
Вывод звука идет с минимальной задержкой через библиотеку ASIO (используется дополнительно bass.dll) 

__________________________________________________________________________________
Блок ползунков внутри с надписями  ... -2, -1, base, 1, 2,... это как бы эквалайзер, base - амплитуда базовой частоты, а остальные это гармоники. 
Если гармоник нет, то в поле Actual Freq отображается реальная частота воспроизводимого звука. 
В более новой версии, лежащей в репозитории, отображается также длина получаемой волны из рассчета 330 метров в секунду. Для чего я это сделал?
Сейчас например тестирую один басовый динамик, зажимаю Ля 110 Герц, длина волны 3 метра, в комнате раздается звук в разных частях разной амплитуды из-за интерференции.

The block of sliders inside with the inscriptions ... -2, -1, base, 1, 2, ... is like an equalizer, base is the amplitude of the base frequency, and the rest are harmonics.
If there are no harmonics, the Actual Freq field displays the actual frequency of the reproduced sound.
The newer version, which is in the repository, also displays the wavelength obtained at the rate of 330 meters per second. Why did I do this?
Now, for example, I’m testing one bass speaker, clamping La 110 Hertz, wavelength 3 meters, the sound is heard in the room in different parts of different amplitudes due to interference.
__________________________________________________________________________________
Правее ползунков отображается информация, принимаемая с миди-клавиатуры, к примеру с картинки, 
9 - это код нажатия клавиши, 17 это номер (Фа, F) клавиши миди-клавы, 102 это параметр, относящейся к скорости нажатия клавиши velocity или просто условно амплитуда нажатия. Когда клавиша отпускается посылается тоже самое с амплитудой 0.

Звуковая волна получается сложением синусов разной амплитуды и частоты.

Блок Release sound содержит ползунок, влияющий на затухание волны после отпускания клавиши.

Поле A(La)_Note содержит базовую частоту ноты Ля, обычно 440 Герц, но можно поменять строй.

To the right of the sliders is displayed information received from a MIDI keyboard, for example, from a picture,
9 is the keypress code, 17 is the number (Фа, F) of the midi key, 102 is a parameter related to the velocity of the velocity key or simply the amplitude of the keystroke. When the key is released the same thing is sent with an amplitude of 0.

A sound wave is obtained by adding sines of different amplitude and frequency.

The Release sound block contains a slider that affects the attenuation of the wave after the key is released.

Field A (La) _Note contains the base frequency of La notes, usually 440 Hertz, but you can change the tuning.
__________________________________________________________________________________

После Scale 12 задает строй как равномерно темперированный, октава делится на 12 равных частей. Можно изменить, например на 24, поэкспериментировать.

Если нет миди-клавиатуры играть можно на буквенных из ряда QWERTYUIOP и цифровых клавишах, стрелки влево-вправо меняют привязку к общему пианороллу.

Изменять значения параметров можно только после нажатия кнопки "Stop Generate Mode", затем запустить вновь звук кнопкой "Generate Sound Mode".

After Scale 12 sets the system as evenly tempered, the octave is divided into 12 equal parts. You can change, for example to 24, to experiment.

If there is no MIDI keyboard, you can play on alphabetic QWERTYUIOP series and number keys, left and right arrows change the binding to the general piano roll.

You can change the parameter values ​​only after pressing the "Stop Generate Mode" button, then start the sound again with the "Generate Sound Mode" button.
__________________________________________________________________________________


