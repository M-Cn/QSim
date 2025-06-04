#include <math.h>
#include "../../include/Math/Complex.h"
#include "../../include/Math/ComplexMatrix.h"
#include "../../include/utils.h"

Complex CreateComplex(const double re, const double im)
{
    Complex ret;

    ret.m_re = re;
    ret.m_im = im;

    return ret;
}

Complex ComplexAdd(const Complex in1, const Complex in2)
{
    return CreateComplex(in1.m_re + in2.m_re, in1.m_im + in2.m_im);
}

Complex ComplexSubtract(const Complex in1, const Complex in2)
{
    return CreateComplex(in1.m_re - in2.m_re, in1.m_im - in2.m_im);
}

Complex ComplexMultiply(const Complex in1, const Complex in2)
{
    double a = in1.m_re;
    double b = in1.m_im;
    double c = in2.m_re;
    double d = in2.m_im;

    double ac = a * c;
    double bd = b * d;
    double bc = b * c;
    double ad = a * d;

    return CreateComplex(ac - bd, ad + bc);
}

Complex ComplexDivide(const Complex in1, const Complex in2)
{
    double a = in1.m_re;
    double b = in1.m_im;
    double c = in2.m_re;
    double d = in2.m_im;

    double ac = a * c;
    double bd = b * d;
    double bc = b * c;
    double ad = a * d;

    return CreateComplex((ac + bd) / (c * c + d * d), (bc - ad) / (c * c + d * d));
}

Complex ComplexConjugate(const Complex in)
{
    return CreateComplex(in.m_re, -in.m_im);
}

double ComplexMagnitude(const Complex in)
{
    return sqrt(in.m_re * in.m_re + in.m_im * in.m_im);
}

double ComplexArgument(const Complex in)
{
    return atan2(in.m_im, in.m_re);
}

bool ComplexIsEqualTo(const Complex in1, const Complex in2)
{
    if (DOUBLE_EQUALS(in1.m_re, in2.m_re) && DOUBLE_EQUALS(in1.m_im, in2.m_im))
        return true;

    return false;
}