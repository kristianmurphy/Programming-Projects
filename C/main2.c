/**


*Date: 2018/09/05

**/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <unistd.h>

/* Citation links:
* 
* formula: http://www.healthfitonline.com/resources/harris_benedict.php
* research: https://www.verywellfit.com/how-many-calories-do-i-burn-every-day-3495464
* 
*/

#define MAXIMUM 600
#define MINIMUM 20
#define MAXIMUMAGE 100
#define MINIMUMAGE 1
#define MAXIMUMHEIGHT 96
#define MINIMUMHEIGHT 12

int main()
{
	// Var
		int j = 2;
		int i = 1;
		int age;
		char retry;
		double weight;
		double height;
		double man;
		double woman;
	
	// Restart
		while(i <= 10) {
			
		// Banner
			printf("Welcome to the calorie calculator!\n");
			printf("______________________________________________\n\n");
			sleep(1);
	
	// Input
			do{
				printf("Please enter your weight, between %d and %d\n",MINIMUM, MAXIMUM);
				scanf("%lf",&weight);
			}while (weight>MAXIMUM || weight<MINIMUM);

			do{
				printf("Please type your height in terms of inches, between 12 and 96 inches\n");
				scanf("%lf",&height);
			}while (height>MAXIMUMHEIGHT || weight<MINIMUMHEIGHT);
			
			do{
				printf("Please type your age in terms of years, between 1 and 100.\n");
				scanf("%d",&age);
			}while (age>MAXIMUMAGE || age<MINIMUMAGE);

	// Calorie
			man = 66 + (6.23 * weight) + (12.7 * height) - (6.8 * age);
			woman = 655 + (4.35 * weight);
	
	// Output
			printf("\n Statistics:\n");
			printf("Weight: %1lf pounds, \n",weight);
			printf("Height: %1lf inches, \n",height);
			printf("Age: %d years, \n\n",age);
			printf("\n (Based on the statistics stated above)\n\n");
			printf(" Calories, specified for both man and woman metabolic systems: \n");
			printf("Man: %1lf calories, \n", man);
			printf("Woman: %1lf calories \n", woman);
			
	// Restart
			while(j == 2){
					i = 2;
					j = 1;
					printf("Would you like to [c] close or [r] retry this program? [c/r] - \n");
					scanf(" %c", &retry);
					if(retry == 'r'){
						printf("retrying...");
						i++;
				}else if(retry == 'c'){
						printf("Weight: %1lf pounds, \n",weight);
						printf("Height: %1lf inches, \n",height);
						printf("Age: %d years, \n",age);
						printf("\n (Based on the statistics stated above)\n\n");
						printf(" Calories, specified for both man and woman metabolic systems: \n");
						printf("Man: %1lf calories, \n", man);
						printf("Woman: %1lf calories \n", woman);
						printf("\n Thanks for using this program!");
						i == 11;
				}else{
						printf("Would you like to [c] close or [r] retry this program? [c/r] - \n");
						j = 2;
			}
		}
	}

	
}
