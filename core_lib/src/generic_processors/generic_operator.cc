#include "sct/generic_processors/generic_operator.hh"




lambda_Note operator<(const cutNote& A, const cutNote& B) {
  return make_lambda_Note([](double x, double y) { return  x < y; }, A, B);
}

lambda_Note operator<=(const cutNote& A, const cutNote& B) {
  return make_lambda_Note([](double x, double y) { return  x <= y; }, A, B);
}

lambda_Note operator>(const cutNote& A, const cutNote& B) {
  return make_lambda_Note([](double x, double y) { return  x > y; }, A, B);
}

lambda_Note operator>=(const cutNote& A, const cutNote& B) {
  return make_lambda_Note([](double x, double y) { return  x >= y; }, A, B);
}

lambda_Note operator==(const cutNote& A, const cutNote& B) {
  return make_lambda_Note([](double x, double y) { return  x == y; }, A, B);
}

lambda_Note operator!=(const cutNote& A, const cutNote& B) {
  return make_lambda_Note([](double x, double y) { return  x != y; }, A, B);
}

lambda_Note operator&&(const cutNote& NoteA, const cutNote& NoteB) {
  return make_lambda_Note([](double x, double y) { return  x && y; }, NoteA, NoteB);
}

lambda_Note operator||(const cutNote& NoteA, const cutNote& NoteB) {
  return make_lambda_Note([](double x, double y) { return  x || y; }, NoteA, NoteB);
}



lambda_Note operator+(const cutNote& lhs, double rhs) {
  return make_lambda_Note([rhs](double x) { return x + rhs; }, lhs);
}

lambda_Note operator+(double lhs, const cutNote& rhs) {
  return make_lambda_Note([lhs](double x) { return lhs + x; }, rhs);
}

lambda_Note operator+(const cutNote& lhs, const cutNote& rhs) {
  return make_lambda_Note([](double x, double y) { return x + y; }, lhs, rhs);
}



lambda_Note operator-(const cutNote& lhs, double rhs) {
  return make_lambda_Note([rhs](double x) { return x - rhs; }, lhs);
}

lambda_Note operator-(double lhs, const cutNote& rhs) {
  return make_lambda_Note([lhs](double x) { return lhs - x; }, rhs);
}

lambda_Note operator-(const cutNote& lhs, const cutNote& rhs) {
  return make_lambda_Note([](double x, double y) { return x - y; }, lhs, rhs);
}

lambda_Note operator*(const cutNote& lhs, double rhs) {
  return make_lambda_Note([rhs](double x) { return x * rhs; }, lhs);
}

lambda_Note operator*(double lhs, const cutNote& rhs) {
  return make_lambda_Note([lhs](double x) { return lhs * x; }, rhs);
}

lambda_Note operator*(const cutNote& lhs, const cutNote& rhs) {
  return make_lambda_Note([](double x, double y) { return  x*y; }, lhs, rhs);
}


lambda_Note operator/(const cutNote& lhs, double rhs) {
  return make_lambda_Note([rhs](double x) { return x * rhs; }, lhs);
}

lambda_Note operator/(double lhs, const cutNote& rhs) {
  return make_lambda_Note([lhs](double x) { return lhs * x; }, rhs);
}

lambda_Note operator/(const cutNote& lhs, const cutNote& rhs) {
  return make_lambda_Note([](double x, double y) { return  x*y; }, lhs, rhs);
}
