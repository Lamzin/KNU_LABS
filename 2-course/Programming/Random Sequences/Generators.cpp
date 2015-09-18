#include <math.h>


#include "types.h"
#include "generators.h"
#include "config.h"

f64 RAND(){
	return (static_cast<f64>(static_cast<ui64>(rand()) * RAND_MAX + rand()) / (RAND_MAX * RAND_MAX + 1));
}

ui64 RAND_ui64(){
	return (static_cast<ui64>(rand()) * RAND_MAX + rand()) % (RAND_MAX * RAND_MAX + 1);
}

//*********************************************************
//0

RandomGenerator::RandomGenerator(){
	//histo = new Histogram();
}

RandomGenerator::~RandomGenerator(){
	delete histo;
}

Histogram *RandomGenerator::get_histogram(){
	return histo;
}

std::string RandomGenerator::__doc__(){
	return __doc;
}

ui32 RandomGenerator::next(){
	return static_cast<ui32>(this->next_f64() * modulo);
}

f64 RandomGenerator::next_f64(){
	return static_cast<f64>(this->next()) / modulo;
}



//********************************************************
//1
LinearCongruential::LinearCongruential(){
	histo = new Histogram(0.0f, 1.0f, 10.0f);
	
	numb0 = LINEAR_NUMB_0;
	a = LINEAR_A;
	c = LINEAR_C;
	modulo = LINEAR_MODULO;
}

ui32 LinearCongruential::next(){
	numb1 = (numb0 * a + c) % modulo;
	histo->add(static_cast<f64>(numb1) / modulo);

	return numb0 = numb1;
}



//********************************************************
//2
QuadraticCongruential::QuadraticCongruential(){
	histo = new Histogram(0.0f, 1.0f, 10.0f);

	numb0 = QUADRATIC_NUMB_0;
	a = QUADRATIC_A;
	c = QUADRATIC_C;
	d = QUADRATIC_D;
	modulo = QUADRATIC_MODULO;
}

ui32 QuadraticCongruential::next(){
	numb1 = (numb0 * ((d * numb0 + a) % modulo) + c) % modulo;
	histo->add(static_cast<f64>(numb1) / modulo);
	return numb0 = numb1;
}



//********************************************************
//3
FibonacciMethod::FibonacciMethod(){
	histo = new Histogram(0.0f, 1.0f, 10.0f);


	numb0 = FIBONACCI_NUMB_0;
	numb1 = FIBONACCI_NUMB_1;
	modulo = FIBONACCI_MODULO;
}

ui32 FibonacciMethod::next(){
	numb2 = (numb0 + numb1) % modulo;
	numb0 = numb1;
	numb1 = numb2;
	histo->add(static_cast<f64>(numb2) / modulo);
	return numb2;
}



//********************************************************
//4
InversiveCongruential::InversiveCongruential(){
	histo = new Histogram(0.0f, 1.0f, 10.0f);


	numb0 = INVERSIVE_NUMB_0;
	a = INVERSIVE_A;
	c = INVERSIVE_C;
	modulo = INVERSIVE_MODULO;
}

ui64 InversiveCongruential::reverse_element(ui64 num){
	//http://e-maxx.ru/algo/reverse_element
	ui64 res = 1, pow = 1;
	while (pow <= (modulo - 2)){
		if (pow & (modulo - 2)){
			res *= num;
		}

		num = (num * num) % modulo;
		pow <<= 1;
	}

	return res;
}


ui32 InversiveCongruential::next(){
	if (numb0 == 0) numb0 = RAND_ui64() % modulo;

	numb1 = (a * reverse_element(numb0) + c) % modulo;
	histo->add(static_cast<f64>(numb1) / modulo);
	return numb0 = numb1;
}



//********************************************************
//5
ShufflingMethod::ShufflingMethod(){
	histo = new Histogram(0.0f, 1.0f, 10.0f);


	X = new LinearCongruential();
	Y = new QuadraticCongruential();
	modulo = SHUFFLING_MODULO;
}

