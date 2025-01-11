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

int main()
{
	// Var
	double weight;
	double height;
	int age;
	double man;
	double woman;
	
	// Banner
	printf("Welcome to the calorie calculator.\n");
	printf("______________________________________________\n\n");
	sleep(1);
	
	// Input
	printf("Please type your weight in terms of pounds.\n");
	scanf("%lf",&weight);
	printf("Please type your height in terms of inches.\n");
	scanf("%lf",&height);
	printf("Please type your age in terms of years.\n");
	scanf("%d",&age);
	
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
	
	return 0;
}
