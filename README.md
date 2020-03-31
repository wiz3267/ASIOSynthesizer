# ASIOSynthesizer
 the synthesizer allows you to play on the MIDI keyboard
 
 Это программа синтезатор синусоидальных звуков (электроорган) с возможностью добавления гармоник.
Звуковая волна получается сложением синусов разной амплитуды и частоты.
Через виртуальный миди-кабель может управляться секвенсером (например, Cubase).
Вывод звука идет с минимальной задержкой через библиотеку ASIO (используется дополнительно bassasio.dll bass.dll) 
Программа основана на библиотеке BASS.
Проект создавался в Visual Studio 6.0.

***********************************************************************
Как скачивать и запускать.

Нажимаем зеленую кнопку Clone or Download, затем скачиваем *.ZIP архив, 
разархивируем его и запускаем ASIOSynthesizer_release.exe

***********************************************************************


Блок ползунков внутри с надписями  -6, -5, -4, -3, -2, -1, base, 1, 2, 3, 4, 5, 6 это эквалайзер получаемой волны, 
base - амплитуда базовой частоты, а остальные это гармоники.  Если гармоник нет, то в поле Actual Freq отображается реальная частота воспроизводимого звука. 

В поле WaveLen отображается длина физически получаемой звуковой волны в метрах из рассчета 330 метров в секунду. Для чего я это сделал? Чтобы понять почему в разных частях небольшой комнаты, в которой я нахожусь, воспроизводимые звуки от синтезатора в нижнем регистре разная.
Сейчас, например тестирую один басовый динамик, зажимаю Ля 110 Герц, длина волны 3 метра,  громкость получаемого звука в разных частях комнаты разная из-за явления интерференции, т.е. суммарного сложения амплитуд в пространстве. Волна отражается от всех поверхностей и в каждой точке трехмерного пространства получается разная амплитуда. 

Правее ползунков отображается информация, принимаемая с миди-клавиатуры, к примеру с картинки, 
9 - это код нажатия клавиши, 17 это номер (Фа, F) клавиши миди-клавы, 102 это параметр, относящейся к скорости нажатия клавиши velocity или просто условно амплитуда нажатия. Когда клавиша отпускается посылается тоже самое с амплитудой 0.

Блок Release sound содержит ползунок, влияющий на затухание волны после отпускания клавиши.

Поле A(La)_Note содержит базовую частоту ноты Ля, обычно 440 Герц, но можно поменять строй.

После Scale 12 задает строй как равномерно темперированный, октава делится на 12 равных частей. Можно изменить, например на 24, поэкспериментировать.

Если нет миди-клавиатуры играть можно на буквенных клавишах из ряда QWERTYUIOP и цифровых клавишах, стрелки влево-вправо меняют привязку к общему пианороллу.

Изменять значения параметров можно только после нажатия кнопки "Stop Generate Mode". Затем нужно запустить вновь генерацию звука кнопкой "Generate Sound Mode".

