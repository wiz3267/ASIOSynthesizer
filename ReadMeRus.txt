Это программа синтезатор (синусоидальных) сложных звуков (например как электроорган) с возможностью добавления гармоник.

Звуковая волна получается сложением синусов разной амплитуды и частоты + обработка через фильтры
и линии задержки (эффекты эха, реверберации). В настоящее время не может работать в режиме VST инструмента,
и внешнее управление возможно пока только через виртуальный кабель и секвенсор (я использовал Cubase)

Вывод звука идет с минимальной задержкой через библиотеку ASIO (используется дополнительно bassasio.dll bass.dll) 
Программа основана на библиотеке BASS.

Проект создавался в Visual Studio 6.0.

***********************************************************************
Как скачивать и запускать.

Нажимаем на сайте github зеленую кнопку Code, затем скачиваем *.ZIP архив, 
разархивируем его и запускаем ASIOSynthesizer_release.exe

***********************************************************************


Блок ползунков внутри с надписями  1/6, 1/5, 1/4, 1/3, 1/2, sin, sqr, 10g, 4x, [v1], [v2],  

это микшер получаемой волны, 

sin - амплитуда базовой частоты, а остальные это или одельные гармоники от базовой, либо другие типы волн
sqr - квадратно-синусоидальная волна. ее вид можно регулировать круговым слайдером sqr. При значении слайдера 0
волна чисто квадратная, при значении 100 - чисто синус. 
10g - это сложная волна, которая может состоять от 1 до 50 произвольных гармоник с разной амплитудой,
которые можно задать с помошью мышки в окне гистограммы, ниже отображается форма получаемой волны,
с помощью кнопок <+>,<-> можно менять масштаб графика по оси X.

В поле Base Freq отображается базовая частота воспроизводимой ноты.

В поле WaveLen отображается длина физически получаемой звуковой волны в метрах из рассчета 330 метров в секунду. Для чего я это сделал? Чтобы понять почему в разных частях небольшой комнаты, в которой я нахожусь, воспроизводимые звуки от синтезатора в нижнем регистре разная.
Сейчас, например тестирую один басовый динамик, зажимаю Ля 110 Герц, длина волны 3 метра,  громкость получаемого 
звука в разных частях комнаты разная из-за явления интерференции, 
т.е. суммарного сложения амплитуд в пространстве. 
Волна отражается от всех поверхностей и в каждой точке трехмерного пространства получается разная амплитуда. 

Правее ползунков отображается информация, принимаемая с миди-клавиатуры, к примеру с картинки, 
9 - это код нажатия клавиши, 17 это номер (Фа, F) клавиши миди-клавы, 102 это параметр, 
относящейся к скорости нажатия клавиши velocity или просто условно амплитуда нажатия. 
Когда клавиша отпускается посылается тоже самое с амплитудой 0.

Блок Release sound содержит ползунок, влияющий на затухание волны после отпускания клавиши.

Поле A(La)_Note содержит базовую частоту ноты Ля, обычно 440 Герц, при изменении можно поменять строй.

После Scale 12 задает строй как равномерно темперированный, октава делится на 12 равных частей. 
Можно изменить, например на 24, 36, 48 и т.д. поэкспериментировать.

При нажатой опции "Garmonic mode" внешний вид клавиатуры меняется, и для высчитывания частот нот
используется значение из поля Base freq. При этом инструмент переходит в режим игры натуральным строем.
В таком случае самая первая белая клавиша "До"(С) будет иметь частоту из поля Base freq, а остальные
клавиши, подряд, белые и черные, будут иметь частоты Fn=BaseFreq*N, например 50,100,150,200,250 и т.д.

Если нет миди-клавиатуры играть можно на буквенных клавишах из ряда <tab>,Q,W,E,R,T,Y,U,I,O,P и цифровых клавишах, 
стрелки управления курсором <влево>-<вправо> меняют привязку к пианороллу, при этом на нем отображается
кружок, соответствующей клавише <tab>





