#include "float.h"

#define FLOAT_LOOP_MAX 100

#define FLOAT_EXP_EPSILON 1e-9f
#define FLOAT_LOG_EPSILON 1e-6f

#define FLOAT_LOG2 0.693147180559945309417232121458176568075500134360255254120f

#define FLOAT_EXPONENT(bitmap) (((bitmap & 0x7F800000) >> 23) - 127)
#define FLOAT_NEGATIVE(bitmap) (((bitmap & 0x80000000) >> 31))
#define FLOAT_MANTISSA(bitmap) (((bitmap & 0x007FFFFF) | 0x00800000) / (float)(0x00800000))

float get_exponent(float x);
float get_mantissa(float x);

float get_exponent(float x) {
	return FLOAT_EXPONENT(*(int*)(&x));
}

float get_mantissa(float x) {
	return FLOAT_NEGATIVE(*(int*)(&x)) ? -FLOAT_MANTISSA(*(int*)(&x)) : FLOAT_MANTISSA(*(int*)(&x));
}

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
	if (x < 2.0f) {
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
	} else {
		return float_log(get_mantissa(x)) + get_exponent(x) * FLOAT_LOG2;
	}
}

float float_pow(float x, float c) {
	return float_exp(c * float_log(x));
}

float float_log2(float x) {
	return float_log(x) / FLOAT_LOG2;
}

float float_pow2(float c) {
	return float_pow(2.0f, c);
}
