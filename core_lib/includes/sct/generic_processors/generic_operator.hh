#ifndef generic_operator_h__
#define generic_operator_h__

#include "sct/generic_processors/cutNote.hh"
#include "sct/generic_processors/lambda_Note.hh"
#include "sct/platform.hh"


DllExport lambda_Note operator+(const cutNote&, double);
DllExport lambda_Note operator+(double, const cutNote&);
DllExport lambda_Note operator+(const cutNote&, const cutNote&);


DllExport lambda_Note operator-(const cutNote& lhs, double rhs);
DllExport lambda_Note operator-(double lhs, const cutNote& rhs);
DllExport lambda_Note operator-(const cutNote& lhs, const cutNote& rhs);

DllExport lambda_Note operator*(const cutNote&, double);
DllExport lambda_Note operator*(double, const cutNote&);
DllExport lambda_Note operator*(const cutNote& lhs, const cutNote& rhs);


DllExport lambda_Note operator/(const cutNote&, double);
DllExport lambda_Note operator/(double, const cutNote&);
DllExport lambda_Note operator/(const cutNote& lhs, const cutNote& rhs);

DllExport lambda_Note operator<(const cutNote& A, const cutNote&  B);
DllExport lambda_Note operator<(const cutNote& A, double  B);
DllExport lambda_Note operator<(double A, const cutNote&  B);


DllExport lambda_Note operator<=(const cutNote& A, const cutNote&  B);
DllExport lambda_Note operator<=(const cutNote& A, double B);
DllExport lambda_Note operator<=(double A, const cutNote&  B);


DllExport lambda_Note operator>(const cutNote& A, const cutNote&  B);
DllExport lambda_Note operator>(const cutNote& A, double  B);
DllExport lambda_Note operator>(double A, const cutNote&  B);


DllExport lambda_Note operator>=(const cutNote& A, const cutNote&  B);
DllExport lambda_Note operator>=(const cutNote& A, double  B);
DllExport lambda_Note operator>=(double A, const cutNote&  B);


DllExport lambda_Note operator==(const cutNote& A, const cutNote&  B);
DllExport lambda_Note operator==(const cutNote& A, double  B);
DllExport lambda_Note operator==(double A, const cutNote&  B);

DllExport lambda_Note operator!=(const cutNote& A, const cutNote&  B);
DllExport lambda_Note operator!=(const cutNote& A, double  B);
DllExport lambda_Note operator!=(double A, const cutNote&  B);


DllExport lambda_Note operator&&(const cutNote& NoteA, const cutNote& NoteB);

DllExport lambda_Note operator!(const cutNote& note_);

DllExport  lambda_Note operator||(const cutNote& NoteA, const cutNote& NoteB);
#endif // generic_operator_h__
