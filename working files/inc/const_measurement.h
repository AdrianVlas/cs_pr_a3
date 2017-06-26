#ifndef __CONST_MESUREMENT__
#define __CONST_MESUREMENT__

#define USTUVANNJA_VAGA 12
#define DEFAULT_USTUVANNJA_VALUE ((1<<USTUVANNJA_VAGA) - 1)

#define MEASUREMENT_TIM_FREQUENCY       60000000 //МГц

#define MAIN_FREQUENCY  50      //Гц

#define NUMBER_ADCs                     1
#define NUMBER_CANALs_ADC               16
#define NUMBER_INPUTs_ADCs              (NUMBER_ADCs*NUMBER_CANALs_ADC)

#define VAGA_NUMBER_POINT                5
#define NUMBER_POINT                     (1 << VAGA_NUMBER_POINT)

#define NUMBER_PERIOD_TRANSMIT           10

/*
Коефіцієнт, який переводить число з АЦП у мА
          2500
Koef = ------------
        R*K*0xFFF
де:
K - коефіцієнт передачі і він рівний 8.2
2500 - максимальне значення напруги у мілівольтах, яке може оцифрувати АЦП (у нас це є 2,5 В = 2500 мВ)
R - резистор, який перетворює трансформований струм у напругу. Зараз стоїть 0,05 Ом
0xFFF - максимальне число, яке може видати АЦП

Koef = 1,4890258792697817088060990500015 для фазних струмів (3/2 = 1.5) 

Множення на ці коефіцієнти переводять одиниці АЦП у мА

Але коли ми проводимо розрахунки з допомогою перетворення Фур'є, то результатом є амплітуда 1-ої  агмоніки (або інших гармонік. якщо розрахунок би йшов по них)
Тому крім цього коефіцієнта треба ще поділити на корінь з двох.
для простоти зробимо узагальнений коефіцієнт, що є результатом Koef_1 = Koef/sqrt(2)

Koef_1 = 1,0529002965939240662331283869455 для фазних струмів (539/512 = 1,052734375)
*/

#define MNOGNYK_I                     3           
#define VAGA_DILENNJA_I               1
#define MNOGNYK_I_DIJUCHE             539          
#define VAGA_DILENNJA_I_DIJUCHE       9
#define MNOGNYK_I_DIJUCHE_FLOAT       1.0529002965939240662331283869455f

/*
Коефіцієнт, який переводить число з АЦП у мВ
       2500(2R1+R)
Koef = ------------
        R*K*0xFFF
де:
K - коефіцієнт передачі і він рівний 8.2
2500 - максимальне значення напруги у мілівольтах, яке може оцифрувати АЦП (у нас це є 2,5 В = 2500 мВ)
R - резистор, з якого напруга знімається. Зараз стоїть 5 Ом
R1 - опір двох додаткових резмсторів у дільнику напруги. Зараз стоять по 50 кОм
0xFFF - максимальне число, яке може видати АЦП

Koef = 1489,100330563745197891539354954 для фазних напруг (1489/1 = 1489) 

Множення на ці коефіцієнти переводять одиниці АЦП у мВ

Але коли ми проводимо розрахунки з допомогою перетворення Фур'є, то результатом є амплітуда 1-ої  агмоніки (або інших гармонік. якщо розрахунок би йшов по них)
Тому крім цього коефіцієнта треба ще поділити на корінь з двох.
для простоти зробимо узагальнений коефіцієнт, що є результатом Koef_1 = Koef/sqrt(2)

Koef_1 = 1052,9529416087537624364400433648 для фазних струмів (1053/1 = 1053)
*/

#define MNOGNYK_U                     1489           
#define VAGA_DILENNJA_U               0
#define MNOGNYK_U_DIJUCHE             1053           
#define VAGA_DILENNJA_U_DIJUCHE       0
#define MNOGNYK_U_DIJUCHE_FLOAT       1052.9529416087537624364400433648f


#define GND_NORMAL_VALUE                0x0
#define VREF_NORMAL_VALUE               0x800
#define VDD_NORMAL_VALUE                0xb00

//Канали
#define C_GND_ADC_1             0
#define C_I1_1                  1
#define C_I1_16                 2
#define C_I2_1                  3
#define C_I2_16                 4
#define C_I3_1                  5
#define C_I3_16                 6
#define C_U_1                   7
#define C_U_16                  8
#define C_U_256                 9
#define C_GND_ADC_2             10
#define C_GND_ADC_3             11
#define C_GND_ADC_4             12
#define C_GND_ADC_5             13
#define C_VREF_ADC              14
#define C_VDD_ADC               15

#define READ_AIN   (                            \
                    (1 << C_I1_1   ) |          \
                    (1 << C_I1_16  ) |          \
                    (1 << C_I2_1   ) |          \
                    (1 << C_I2_16  ) |          \
                    (1 << C_I3_1   ) |          \
                    (1 << C_I3_16  ) |          \
                    (1 << C_U_1    ) |          \
                    (1 << C_U_16   )            \
                   )

#define READ_DATA_VAL  (            \
                         READ_AIN   \
                       )

#define READ_TEST_VAL  (                                 \
                        (1 << C_GND_ADC_1)             | \
                        (1 << C_GND_ADC_2)             | \
                        (1 << C_GND_ADC_3)             | \
                        (1 << C_GND_ADC_4)             | \
                        (1 << C_GND_ADC_5)             | \
                        (1 << C_VREF_ADC )             | \
                        (1 << C_VDD_ADC  )               \
                       )

#define DATA_VAL_READ_BIT         0
#define DATA_VAL_READ             (1 << DATA_VAL_READ_BIT)
#define TEST_VAL_READ_BIT         1
#define TEST_VAL_READ             (1 << TEST_VAL_READ_BIT)

#define NUMBER_GND_ADC          5

#define I_I1          0
#define I_I2          1
#define I_I3          2
#define I_I4          3
#define I_U           4

#define IM_I1         0
#define IM_I2         1
#define IM_I3         2
#define IM_I4         3
#define IM_U          4

#endif