ui32 ShufflingMethod::next(){
	numb0 = (X->next() + (modulo - Y->next())) % modulo;
	histo->add(static_cast<f64>(numb0) / modulo);
	return numb0;
}



//*********************************************************
// #6
StandardDeviation::StandardDeviation(){
	histo = new Histogram(-10.0f, 10.0f, 1.0f);

	sum = 0.0f;
	Gen = new LinearCongruential();
	for (int i = 0; i < 12; i++){
		//arr[i] = RAND();
		arr[i] = Gen->next_f64();
		sum += arr[i];
	}
	modulo = STANDART_DEVIATION_MODULO;
}

f64 StandardDeviation::next_f64(){
	sum -= arr[0];
	for (int i = 1; i < 12; i++){
		arr[i - 1] = arr[i];
	}
	
	//arr[11] = RAND();
	arr[11] = Gen->next_f64();
	sum += arr[11];

	histo->add(sum - 6);
	return sum - 6;
}



//*********************************************************
// #7
PolarCoordinates::PolarCoordinates(){
	histo = new Histogram(-10.0f, 10.0f, 1.0f);


	Gen = new LinearCongruential();
	modulo = POLAR_COORDINATES_MODULO;
	start = true;
}

f64 PolarCoordinates::next_f64(){
	if (start){
		start = false;
		
		do {
			V1 = 2 * Gen->next_f64() - 1;
			V2 = 2 * Gen->next_f64() - 1;
			//V1 = 2 * RAND() - 1;
			//V2 = 2 * RAND() - 1;

			S = V1 * V1 + V2 * V2;
		} while (S >= 1.0f);
		
		numb0 = V1 * sqrt(-2 * log(S) / S);
		numb1 = V2 * sqrt(-2 * log(S) / S);
		
		histo->add(numb0);
		return numb0;
	}
	else{
		start = true;
		histo->add(numb1);
		return numb1;
	}

}



//*********************************************************
// #8 // Knuth 2t p131
RatioMethodForNormalDeviates::RatioMethodForNormalDeviates(){
	histo = new Histogram(-10.0f, 10.0f, 1.0f);


	Gen = new LinearCongruential();
	modulo = RATIO_MODULO;
}

f64 RatioMethodForNormalDeviates::next_f64(){
	
	do{
		do{
			U = Gen->next_f64();
			//U = RAND();
		} while (U < 0.000001f);

		V = Gen->next_f64();

		numb0 = sqrt(8 / exp(1.0f)) * (V - 0.5f) / U;

	} while (numb0 * numb0 > -4 * log(U) || numb0 * numb0 < 4 * exp(-1.35) / U + 1.4);

	histo->add(numb0);
	return numb0;
}


//*********************************************************
// #9 // Knuth 2volume page133 // Exponential Distribution
LogarithmMethod::LogarithmMethod(){
	histo = new Histogram(-5.0f, 5.0f, 10.0f);


	Gen = new LinearCongruential();
	modulo = LOGARITHM_MODULO;
	mu = LOGARITHM_MU;
}

f64 LogarithmMethod::next_f64(){
	
	numb0 = log10(Gen->next_f64()) * mu;
	histo->add(numb0);
	return numb0;
}



//*********************************************************
// #10 // Knuth 2volume page134
GammaDistribution::GammaDistribution(){
	histo = new Histogram(-10.0f, 10.0f, 1.0f);


	Gen = new LinearCongruential();
	modulo = GAMMA_MODULO;
	a = GAMMA_A;
}

f64 GammaDistribution::some_value(){
	return (1 + Y * Y) * exp((a - 1) * log(X / (a - 1)) - sqrt(2 * a - 1)*Y);
}

f64 GammaDistribution::next_f64(){

	do{
	
		U = Gen->next_f64();
		//U = RAND();
		Y = tan(PI * U);
		X = sqrt(2 * a - 1) * Y + a - 1;

	} while (X <= 0.0f || Gen->next_f64() > some_value());

	histo->add(X);
	return X;
}
