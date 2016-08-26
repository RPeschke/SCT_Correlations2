#include "sct/generic_processors/generic_operator.hh"




lambda_Note operator<(const cutNote& A, const cutNote& B) {
  return make_lambda_Node([](double x, double y) { return  x < y; }, A, B);
}

lambda_Note operator<(const cutNote& A, double B) {
  return make_lambda_Node([B](double x) { return  x < B; }, A);
}

lambda_Note operator<(double A, const cutNote& B) {
  return make_lambda_Node([A](double y) { return  A < y; }, B);
}

lambda_Note operator<=(const cutNote& A, const cutNote& B) {
  return make_lambda_Node([](double x, double y) { return  x <= y; }, A, B);
}

lambda_Note operator<=(const cutNote& A, double B) {
  return make_lambda_Node([B](double x) { return  x <= B; }, A);
}

lambda_Note operator<=(double A, const cutNote& B) {
  return make_lambda_Node([A](double y) { return  A <= y; }, B);
}

lambda_Note operator>(const cutNote& A, const cutNote& B) {
  return make_lambda_Node([](double x, double y) { return  x > y; }, A, B);
}

lambda_Note operator>(const cutNote& A, double B) {
  return make_lambda_Node([B](double x) { return  x > B; }, A);
}

lambda_Note operator>(double A, const cutNote& B) {
  return make_lambda_Node([A](double y) { return  A > y; }, B);
}

lambda_Note operator>=(const cutNote& A, const cutNote& B) {
  return make_lambda_Node([](double x, double y) { return  x >= y; }, A, B);
}

lambda_Note operator>=(const cutNote& A, double B) {
  return make_lambda_Node([B](double x) { return  x >= B; }, A);
}

lambda_Note operator>=(double A, const cutNote& B) {
  return make_lambda_Node([A](double y) { return  A >= y; }, B);
}

lambda_Note operator==(const cutNote& A, const cutNote& B) {
  return make_lambda_Node([](double x, double y) { return  x == y; }, A, B);
}

lambda_Note operator==(const cutNote& A, double B) {
  return make_lambda_Node([B](double x) { return  x == B; }, A);
}

lambda_Note operator==(double A, const cutNote& B) {
  return make_lambda_Node([A](double y) { return  A == y; }, B);
}

lambda_Note operator!=(const cutNote& A, const cutNote& B) {
  return make_lambda_Node([](double x, double y) { return  x != y; }, A, B);
}

lambda_Note operator!=(const cutNote& A, double B) {
  return make_lambda_Node([B](double x) { return  x != B; }, A);
}

lambda_Note operator!=(double A, const cutNote& B) {
  return make_lambda_Node([A](double y) { return  A != y; }, B);
}

lambda_Note operator&&(const cutNote& NoteA, const cutNote& NoteB) {
  return make_lambda_Node([](double x, double y) { return  x && y; }, NoteA, NoteB);
}

lambda_Note operator||(const cutNote& NoteA, const cutNote& NoteB) {
  return make_lambda_Node([](double x, double y) { return  x || y; }, NoteA, NoteB);
}


lambda_Note operator!(const cutNote& note_) {
  return make_lambda_Node([](double x) { return  !x ; }, note_);
}
lambda_Note operator+(const cutNote& lhs, double rhs) {
  return make_lambda_Node([rhs](double x) { return x + rhs; }, lhs);
}

lambda_Note operator+(double lhs, const cutNote& rhs) {
  return make_lambda_Node([lhs](double x) { return lhs + x; }, rhs);
}

lambda_Note operator+(const cutNote& lhs, const cutNote& rhs) {
  return make_lambda_Node([](double x, double y) { return x + y; }, lhs, rhs);
}



lambda_Note operator-(const cutNote& lhs, double rhs) {
  return make_lambda_Node([rhs](double x) { return x - rhs; }, lhs);
}

lambda_Note operator-(double lhs, const cutNote& rhs) {
  return make_lambda_Node([lhs](double x) { return lhs - x; }, rhs);
}

lambda_Note operator-(const cutNote& lhs, const cutNote& rhs) {
  return make_lambda_Node([](double x, double y) { return x - y; }, lhs, rhs);
}

lambda_Note operator*(const cutNote& lhs, double rhs) {
  return make_lambda_Node([rhs](double x) { return x * rhs; }, lhs);
}

lambda_Note operator*(double lhs, const cutNote& rhs) {
  return make_lambda_Node([lhs](double x) { return lhs * x; }, rhs);
}

lambda_Note operator*(const cutNote& lhs, const cutNote& rhs) {
  return make_lambda_Node([](double x, double y) { return  x*y; }, lhs, rhs);
}


lambda_Note operator/(const cutNote& lhs, double rhs) {
  return make_lambda_Node([rhs](double x) { return x * rhs; }, lhs);
}

lambda_Note operator/(double lhs, const cutNote& rhs) {
  return make_lambda_Node([lhs](double x) { return lhs * x; }, rhs);
}

lambda_Note operator/(const cutNote& lhs, const cutNote& rhs) {
  return make_lambda_Node([](double x, double y) { return  x*y; }, lhs, rhs);
}


