/*
* file: tradingstocks.c
* author: Kristian Murphy
* ticker: KALU
* date: November 6, 2018
*/

#include <stdio.h>
#include <string.h>

#define MAX_PRICES 30

// prototypes
void banner();
void readPrices(char* fileName, int priceCapacity, double* pPrices, int* pricesSize);
double getMinPrice(double* pPrices, int pricesSize);
double getMaxPrice(double* pPrices, int pricesSize); 
void profitableTrades(double* pPrices, int pricesSize, double* pProfits, int* pProfitsSize);
void save(char* pricesFilename, double* pProfits, int profitsSize);
void print(double* pProfits, int profitsSize, double maxPrice, double minPrice);

// definitions
void banner()
{
	printf("Welcome to the KALU stocks program\n_____________________________\n\n");
}

void readPrices(char* pricesFilename, int priceCapacity, double* pPrices, int* pPricesSize)
{
	float price;
	int i = 0;
	*pPricesSize = 0;
	
	FILE* pFile = 0;
	pFile = fopen(pricesFilename, "r");

	if(pFile){
		while(fscanf(pFile, "%f", &price)>0){
			pPrices[i] = price;
			i++;
			*pPricesSize = i;
		}
		
	}else{
	// Error Message if file could not be opened
		printf("Could not find file %s to open for reading", pricesFilename);
	}

	if(pFile) fclose(pFile);
}

void profitableTrades(double* pPrices, int pricesSize,double* pProfits, int* pProfitsSize)
{
	int j;
	int i;
	int r = 0;
	double buy;
	double sell;
	double profit;
	double maxLocalProfit;
	
    //...
     for(i=pricesSize-1;i>=0;i--){    

		  buy = pPrices[i];
		  
        for(j=i+1;j>=0;j--){ 
			sell = pPrices[j];

			profit = sell - buy;
			
			if (profit > maxLocalProfit){
				maxLocalProfit = profit;
			}

           }
			pProfits[r] = maxLocalProfit; 
			r++;
			maxLocalProfit = -100; 
     }

	 *pProfitsSize = r;
}

void save(char* profitsFilename, double* pProfits, int profitsSize)
{
	FILE* pFile = 0;
	pFile = fopen(profitsFilename, "w");

	if(pFile){

		int x;
		for(x=0; x<profitsSize; x++){
			fprintf(pFile, "%.2f\n", pProfits[x]);
		}
		
	}else{
		// error message - reading
		printf("Could not find file %s to open for writing", profitsFilename);
	}
	if(pFile) fclose(pFile);
}

double getMaxPrice(double* pPrices, int pricesSize){
	double maxNum = pPrices[0];
	int i = 0;
	
	for(i=0;i<pricesSize;i++){
		if(pPrices[i] > maxNum){
			maxNum = pPrices[i];
		}
	}
	return(maxNum);
}

double getMinPrice(double* pPrices, int pricesSize){
	double minNum = pPrices[0];
	int i = 0;
	
	for(i=0;i<pricesSize;i++){
		if(pPrices[i] < minNum){
			minNum = pPrices[i];
		}
	}
	return(minNum);
}

void print(double* pProfits, int profitsSize, double maxPrice, double minPrice)
{
	int y;
	printf("High closing price - %.2f \nLow closing price - %.2f \n", maxPrice, minPrice);
	printf("Possible profits - \n");
	for(y=0; y<profitsSize; y++){
		printf("%.2f\n", pProfits[y]);
	}
	int i;
	double maxProfit = pProfits[0];
	for(i=0;i<profitsSize;i++){
		if(pProfits[i] > maxProfit){
			maxProfit = pProfits[i];
		}
	}
	printf("\nHighest profit - %.2f \n", maxProfit);
}

void test()
{
	char* pricesFilename = "prices.txt";
	char* profitsFilename = "profits.txt";
	int pricesCapacity = MAX_PRICES;
	double prices[MAX_PRICES];
	double profits[MAX_PRICES];
	double maxPrice;
	double minPrice;
	int pricesSize;
	int profitsSize;

		banner();
		
		readPrices(pricesFilename , pricesCapacity, prices, &pricesSize);
		
		maxPrice = getMaxPrice(prices, pricesSize); 
		
		minPrice = getMinPrice(prices, pricesSize); 
		
		profitableTrades(prices, pricesSize, profits, &profitsSize);
				
		save(profitsFilename, profits, profitsSize);
		
		print(profits, profitsSize, maxPrice, minPrice);
}

int main(int argc, char **argv)
{
	test();
	return 0;
}
