/**
 * $Revision$
 * $Date$
 * $Author$
 */

#include "float.h"

#define FLOAT_LOOP_MAX 25

#define FLOAT_EXP_EPSILON 1e-9f
#define FLOAT_LOG_EPSILON 1e-6f

float float_abs(float x) {
	return x < 0.0f ? -x : x;
}

float float_exp(float x) {
	int i;

	float sum = 1.0f;
	float res = 0.0f;

	for(i = 1; i < FLOAT_LOOP_MAX; i++) {
		res += sum;
		sum *= x / i;

		if (float_abs(sum * res) < FLOAT_EXP_EPSILON)
			break;
	}

	return res;
}

float float_log(float x) {
	int i;

	float sum = (x - 1.0f) / (x + 1.0f);
	float tmp = sum * sum;

	float res = 0.0f;

	for(i = 1; i < FLOAT_LOOP_MAX; i += 2) {
		res += sum / i;
		sum *= tmp;

		if (float_abs(sum / res) < FLOAT_LOG_EPSILON)
			break;
	}

	return 2.0f * res;
}

float float_pow(float x, float c) {
	return float_exp(c * float_log(x));
}
