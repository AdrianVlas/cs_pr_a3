#ifndef __CONST_DRIVER_SERIAL_FLASH__
#define __CONST_DRIVER_SERIAL_FLASH__

#define NUMBER_DATAFLASH_CHIP      2

#define INDEX_DATAFLASH_1           0
#define INDEX_DATAFLASH_2           1

#define VAGA_SIZE_PAGE_DATAFLASH_1      8 //ця константа потрібна тільки для того, щоб можна було легко множити на 256 і ділити на 256
#define SIZE_PAGE_DATAFLASH_1           (1 << VAGA_SIZE_PAGE_DATAFLASH_1) //256 байт
#define NUMBER_PAGES_INTO_DATAFLASH_1   512

#define VAGA_SIZE_PAGE_DATAFLASH_2      9 //ця константа потрібна тільки для того, щоб можна було легко множити на 512 і ділити на 512
#define SIZE_PAGE_DATAFLASH_2           (1 << VAGA_SIZE_PAGE_DATAFLASH_2) //512 байт
#define NUMBER_PAGES_INTO_DATAFLASH_2   4096

#if SIZE_PAGE_DATAFLASH_2 >= SIZE_PAGE_DATAFLASH_1
#define SIZE_PAGE_DATAFLASH_MAX         SIZE_PAGE_DATAFLASH_2
#else
#define SIZE_PAGE_DATAFLASH_MAX         SIZE_PAGE_DATAFLASH_1
#endif

#define NUMBER_PAGES_INTO_AR            NUMBER_PAGES_INTO_DATAFLASH_2
#define NUMBER_PAGES_INTO_DR            480
#define NUMBER_PAGES_INTO_PR_ERR        (NUMBER_PAGES_INTO_DATAFLASH_1 - NUMBER_PAGES_INTO_DR)

#define NUMBER_PAGES_IN_ONE_DR_RECORD         8
#define SIZE_BUFFER_FOR_DR_RECORD             (SIZE_PAGE_DATAFLASH_1*NUMBER_PAGES_IN_ONE_DR_RECORD) 
#define MAX_NUMBER_RECORDS_INTO_DR            60
#define MIN_ADDRESS_DR_AREA                   0x0
#define SIZE_DR_AREA                          (NUMBER_PAGES_INTO_DR<<VAGA_SIZE_PAGE_DATAFLASH_1)
#define MAX_ADDRESS_DR_AREA                   (MIN_ADDRESS_DR_AREA + SIZE_DR_AREA - 1)

#define FIRST_INDEX_START_START_RECORD_DR     0
#define FIRST_INDEX_DATA_TIME_DR              1
#define FIRST_INDEX_NAME_OF_CELL_DR           8
#define FIRST_INDEX_NUMBER_ITEMS_DR           40
#define FIRST_INDEX_NUMBER_CHANGES_DR         41
#define FIRST_INDEX_NUMBER_MAX_PHASE_DR       43
#define FIRST_INDEX_NUMBER_MIN_U_DR           44
#define FIRST_INDEX_NUMBER_MAX_U_DR           45
#define FIRST_INDEX_NUMBER_MAX_ZOP_DR         46
#define FIRST_INDEX_FIRST_BLOCK_DR            47
#define FIRST_INDEX_FIRST_DATA_DR             846

