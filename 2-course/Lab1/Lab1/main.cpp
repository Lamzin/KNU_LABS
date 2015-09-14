#include <iostream>
#include <fstream>

using namespace std;

#include "types.h" 
#include "generators.h"

RandomGenerator *choose_generator();
ui32 choose_length_of_sequence();

void print_sequence(RandomGenerator *Generator, ui32 length);
void print_histogram(Histogram *histogram);

int main(){
	
	RandomGenerator *Generator = choose_generator();
	int length = choose_length_of_sequence();


	print_sequence(Generator, length);
	
	print_histogram(Generator->get_histogram());


	return 0;
}


RandomGenerator *choose_generator(){
	int numb;

	do{
		cout << "Number of algorithm = ";
		cin >> numb;

		switch (numb)
		{
			case 1:
				return new LinearCongruential();
				break;
			case 2:
				return new QuadraticCongruential();
				break;
			case 3:
				return new FibonacciMethod();
				break;
			case 4:
				return new InversiveCongruential();
				break;
			case 5:
				return new ShufflingMethod();
				break;
			case 6:
				return new StandardDeviation();
				break;
			case 7:
				return new PolarCoordinates();
				break;
			case 8:
				return new RatioMethodForNormalDeviates();
				break;
			case 9:
				return new LogarithmMethod();
				break;
			case 10:
				return new GammaDistribution();
				break;
			default:
				cout << "Error! Try again!\n";
				break;
		}

	} while (numb > 0 && numb < 11);

	return NULL;
}


ui32 choose_length_of_sequence(){
	ui32 length;

	cout << "\nLength of sequence = ";
	cin >> length;

	return length;
}


void print_sequence(RandomGenerator *Generator, ui32 length){
	fstream file("sequence.txt", ios::out);

	for (int i = 0; i < length; i++){
		file << Generator->next() << " ";
	}

}


void print_histogram(Histogram *histogram){
	fstream file("histogram.txt", ios::out);
	
	for (auto it = histogram->statistic.begin(); it != histogram->statistic.end(); it++){
		file.precision(3);
		file << fixed << "[ " << static_cast<f64>(it->first) / histogram->coefficient << " , " << static_cast<f64>(it->first + 1) / histogram->coefficient << " ] - ";
		file << fixed << static_cast<f64>(it->second * 100) / histogram->count << "%" << endl;
	}

}