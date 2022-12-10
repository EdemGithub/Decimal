#include "s21_decimal.h"

int s21_is_less(s21_decimal dec1, s21_decimal dec2) {
  int is_less = 0;
  int sign_1 = get_sign(&dec1);
  int sign_2 = get_sign(&dec2);
  normalize(&dec1, &dec2);
  if (!sign_1 && !sign_2) {
    is_less = s21_is_less_simple(
        dec1, dec2);
  } else if (sign_1 ^
             sign_2) {
    is_less = (sign_1) ? 1 : 0;
  } else {
    is_less = !s21_is_less_simple(dec1, dec2);
  }
  return is_less;
}

int s21_is_less_simple(s21_decimal dec1, s21_decimal dec2) {
  int is_less = 0;
  for (int i = 95; i >= 0; i--) {
    if (get_bit(dec1, i) ^ get_bit(dec2, i)) {
      is_less = get_bit(dec2, i) != 0 ? 1 : 0;
      break;
    }
  }
  return is_less;
}

int s21_is_equal(s21_decimal dec1, s21_decimal dec2) {
  int is_equal;
  int sign_1 = get_sign(&dec1);
  int sign_2 = get_sign(&dec2);
  normalize(&dec1, &dec2);
  if (sign_1 ^ sign_2) {
    is_equal = 0;
    if (s21_is_equal_simple(dec1, DECIMAL_ZERO) &&
        s21_is_equal_simple(dec2, DECIMAL_ZERO)) {
      is_equal = 1;
    }
  } else {
    is_equal = s21_is_equal_simple(dec1, dec2);
  }
  return is_equal;
}

int s21_is_equal_simple(s21_decimal dec1, s21_decimal dec2) {
  int is_equal = 1;
  for (int i = 95; i >= 0; i--) {
    if (get_bit(dec1, i) != get_bit(dec2, i)) {
      is_equal = 0;
      break;
    }
  }
  return is_equal;
}

int s21_is_less_or_equal(s21_decimal dec1, s21_decimal dec2) {
  return s21_is_less(dec1, dec2) || s21_is_equal(dec1, dec2);
}

int s21_is_greater(s21_decimal dec1, s21_decimal dec2) {
  return s21_is_less(dec2, dec1);
}

int s21_is_greater_or_equal(s21_decimal dec1, s21_decimal dec2) {
  return s21_is_greater(dec1, dec2) || s21_is_equal(dec1, dec2);
}

int s21_is_not_equal(s21_decimal dec1, s21_decimal dec2) {
  return !s21_is_equal(dec1, dec2);
}