#define VAGA_SIZE_ONE_RECORD_PR_ERR           5
#define SIZE_ONE_RECORD_PR_ERR                (1<<VAGA_SIZE_ONE_RECORD_PR_ERR)
#define NUMBER_RECORDS_PR_ERR_INTO_PAGE       (SIZE_PAGE_DATAFLASH_1>>VAGA_SIZE_ONE_RECORD_PR_ERR) //кількість записів програмних подій у одній строрінці мікросхеми послідовної DataFlash
#define MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER 32 //максимальнакількість записів в буфері типу FIFO, які чекають на запису DataFlash
#define SIZE_BUFFER_FOR_PR_ERR                (SIZE_ONE_RECORD_PR_ERR*MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER)
#define MAX_NUMBER_RECORDS_INTO_PR_ERR        (NUMBER_PAGES_INTO_PR_ERR*NUMBER_RECORDS_PR_ERR_INTO_PAGE)
#define MIN_ADDRESS_PR_ERR_AREA               (MAX_ADDRESS_DR_AREA + 1)
#define SIZE_PR_ERR_AREA                      (NUMBER_PAGES_INTO_PR_ERR<<VAGA_SIZE_PAGE_DATAFLASH_1)
#define MAX_ADDRESS_PR_ERR_AREA               (MIN_ADDRESS_PR_ERR_AREA + SIZE_PR_ERR_AREA - 1)

#define VAGA_NUMBER_POINT_AR                  (VAGA_NUMBER_POINT - 1)
#define NUMBER_POINT_AR                       (1 << VAGA_NUMBER_POINT_AR)
#define MIN_ADDRESS_AR_AREA                   0x0
#define SIZE_AR_AREA                          (NUMBER_PAGES_INTO_AR<<VAGA_SIZE_PAGE_DATAFLASH_2)
#define MAX_ADDRESS_AR_AREA                   (MIN_ADDRESS_AR_AREA + SIZE_AR_AREA - 1)


#define TRANSACTION_EXECUTING_NONE              0
#define TRANSACTION_EXECUTING                   1
#define TRANSACTION_EXECUTED_WAIT_ANALIZE       2

#define CODE_OPERATION_NONE                                 0
#define CODE_OPERATION_STATUS_READ                          1
#define CODE_OPERATION_PAGESIZE_256                         2
#define CODE_OPERATION_ERASE                                3
#define CODE_OPERATION_WRITE_PAGE_THROUGH_BUFFER            4
#define CODE_OPERATION_READ_HIGH_FREQ                       5
#define CODE_OPERATION_READ_PAGE_INTO_BUFFER                6
#define CODE_OPERATION_WRITE_BUFFER                         7
#define CODE_OPERATION_WRITE_BUFFER_INTO_MEMORY_WITH_ERASE  8

