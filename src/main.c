#include <stdio.h>
#include <math.h>
#include <stdbool.h>

void solve_opt_f(float delta, float *x1, float *x2) {
	// solve system 2 using float variables and optimizations
	float A = 2, difference_between_B_and_A = 1e-4, C_minus_1 = 1e-4;
	*x2 = (difference_between_B_and_A + delta) / C_minus_1;
	*x1 = A - *x2;
}

void solve_no_opt_f(float delta, float *x1, float *x2) {
	// solve system 2 using float variables
	float A = 2, B = 2 + 1e-4, C = 1 + 1e-4;
	*x2 = (B - A + delta) / (C - 1);
	*x1 = A - *x2;
}

void solve_opt_d(double delta, double *x1, double *x2) {
	// solve system 2 using double variables and optimizations
	double A = 2, difference_between_B_and_A = 1e-4, C_minus_1 = 1e-4;
	*x2 = (difference_between_B_and_A + delta) / C_minus_1;
	*x1 = A - *x2;
}

void solve_no_opt_d(double delta, double *x1, double *x2) {
	// solve system 2 using double variables
	double A = 2, B = 2 + 1e-4, C = 1 + 1e-4;
	*x2 = (B - A + delta) / (C - 1);
	*x1 = A - *x2;
}

bool validate_solution_opt_f(float x1, float x2) {
	float true_x1 = 1, true_x2 = 1, square_of_eps = 1e-12;
	return ((true_x1 - x1) * (true_x1 - x1) + (true_x2 - x2) * (true_x2 - x2) <= square_of_eps);
}

bool validate_solution_no_opt_f(float x1, float x2) {
	float true_x1 = 1, true_x2 = 1, eps = 1e-6;
	return (sqrtf((true_x1 - x1) * (true_x1 - x1) + (true_x2 - x2) * (true_x2 - x2)) <= eps);
}

bool validate_solution_opt_d(double x1, double x2) {
	double true_x1 = 1, true_x2 = 1, square_of_eps = 1e-12;
	return ((true_x1 - x1) * (true_x1 - x1) + (true_x2 - x2) * (true_x2 - x2) <= square_of_eps);
}

bool validate_solution_no_opt_d(double x1, double x2) {
	double true_x1 = 1, true_x2 = 1, eps = 1e-6;
	return (sqrt((true_x1 - x1) * (true_x1 - x1) + (true_x2 - x2) * (true_x2 - x2)) <= eps);
}

int main() {
	float delta_opt_f = 1e-4, delta_no_opt_f = 1e-4, x1_opt_f, x1_no_opt_f, x2_opt_f, x2_no_opt_f;
	double delta_opt_d = 1e-4, delta_no_opt_d = 1e-4, x1_opt_d, x1_no_opt_d, x2_opt_d, x2_no_opt_d;
	bool answer_is_found_opt_f = 0, answer_is_found_opt_d = 0, answer_is_found_no_opt_f = 0, answer_is_found_no_opt_d = 0;
	while ((!answer_is_found_opt_f) || (!answer_is_found_no_opt_f) || (!answer_is_found_opt_d) || (!answer_is_found_no_opt_d)) {
		if (!answer_is_found_opt_f) {
			printf("Current delta for experiment in floats with optimizations is     %.60f\n", delta_opt_f);
		}
		if (!answer_is_found_no_opt_f) {
			printf("Current delta for experiment in floats without optimizations is  %.60f\n", delta_no_opt_f);
		}
		if (!answer_is_found_opt_d) {
			printf("Current delta for experiment in doubles with optimizations is    %.60lf\n", delta_opt_d);
		}
		if (!answer_is_found_no_opt_d) {
			printf("Current delta for experiment in doubles without optimizations is %.60lf\n", delta_no_opt_d);
		}

		solve_opt_f(delta_opt_f, &x1_opt_f, &x2_opt_f);
		solve_no_opt_f(delta_no_opt_f, &x1_no_opt_f, &x2_no_opt_f);
		solve_opt_d(delta_opt_d, &x1_opt_d, &x2_opt_d);
		solve_no_opt_d(delta_no_opt_d, &x1_no_opt_d, &x2_no_opt_d);

		answer_is_found_opt_f = validate_solution_opt_f(x1_opt_f, x2_opt_f);
		answer_is_found_no_opt_f = validate_solution_no_opt_f(x1_no_opt_f, x2_no_opt_f);
		answer_is_found_opt_d = validate_solution_opt_d(x1_opt_d, x2_opt_d);
		answer_is_found_no_opt_d = validate_solution_no_opt_d(x1_no_opt_d, x2_no_opt_d);

		printf("\n");

		if (answer_is_found_opt_f) {
			printf("!!ATTENTION!! Result for experiment in floats with optimizations is     %.60f\n", delta_opt_f);
		}
		else {
			delta_opt_f *= 0.5f;
		}
		if (answer_is_found_no_opt_f) {
			printf("!!ATTENTION!! Result for experiment in floats without optimizations is  %.60f\n", delta_no_opt_f);
		}
		else {
			delta_no_opt_f *= 0.5f;
		}
		if (answer_is_found_opt_d) {
			printf("!!ATTENTION!! Result for experiment in doubles with optimizations is    %.60lf\n", delta_opt_d);
		}
		else {
			delta_opt_d *= 0.5;
		}
		if (answer_is_found_no_opt_d) {
			printf("!!ATTENTION!! Result for experiment in doubles without optimizations is %.60lf\n", delta_no_opt_d);
		}
		else {
			delta_no_opt_d *= 0.5;
		}
	}
}