#include "mbed.h"
#include "adrobo.h"

BusOut led(LED1,LED2,LED3,LED4,LED5,LED);
BusIn sw(SW1, SW2);
AnalogIn ad[] = {AD1, AD2, AD3};
PwmOut servo1(SERVO1), servo2(SERVO2), servo3(SERVO3);

int main() {
	servo1.period_ms(20);
  servo2.period_ms(20);
  servo3.period_ms(20);
	sw.mode(PullUp);
	int i = 425, j = 3100 - 2 * i, k = 1300;
  float value1, value2, value3;
	
	
  while(1) {
		value3 = ad[2].read();
    printf("%f\r\n", value3);
    wait(0.2);
	  if(value3 <= 0.014){ 
	  	led = led | 0x01;
			for(; i <= 900; i += 25) {
				j = 3100 - 2 * i;
				servo1.pulsewidth_us(i);
				servo2.pulsewidth_us(j);
				wait(0.1);
			}
			/*wait(0.2);*/
			k = 500;
			servo3.pulsewidth_us(k);
      wait(0.2);
			while(1) {
				value1 = ad[0].read();
		  	value2 = ad[1].read();
				printf("v1 %f\r\n", value1);
			  printf("v2 %f\r\n", value2);
        wait(0.2);
				
        if (value1 >= 0.5 && 	value2 >= 0.5){
					while(1){
						value1 = ad[0].read();
		  	    value2 = ad[1].read();	
						printf("w1 %f\r\n", value1);
					  printf("w2 %f\r\n", value2);
						printf("servo1 %d\r\n", i);
					  printf("servo2 %d\r\n", j);						
            wait(0.2);
						
						if (value1 - value2 >= 0.1){
							if (i <= 1300){
								i = i + 25;
								j = 3100 - 2 * i;
								servo1.pulsewidth_us(i);
								servo2.pulsewidth_us(j);						
							}	
              wait(0.1);							
						}
						
						if (value2 - value1 >= 0.1){
							if (i >= 450){
								i = i - 25;
								j = 3100 - 2 * i;
								servo1.pulsewidth_us(i);
								servo2.pulsewidth_us(j);	
							}
							wait(0.1);	
						}		
						
						if (value1 <= 0.5 || value2 <= 0.5){
							break;
						}
					}
				}
				
				if ((sw & 0x01) == 0) {				
					i = 1350;
					j = 900;
					servo1.pulsewidth_us(i);
          servo2.pulsewidth_us(j);
					led = led | 0x02;
					wait(0.3);
					
					while(1) {
				    value1 = ad[0].read();
		       	value2 = ad[1].read();
						printf("x1 %f\r\n", value1);
						printf("x2 %f\r\n", value2);
						wait(0.2);
				
						if (value1 >= 0.5 && 	value2 >= 0.5){
							while(1){
								value1 = ad[0].read();
								value2 = ad[1].read();	
								printf("y1 %f\r\n", value1);
								printf("y2 %f\r\n", value2);
								printf("servo1 %d\r\n", i);
								printf("servo2 %d\r\n", j);
					
								wait(0.2);
						
								if (value1 - value2 >= 0.1){
									if (j >= 450){
										j = j - 25;
										servo2.pulsewidth_us(j);						
									}	
									wait(0.1);							
								}
				
								if (value2 - value1 >= 0.1){
									if (j <= 2250){
										j = j + 25;
										servo2.pulsewidth_us(j);	
									}
									wait(0.1);	
								}		
					
							  if (value1 <= 0.5 || value2 <= 0.5){
									break;
								}
							}
						}
						if ((sw & 0x01) == 0) {		
							break;
						}
					}
					/*j = 1300;
					servo2.pulsewidth_us(j);*/
					for(; i >= 900; i -= 25) {
						j = 1300;
					  servo2.pulsewidth_us(j);
					  servo1.pulsewidth_us(i);
						wait(0.1);
					}	
				}
				
				if ((sw & 0x02) == 0) {
					break;
				}
			}		
			for(; i >= 425; i -= 25) {
				j = 3100 - 2 * i;
				servo1.pulsewidth_us(i);
				servo2.pulsewidth_us(j);
				wait(0.1);
			}
			/*wait(0.2);*/
			k = 1300;
			servo3.pulsewidth_us(k);
			wait(60);		
		}
	}
}