/*Біти 0-15 відносять до мікросхеми DataFlash дискретного реєстратора і реєстратора програмних подій*/
#define TASK_ERASE_DATAFLASH_1_BIT                                          0
#define TASK_ERASE_DATAFLASH_1                                              (1<<TASK_ERASE_DATAFLASH_1_BIT)
#define TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH_BIT                        1
#define TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH                            (1<<TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH_BIT)
#define TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR_BIT        2
#define TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR            (1<<TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU_BIT                          3
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU                              (1<<TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT                      4
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU                          (1<<TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB_BIT                           5
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB                               (1<<TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485_BIT                         6
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485                             (1<<TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT                       7
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB                           (1<<TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT                     8
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485                         (1<<TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT)

#define  SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2                16

/*Біти 16-31 відносять до мікросхеми DataFlash аналогового реєстратора*/
#define TASK_ERASE_DATAFLASH_2_BIT                                          (0 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_ERASE_DATAFLASH_2                                              (1<<TASK_ERASE_DATAFLASH_2_BIT)
#define TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR_BIT   (1 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR       (1<<TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR_BIT)
#define TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR_BIT        (2 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR            (1<<TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU_BIT                          (3 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU                              (1<<TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB_BIT                           (5 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB                               (1<<TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485_BIT                         (6 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485                             (1<<TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485_BIT)

#define WIGHT_OF_DR_WAITING                       2

#define STATE_DR_NO_RECORD                        0 //На даний момент ніких дій з дискретним реєстратором не виконується
#define STATE_DR_FORCE_START_NEW_RECORD           1 //Оформлені події оформити як запис, але ще не досягнуто умови завершення роботи дискретного реєстратора тому при наступному проході розпочати новий запис
#define STATE_DR_EXECUTING_RECORD                 2 //Іде процес запису реєстратора
#define STATE_DR_MAKE_RECORD                      3 //Оформити запис для  запису у Dataflash
#define STATE_DR_CUT_RECORD                       4 //Оформлені події оформити як запис, але ще не досягнуто умови завершення роботи дискретного реєстратора тому при наступному проході розпочати новий запис

#define MAX_TIME_OFFSET_FROM_START                      0xFFFFFF // 4 год. 39 хв. 37 сек. 215 мілісек.
#define MAX_EVENTS_IN_ONE_RECORD                        41

#define LABEL_START_RECORD_DR           0xA5

#define READING_DR_FOR_MENU             1
#define READING_DR_FOR_USB              2
#define READING_DR_FOR_RS485            3
#define READING_PR_ERR_FOR_MENU         4
#define READING_PR_ERR_FOR_USB          5
#define READING_PR_ERR_FOR_RS485        6

#define READING_AR_FOR_MENU             1
#define READING_AR_FOR_USB              2
#define READING_AR_FOR_RS485            3

#define LABEL_START_RECORD_PR_ERR       0x5A

#define ETAP_NONE                                 0
#define ETAP_READ_MEMORY_INTO_BUFFER              1
#define ETAP_HAVE_READ_MEMORY_INTO_BUFFER         2
#define ETAP_MODIFY_AND_WRITE_BUFFER              3
#define ETAP_MODIFIED_AND_WRITTEN_BUFFER          4
#define ETAP_WRITE_BUFFER_INTO_MEMORY             5
#define ETAP_ERROR_BEFALLEN                       6

#define LABEL_START_RECORD_AR           0xAB

#define STATE_AR_TEMPORARY_BLOCK                  -1//На даний момент певні внутрішні операції блокують роботу аналогового реєстратрора
#define STATE_AR_NO_RECORD                        0 //На даний момент ніяких дій з аналоговим реєстратором не виконується
#define STATE_AR_START                            1 //Запуск нового запису аналогового реєстратора
#define STATE_AR_SAVE_SRAM_AND_SAVE_FLASH         2 //Стан роботи аналогового реєстратора "загрузка і вигрузка"
#define STATE_AR_ONLY_SAVE_FLASH                  3 //Стан роботи аналогового реєстратора "тільки вигрузка", бо "загрузка" вже закінчилася

/*
Виходимо з того, що максимально можливий аналоговий масив може бути 5с(доаварійний
масив) + 25с(післяаварійний масив) = 30с
Тоді повний об'єм буде
30(с)х50(періодів)х16(виборок на період)х(9(канали) + 13(двобайтні слова дискретних сигналів))
х2(байти на число) = 1056000(байти)
Ще має бути 1(байт мітки початку запису )+7(байти мітки часу)+
4(байти коеф.тр.ТТ)+4(байти коеф.тр.ТН)++32(байти імені комірки) = 48 байти

!!!Розмір заголовку аналоговог ореєстратора обов'язково має бути числом кратиним 2, 
щоб не вийшло так, що коли ми формуємо буфер для запису у DataFlash (розмір буферу 
256 байт), то не виходить записати одну миттєву виборку (розмір 2-а байт): тоді б 
виникла ситуація, що один байт треба писати одною трансакцією, а інший байт - 
вже другою трансакцією. Ця ситуація дуже б ускладнила роботу з аналоговим реєстратором. 
Тому краще такої ситуації уникнути саме тимоб оскільки і розмір буферу/сторінки 
мікросхеми dataFlash є кратним 2, розмір миттєвої виборки є кратним 2, то і розмір 
заголовку аналогового реєстратора має бути кратним 2.!!!
48 є кратним 2 - отже все нормально!

Тобто розмір максимального аналогового запису 1056000+48 = 1056048(байти)
З урахуванням того, що розмір сторінки DF становить 512 байт, то максимальний
аналоговий запис становить 1056048/512 = 2062.59375 сторінки. Значить буде вестися 
запис у 2063 сторінки DF.

Читання зовнішнбої SRAM становить 85(нс)  - це випливає з настройок FSMC. Тоді для копіювання 512 
байт з зовнішньої SRAM у внутрішню SRAM становить 512(байт)х85(нс)=43,52(мкс)

DF(DataFlsh) обмінюється з центральним мікроконтролером через SPI1, який настроєний
на швидкість обміну 30МБіт/с і передає 8 біт інформації. Тобто швидкість обміну 
становить 3,75МБайти/с.

З увахуванням швидкості обміну і ширин пакетів виходіть такі часи

1)Запис 512 байт у DF операцією "Main Memory Page Program Through Buffer" < 40,138(мс)
2)Читання сторінки у буфер операцією "Main Memory Page to Buffer Transfer" < 202(мкс)
3)Модифікація до 512 байт у буфері DF операцією "Buffer Write" < 138(мкс)
4)Запис буферу DF у DF операцією "Buffer to Main Memory Page Program with 
Built-in Erase" < 40,002(мс)

Для запису цілої сторінки треба виконати операції:
зкопіювати 512 байт з зовнішньої SRAM у внутрішню SRAM < 43,52(мкс)
Виконати операцю "Main Memory Page Program Through Buffer" < 40,070(мс)
Періодично читати біт статусу, який перевіряєиться кожні 2мс (бо іде чергування
DataFlash1/DataFlash2). Тому за 41 мс ця опеація має гарантовано виконатися.
Для перестраховки приймемо значення 45 мс.

Для модифікації до 512 байт на одній сторінці треба:
скопіювати 512 байт з зовнішньої SRAM у внутрішню SRAM < 43,52(мкс)
Виконати операцю "Main Memory Page to Buffer Transfer" < 202(мкс)

Через 2(мс) запуститься операція перевірки біту статусу (див. пояснення вище) який 
теоретично має бути у дозволеному стані бо 202(мкс) < 2 (мc)
Ще черзе 2(мс (див. пояснення вище) можна запускати операцію модифікаціїмайт у буфері.
Тобто затримка між операціями складе 4(мс)
Тобто реально затримка буде не 202(мкс), а 4(мс)

Виконати модифікацію байт у буфері DF < 138(мкс) 

Через 2(мс) запустится операція перевірки біту статусу (див. пояснення вище) який 
теоретично має бути у дозволеному стані бо 202(мкс) < 2 (мc)
Це черзе 2(мс) (див. пояснення вище) можна запускати операцію запису у буфер.
Тобто затримка між операціями складе 4(мс)
Тобто реально затримка буде не 138(мкс), а 4(мс)

Виконати операцю "Buffer to Main Memory Page Program with 
Built-in Erase" < 40,002(мс)
Періодично читати біт статусу, який перевіряєиться кожні 2мс (див. пояснення вище).
Тому за 41 мс ця опеація має гарантовано виконатися.
Сумарний час:
43,46(мкс)+4(мс)+4(мс)+41(мс) = 50(мс)
Для перестраховки приймемо значення 51 мс.

Теоретично тільки перша і остання сторінки будуть записуватися довшою операцією
(зі модифікацієб вмістимого буферу) а всі решта будуть зприсуватися простішою
операцією, але щоб гарантовано не було переповнення - зробимо розрахунок, коли сторінки
записуються з більшим часом - 51(мс)

Тоді для запису 2063 сторінок треба буде
2063(сторінки)х51(мс) = 105 213(мс)=105,213(с)

Тобто процес запису максимального аналогового запису буде тривати 105,213(с)

Швидкість "заповнення" миттєвими виборками і дискретними сигналами з вимірювальної системи:
(9(канали) + 13(двобайтні слова дискретних сигналів))х2(байти на значення)/1,25(мс
- інтервал між виборками при частоті 50Гц і 16 виборок на період) =35,2 (байт/мс)
Причому це значення є точним, бо ми не робили тут ніяких припущень чи заокуркглень

Швидкісь "вигрузки" запису аналогового реєстратора у DF:
2063(сторінки)х512(байт на сторінку)/105213(мс) = 10.039215686274509803921568627451 (байт/мс)
Причому це значення не є точним, тому що ми тут робили заокруглення. Тобто, реально,
швидкіть має бути ще вищою, бо заокруглення робилися у 
сторону найгіршого випадку якого би взагалі не мало бути, зокрема, що всі сторінки 
записються за 51(мс) - час операції запису через модифікацію вмістимого буферу(
див. пояснення вище)).

Наростання вмістимого буферу при "заповненні" по відношенню до "вигрузки
буде виконуватися зі швидкістю: 35,2 - 10.039215686274509803921568627451 = 25.160784313725490196078431372549(байт/мс)
Це наростання буде здійснюватичся поки виконується "заповнення", тобто максимально
можливий час 25(с)  -максимальний час післяаварійного масиву.
25000(мс)*25.160784313725490196078431372549(байт/мс) = 629019.60784313725490196078431373(байт) < 629020(байт)
629020(байт)/512(байт/стор.) = 1228.5546875(сторінок) < 1229(сторінок)

Крім того треба мати на увазі те, що у записі аналогового реєстратора є 60 байт
інформації по запису (міктка початку запису, час, коефіцієнти трансформації, ім'я
комірки). При умові рівності швидкостей "заповнення" і "вигрузки" ця різниця між міткою
останнього "заповнення" і міткою останньої "вигрузки" мала б зберегтися. При умові, що
швидкіть "вигрузки" буде більшою за швидкіть "заповнення" - то з часом "вигрузка"
дожене "заповнення" і буде працювати по мірі появи даних.

На основі вищевикладених роздумів я роблю висноок, що розмір масиву тимчасового 
зберігання миттєвих значень мало б вистарчити у (розмір доаварійного масису + 
(1229 + 1) сторінки DF). Ще одну сторінку до 1230 теоретично розрахованих я додав 
для перестаховки.

Тобто розмір має бути
5(с - макс. доавар. мас.)х50(пром.частота)х16(кільк. вибор.за пер. для ан.р.)х(9(канали) + 13(двобайтні слова дискретних сигналів)) +1230*[512(байт)/2(байт на одне миттєве значення)](кількість миттєвих значень на сторінці)=
= 88000 +1230х256 = 402880

Число має бути кратним (кількості аналогових каналів + кількості двобайтних слів дискретних сигналів).
Це треба для того, щоб не слідкувати при кожному записі чи ми не вийшли за масив, а 
цей контроль здійснювати при записі всього зрізу
Перший доданок гарантовано є кратним кількості (кількості аналогових каналів + 
кількості двобайтних слів дискретних сигналів), бо він формується
монжником, який називається "кількість ан.каналів + двобайтні слова дискретних сигналів"
Тому треба слідквати за другим доданком
1230(сторінок)х256(слів) = 314880 (слів)

314880/(9 + 13)= 14312.727272727272727272727272727
Якщо ділення не є ціле число, то треба провести корекцію, щоб Х/(9 + 13)
давало ціле число, причому Х > 314886 - тобто беремо найслижче число X = 314886

таким чином
88000 + 314886 = 402886

!!!Вищевикладена дає мені підставу ширину масиву встановити 402886 елементи (двохбайтені,
так як кожна виборка складається із двох байт)!!!

*/

#define SIZE_BUFFER_FOR_AR    100/*402886*/

#define CLEAN_AR_BIT          0
#define CLEAN_AR              (1 << CLEAN_AR_BIT)
#define CLEAN_DR_BIT          1
#define CLEAN_DR              (1 << CLEAN_DR_BIT)
#define CLEAN_PR_ERR_BIT      2
#define CLEAN_PR_ERR          (1 << CLEAN_PR_ERR_BIT)

#endif
