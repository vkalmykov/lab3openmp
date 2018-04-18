#define _USE_MATH_DEFINES
#include <stdio.h>
#include <omp.h>
#include <cstdlib>
#include <cmath>

int main(int argc, char* argv[]) {
	long number, h;
	double x, sum, startTime, resultSum;
	while (true)
	{
		number = h = 0;
		x = sum = startTime = resultSum = 0.0;
		printf("Enter number: ");
		scanf("%d", &number);
		if (number <= 0) {
			break;
		}
		startTime = omp_get_wtime();
		h = 2 * number;
		resultSum = sum = 0;
#pragma omp parallel firstprivate(sum) private(x) shared(number, resultSum, h)
		{
#pragma omp for schedule(guided, 10) nowait
			for (int g = 0; g < number; g++) {
				x = (2.0 * g*1.0 - 1.0) / h*1.0;
				sum += 4.0 / (1.0 + x * x);
			}
			sum *= 1.0 / number;
#pragma omp atomic 
			resultSum += sum;
		}
		printf("Result is %2.15f, error of value %2.15f\nRun time in seconds: %2.6f\n", resultSum, resultSum - M_PI, omp_get_wtime() - startTime);
	}
	std::system("pause");
	return 0;
}