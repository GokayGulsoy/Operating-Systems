#include <stdio.h>

float calculate_square(float val) { 
	return val * val;
}

void calc_and_print_area(float radius) {
	float PI = 3.14;
	float area = PI * calculate_square(radius); 
	printf("Area: %f\n", area);
}

int main() {
	float r;
	printf("Radius: ");
	scanf("%f", &r); 
	calc_and_print_area(r); 
	return 0;
}
