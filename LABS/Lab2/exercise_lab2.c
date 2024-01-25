#include <stdio.h>

int main() {
	int num1, num2, sum, i; 
	printf("Enter the first positive integer: ");
	scanf("%d", &num1);

	while(num1 < 1) {
		printf("Invalid input. Please enter the first positive integer again:");
		scanf("%d", &num1);
	}

	printf("\nEnter the second positive integer: ");
	scanf("%d", &num2);

	while(num2 < 1) {
		printf("Invalid input. Please enter the second positive integer again:");
		scanf("%d", &num2);
	}

	sum = num1 + num2;
	printf("\n%d + %d = %d can be visualized as the following:\n\n", num1, num2, sum);

	for(i=1; i<=num1; i++) {
		printf("* ");
	}
	printf("+ ");
	for(i=1; i<=num2; i++) {
		printf("* ");
	}
	printf("= ");
	for(i=1; i<=sum; i++) {
		printf("* ");
	}
	printf("\n\n");

	return 0;
}
