#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "../include/utils.h"
#include "../include/Debug.h"
#include "../include/Math/Complex.h"
#include "../include/Math/ComplexVector.h"
#include "../include/Math/ComplexMatrix.h"
#include "../include/QSim.h"

// Prints a red message if the specified condition is not met
#define NOTIFY_TEST_FAIL(cond, fmt, ...) \
    do { \
        if (!(cond)) \
        { \
            PRINT_FAILURE(fmt, ##__VA_ARGS__); \
            fflush(stderr); \
            return; \
        } \
    } while(0);

void test_CreateComplex()
{
    Complex c = CreateComplex(3.0, 4.0);

    NOTIFY_TEST_FAIL(DOUBLE_EQUALS(c.m_re, 3.0), "CreateComplex test failed: real part mismatch\n");
    NOTIFY_TEST_FAIL(DOUBLE_EQUALS(c.m_im, 4.0), "CreateComplex test failed: imaginary part mismatch\n");

    PRINT_SUCCESS("CreateComplex test passed!\n");
}

void test_ComplexAdd() 
{
    Complex a = CreateComplex(1.0, 2.0);
    Complex b = CreateComplex(3.0, 4.0);
    Complex result = ComplexAdd(a, b);

    NOTIFY_TEST_FAIL(DOUBLE_EQUALS(result.m_re, 4.0), "ComplexAdd test failed: real part mismatch\n");
    NOTIFY_TEST_FAIL(DOUBLE_EQUALS(result.m_im, 6.0), "ComplexAdd test failed: imaginary part mismatch\n");

    PRINT_SUCCESS("ComplexAdd test passed!\n");
}

void test_ComplexSubtract() 
{
    Complex a = CreateComplex(5.0, 6.0);
    Complex b = CreateComplex(2.0, 4.0);
    Complex result = ComplexSubtract(a, b);

    NOTIFY_TEST_FAIL(DOUBLE_EQUALS(result.m_re, 3.0), "ComplexSubtract test failed: real part mismatch\n");
    NOTIFY_TEST_FAIL(DOUBLE_EQUALS(result.m_im, 2.0), "ComplexSubtract test failed: imaginary part mismatch\n");

    PRINT_SUCCESS("ComplexSubtract test passed!\n");
}

void test_ComplexMultiply() 
{
    Complex a = CreateComplex(1.0, 2.0);
    Complex b = CreateComplex(3.0, 4.0);
    Complex result = ComplexMultiply(a, b);

    NOTIFY_TEST_FAIL(DOUBLE_EQUALS(result.m_re, -5.0), "ComplexMultiply test failed: real part mismatch\n");
    NOTIFY_TEST_FAIL(DOUBLE_EQUALS(result.m_im, 10.0), "ComplexMultiply test failed: imaginary part mismatch\n");

    PRINT_SUCCESS("ComplexMultiply test passed!\n");
}

void test_ComplexDivide() 
{
    Complex a = CreateComplex(1.0, 2.0);
    Complex b = CreateComplex(3.0, 4.0);
    Complex result = ComplexDivide(a, b);

    NOTIFY_TEST_FAIL(DOUBLE_EQUALS(result.m_re, 0.44), "ComplexDivide test failed: real part mismatch\n");
    NOTIFY_TEST_FAIL(DOUBLE_EQUALS(result.m_im, 0.08), "ComplexDivide test failed: imaginary part mismatch\n");

    PRINT_SUCCESS("ComplexDivide test passed!\n");
}

void test_ComplexConjugate() 
{
    Complex a = CreateComplex(5.0, -3.0);
    Complex result = ComplexConjugate(a); // 5 + 3i

    NOTIFY_TEST_FAIL(DOUBLE_EQUALS(result.m_re, 5.0), "ComplexConjugate test failed: real part mismatch\n");
    NOTIFY_TEST_FAIL(DOUBLE_EQUALS(result.m_im, 3.0), "ComplexConjugate test failed: imaginary part mismatch\n");

    PRINT_SUCCESS("ComplexConjugate test passed!\n");
}

void test_ComplexMagnitude() 
{
    Complex a = CreateComplex(3.0, 4.0);
    double magnitude = ComplexMagnitude(a); // 5

    NOTIFY_TEST_FAIL(DOUBLE_EQUALS(magnitude, 5.0), "ComplexMagnitude test failed\n");

    PRINT_SUCCESS("ComplexMagnitude test passed!\n");
}

void test_ComplexArgument() 
{
    Complex a = CreateComplex(1.0, 1.0);
    double arg = ComplexArgument(a);

    NOTIFY_TEST_FAIL(DOUBLE_EQUALS(arg, M_PI / 4), "ComplexArgument test failed\n");

    PRINT_SUCCESS("ComplexArgument test passed!\n");
}

void test_ComplexIsEqualTo() 
{
    Complex a = CreateComplex(2.5, -1.5);
    Complex b = CreateComplex(2.5, -1.5);
    Complex c = CreateComplex(2.5, -1.4);

    NOTIFY_TEST_FAIL(ComplexIsEqualTo(a, b), "ComplexIsEqualTo test failed: expected equal\n");
    NOTIFY_TEST_FAIL(!ComplexIsEqualTo(a, c), "ComplexIsEqualTo test failed: expected not equal\n");

    PRINT_SUCCESS("ComplexIsEqualTo test passed!\n");
}

void test_CreateComplexVector() 
{
    ComplexVector v = CreateComplexVector(3);

    NOTIFY_TEST_FAIL(v.m_size == 3, "CreateComplexVector test failed: size mismatch\n");

    for (size_t i = 0; i < v.m_size; i++) 
    {
        Complex c = ComplexVectorGetElement(&v, i);
        NOTIFY_TEST_FAIL(ComplexIsEqualTo(c, CreateComplex(0.0, 0.0)), "CreateComplexVector test failed: element not zero\n");
    }

    ComplexVectorFree(&v);
    PRINT_SUCCESS("CreateComplexVector test passed!\n");
}

void test_SetGetComplexVectorElement() 
{
    ComplexVector v = CreateComplexVector(2);
    Complex a = CreateComplex(1.5, -2.5);
    Complex b = CreateComplex(-3.0, 4.0);

    ComplexVectorSetElement(&v, 0, a);
    ComplexVectorSetElement(&v, 1, b);

    Complex c0 = ComplexVectorGetElement(&v, 0);
    Complex c1 = ComplexVectorGetElement(&v, 1);

    NOTIFY_TEST_FAIL(ComplexIsEqualTo(c0, a), "ComplexVectorSet/GetElement test failed: mismatch at index 0\n");
    NOTIFY_TEST_FAIL(ComplexIsEqualTo(c1, b), "ComplexVectorSet/GetElement test failed: mismatch at index 1\n");

    ComplexVectorFree(&v);
    PRINT_SUCCESS("Set/GetComplexVectorElement test passed!\n");
}

void test_ComplexVectorAdd() 
{
    ComplexVector v1 = CreateComplexVector(2);
    ComplexVector v2 = CreateComplexVector(2);

    ComplexVectorSetElement(&v1, 0, CreateComplex(1, 1));
    ComplexVectorSetElement(&v1, 1, CreateComplex(2, 2));
    ComplexVectorSetElement(&v2, 0, CreateComplex(3, -1));
    ComplexVectorSetElement(&v2, 1, CreateComplex(-2, 0));

    ComplexVector sum = ComplexVectorAdd(v1, v2);

    NOTIFY_TEST_FAIL(ComplexIsEqualTo(ComplexVectorGetElement(&sum, 0), CreateComplex(4, 0)), "ComplexVectorAdd test failed: mismatch at index 0\n");
    NOTIFY_TEST_FAIL(ComplexIsEqualTo(ComplexVectorGetElement(&sum, 1), CreateComplex(0, 2)), "ComplexVectorAdd test failed: mismatch at index 1\n");

    ComplexVectorFree(&v1);
    ComplexVectorFree(&v2);
    ComplexVectorFree(&sum);

    PRINT_SUCCESS("ComplexVectorAdd test passed!\n");
}

void test_ComplexVectorSubtract() 
{
    ComplexVector v1 = CreateComplexVector(2);
    ComplexVector v2 = CreateComplexVector(2);

    ComplexVectorSetElement(&v1, 0, CreateComplex(4, 4));
    ComplexVectorSetElement(&v1, 1, CreateComplex(1, -1));
    ComplexVectorSetElement(&v2, 0, CreateComplex(1, 2));
    ComplexVectorSetElement(&v2, 1, CreateComplex(-1, -1));

    ComplexVector diff = ComplexVectorSubtract(v1, v2);

    NOTIFY_TEST_FAIL(ComplexIsEqualTo(ComplexVectorGetElement(&diff, 0), CreateComplex(3, 2)), "ComplexVectorSubtract test failed: mismatch at index 0\n");
    NOTIFY_TEST_FAIL(ComplexIsEqualTo(ComplexVectorGetElement(&diff, 1), CreateComplex(2, 0)), "ComplexVectorSubtract test failed: mismatch at index 1\n");

    ComplexVectorFree(&v1);
    ComplexVectorFree(&v2);
    ComplexVectorFree(&diff);

    PRINT_SUCCESS("ComplexVectorSubtract test passed!\n");
}

void test_ComplexVectorScalarMultiply() 
{
    ComplexVector v = CreateComplexVector(2);
    ComplexVectorSetElement(&v, 0, CreateComplex(1, 1));
    ComplexVectorSetElement(&v, 1, CreateComplex(2, -1));

    Complex scalar = CreateComplex(3, 2);

    ComplexVector result = ComplexVectorScalarMultiply(v, scalar);

    NOTIFY_TEST_FAIL(ComplexIsEqualTo(ComplexVectorGetElement(&result, 0), CreateComplex(1, 5)), "ComplexVectorScalarMultiply test failed: mismatch at index 0\n");
    NOTIFY_TEST_FAIL(ComplexIsEqualTo(ComplexVectorGetElement(&result, 1), CreateComplex(8, 1)), "ComplexVectorScalarMultiply test failed: mismatch at index 1\n");

    ComplexVectorFree(&v);
    ComplexVectorFree(&result);

    PRINT_SUCCESS("ComplexVectorScalarMultiply test passed!\n");
}

void test_ComplexVectorDotProduct() 
{
    ComplexVector v1 = CreateComplexVector(2);
    ComplexVector v2 = CreateComplexVector(2);

    ComplexVectorSetElement(&v1, 0, CreateComplex(1, 2));
    ComplexVectorSetElement(&v1, 1, CreateComplex(3, -1));
    ComplexVectorSetElement(&v2, 0, CreateComplex(2, -1));
    ComplexVectorSetElement(&v2, 1, CreateComplex(1, 4));

    Complex dp = ComplexVectorDotProduct(v1, v2); // -1 - 8i

    NOTIFY_TEST_FAIL(ComplexIsEqualTo(dp, CreateComplex(-1, -8)), "ComplexVectorDotProduct test failed\n");

    ComplexVectorFree(&v1);
    ComplexVectorFree(&v2);

    PRINT_SUCCESS("ComplexVectorDotProduct test passed!\n");
}

void test_ComplexVectorMagnitude() 
{
    ComplexVector v = CreateComplexVector(2);
    ComplexVectorSetElement(&v, 0, CreateComplex(3, 4)); // magnitude 5
    ComplexVectorSetElement(&v, 1, CreateComplex(1, 2)); // magnitude sqrt(5)

    double mag = ComplexVectorMagnitude(v);
    double expected = sqrt(25 + 5); // sqrt(30)

    NOTIFY_TEST_FAIL(DOUBLE_EQUALS(mag, expected), "ComplexVectorMagnitude test failed\n");

    ComplexVectorFree(&v);
    PRINT_SUCCESS("ComplexVectorMagnitude test passed!\n");
}

void test_ComplexVectorTransform()
{
    ComplexMatrix m = CreateComplexMatrix(2);
    ComplexMatrixSetElement(&m, 0, 0, CreateComplex(1, 1));  // 1 + i
    ComplexMatrixSetElement(&m, 0, 1, CreateComplex(2, -1)); // 2 - i
    ComplexMatrixSetElement(&m, 1, 0, CreateComplex(0, 3));  // 0 + 3i
    ComplexMatrixSetElement(&m, 1, 1, CreateComplex(-1, 2)); // -1 + 2i

    ComplexVector v = CreateComplexVector(2);
    ComplexVectorSetElement(&v, 0, CreateComplex(2, 0));    // 2 + 0i
    ComplexVectorSetElement(&v, 1, CreateComplex(1, -1));   // 1 - i

    // Perform the transformation (matrix * vector)
    ComplexVector result = ComplexVectorTransform(v, m);

    // Expected results:
    // y0 = (1 + i) * 2 + (2 - i) * (1 - i) = 3 - i
    // y1 = (0 + 3i) * 2 + (-1 + 2i) * (1 - i) = 1 + 9i
    Complex expected0 = CreateComplex(3, -1);
    Complex expected1 = CreateComplex(1, 9);

    Complex r0 = ComplexVectorGetElement(&result, 0);
    Complex r1 = ComplexVectorGetElement(&result, 1);

    NOTIFY_TEST_FAIL(ComplexIsEqualTo(r0, expected0), "ComplexVectorTransform test failed: mismatch at element 0\n");
    NOTIFY_TEST_FAIL(ComplexIsEqualTo(r1, expected1), "ComplexVectorTransform test failed: mismatch at element 1\n");

    ComplexVectorFree(&v);
    ComplexVectorFree(&result);
    ComplexMatrixFree(&m);

    PRINT_SUCCESS("ComplexVectorTransform test passed!\n");
}

void test_CreateComplexMatrix() 
{
    ComplexMatrix m = CreateComplexMatrix(3);
    
    NOTIFY_TEST_FAIL(m.m_size == 3, "CreateComplexMatrix test failed: size mismatch\n");
    
    for (size_t i = 0; i < m.m_size; i++) 
    {
        for (size_t j = 0; j < m.m_size; j++) 
        {
            Complex c = ComplexMatrixGetElement(&m, i, j);

            if (i == j) { NOTIFY_TEST_FAIL(ComplexIsEqualTo(c, CreateComplex(1.0, 0.0)), "CreateComplexMatrix test failed: diagonal element not 1\n"); }
            else { NOTIFY_TEST_FAIL(ComplexIsEqualTo(c, CreateComplex(0.0, 0.0)), "CreateComplexMatrix test failed: off-diagonal element not 0\n"); }
        }
    }

    ComplexMatrixFree(&m);
    PRINT_SUCCESS("CreateComplexMatrix test passed!\n");
}

void test_SetGetComplexMatrixElement() 
{
    ComplexMatrix m = CreateComplexMatrix(2);

    Complex a = CreateComplex(1.5, -2.5);
    Complex b = CreateComplex(-3.0, 4.0);

    ComplexMatrixSetElement(&m, 0, 1, a);
    ComplexMatrixSetElement(&m, 1, 0, b);

    Complex c0 = ComplexMatrixGetElement(&m, 0, 1);
    Complex c1 = ComplexMatrixGetElement(&m, 1, 0);

    NOTIFY_TEST_FAIL(ComplexIsEqualTo(c0, a), "ComplexMatrixSet/GetElement test failed: mismatch at (0,1)\n");
    NOTIFY_TEST_FAIL(ComplexIsEqualTo(c1, b), "ComplexMatrixSet/GetElement test failed: mismatch at (1,0)\n");

    ComplexMatrixFree(&m);
    PRINT_SUCCESS("ComplexMatrixSet/GetComplexMatrixElement test passed!\n");
}

void test_ComplexMatrixDot() 
{
    ComplexMatrix m = CreateComplexMatrix(2);

    ComplexMatrixSetElement(&m, 0, 0, CreateComplex(1, 1));
    ComplexMatrixSetElement(&m, 0, 1, CreateComplex(2, -1));
    ComplexMatrixSetElement(&m, 1, 0, CreateComplex(0, 3));
    ComplexMatrixSetElement(&m, 1, 1, CreateComplex(-1, 2));

    Complex scalar = CreateComplex(3, 2);

    ComplexMatrix result = ComplexMatrixDot(m, scalar);

    // Manually check first element: (1+1i)*(3+2i) = 1*3 + 1*2i + 1i*3 + 1i*2i = 3 + 2i + 3i + 2i^2 = 3 + 5i - 2 = 1 + 5i
    NOTIFY_TEST_FAIL(ComplexIsEqualTo(ComplexMatrixGetElement(&result, 0, 0), CreateComplex(1, 5)), "ComplexMatrixDot test failed: mismatch at (0,0)\n");
    // (2 -1i)*(3+2i) = 6 + 4i -3i -2i^2 = 6 + i + 2 = 8 + i
    NOTIFY_TEST_FAIL(ComplexIsEqualTo(ComplexMatrixGetElement(&result, 0, 1), CreateComplex(8, 1)), "ComplexMatrixDot test failed: mismatch at (0,1)\n");
    // (0 + 3i)*(3 + 2i) = 0 + 0 + 9i + 6i^2 = 9i - 6 = -6 + 9i
    NOTIFY_TEST_FAIL(ComplexIsEqualTo(ComplexMatrixGetElement(&result, 1, 0), CreateComplex(-6, 9)), "ComplexMatrixDot test failed: mismatch at (1,0)\n");
    // (-1 + 2i)*(3+2i) = -3 - 2i + 6i + 4i^2 = -3 + 4i - 4 = -7 + 4i
    NOTIFY_TEST_FAIL(ComplexIsEqualTo(ComplexMatrixGetElement(&result, 1, 1), CreateComplex(-7, 4)), "ComplexMatrixDot test failed: mismatch at (1,1)\n");

    ComplexMatrixFree(&m);
    ComplexMatrixFree(&result);

    PRINT_SUCCESS("ComplexMatrixDot test passed!\n");
}

void test_ComplexMatrixMultiply() 
{
    ComplexMatrix m1 = CreateComplexMatrix(2);
    ComplexMatrix m2 = CreateComplexMatrix(2);

    // Set m1 = [[1+1i, 2-1i],
    //           [0+3i, -1+2i]]
    ComplexMatrixSetElement(&m1, 0, 0, CreateComplex(1, 1));
    ComplexMatrixSetElement(&m1, 0, 1, CreateComplex(2, -1));
    ComplexMatrixSetElement(&m1, 1, 0, CreateComplex(0, 3));
    ComplexMatrixSetElement(&m1, 1, 1, CreateComplex(-1, 2));

    // Set m2 = [[2, -1i],
    //           [1+2i, 0]]
    ComplexMatrixSetElement(&m2, 0, 0, CreateComplex(2, 0));
    ComplexMatrixSetElement(&m2, 0, 1, CreateComplex(0, -1));
    ComplexMatrixSetElement(&m2, 1, 0, CreateComplex(1, 2));
    ComplexMatrixSetElement(&m2, 1, 1, CreateComplex(0, 0));

    ComplexMatrix product = ComplexMatrixMultiply(m1, m2);

    // Manually calculate each element of product:
    // product[0,0] = m1[0,0]*m2[0,0] + m1[0,1]*m2[1,0]
    // = (1+1i)*2 + (2-1i)*(1+2i)
    // = (2+2i) + (2 + 4i -1i -2i^2) = (2+2i) + (2 + 3i + 2) = (2+2i) + (4 + 3i) = 6 + 5i

    NOTIFY_TEST_FAIL(ComplexIsEqualTo(ComplexMatrixGetElement(&product, 0, 0), CreateComplex(6, 5)), "ComplexMatrixMultiply test failed: mismatch at (0,0)\n");

    // product[0,1] = m1[0,0]*m2[0,1] + m1[0,1]*m2[1,1]
    // = (1+1i)*(-i) + (2-1i)*0
    // = (1+1i)*(-i) = -i - i^2 = -i + 1 = 1 - i

    NOTIFY_TEST_FAIL(ComplexIsEqualTo(ComplexMatrixGetElement(&product, 0, 1), CreateComplex(1, -1)), "ComplexMatrixMultiply test failed: mismatch at (0,1)\n");

    // product[1,0] = m1[1,0]*m2[0,0] + m1[1,1]*m2[1,0]
    // = (0+3i)*2 + (-1+2i)*(1+2i)
    // = 6i + (-1 + -2i + 2i + 4i^2)
    // = 6i + (-1 + 0 -4) = 6i - 5 = -5 + 6i

    NOTIFY_TEST_FAIL(ComplexIsEqualTo(ComplexMatrixGetElement(&product, 1, 0), CreateComplex(-5, 6)), "ComplexMatrixMultiply test failed: mismatch at (1,0)\n");

    // product[1,1] = m1[1,0]*m2[0,1] + m1[1,1]*m2[1,1]
    // = (0+3i)*(-i) + (-1+2i)*0
    // = 3i * -i = -3 i^2 = 3

    NOTIFY_TEST_FAIL(ComplexIsEqualTo(ComplexMatrixGetElement(&product, 1, 1), CreateComplex(3, 0)), "ComplexMatrixMultiply test failed: mismatch at (1,1)\n");

    ComplexMatrixFree(&m1);
    ComplexMatrixFree(&m2);
    ComplexMatrixFree(&product);

    PRINT_SUCCESS("ComplexMatrixMultiply test passed!\n");
}

void test_CreateQSim()
{
    QSim qsim = CreateQSim("esempi-input/init-ex.txt", "esempi-input/circ-ex.txt");

    NOTIFY_TEST_FAIL(qsim.m_numQBits == 1, "CreateQSim test failed: numQbits mismatch.\n");
    NOTIFY_TEST_FAIL(qsim.m_numGates == 3, "CreateQSim test failed: numGates mismatch.\n");
    NOTIFY_TEST_FAIL(ComplexIsEqualTo(ComplexVectorGetElement(&qsim.m_initialState, 0), CreateComplex(0.5f, 0.5f)), "CreateQSim test failed: initialState mismatch at index 0.\n");
    NOTIFY_TEST_FAIL(ComplexIsEqualTo(ComplexVectorGetElement(&qsim.m_initialState, 1), CreateComplex(0.5f, -0.5f)), "CreateQSim test failed: initialState mismatch at index 1.\n");

    NOTIFY_TEST_FAIL(qsim.m_gateList[0].m_size == 2, "CreateQSim test failed: size mismatch for Gate at index 0 (expected=%d, got=%zu)\n", 2, qsim.m_gateList[0].m_size);
    NOTIFY_TEST_FAIL(qsim.m_gateList[1].m_size == 2, "CreateQSim test failed: size mismatch for Gate at index 1 (expected=%d, got=%zu)\n", 2, qsim.m_gateList[1].m_size);
    NOTIFY_TEST_FAIL(qsim.m_gateList[2].m_size == 2, "CreateQSim test failed: size mismatch for Gate at index 2 (expected=%d, got=%zu)\n", 2, qsim.m_gateList[2].m_size);

    const QuantumCircuitDef circuidDef = qsim.m_circuitDef;

    NOTIFY_TEST_FAIL(circuidDef.m_numGates == 3, "CreateQSim test failed: circuitDef.numGates mismatch.\n");
    NOTIFY_TEST_FAIL(circuidDef.m_gateIDs[0] == 2, "CreateQSim test failed: circuitDef.gateID mismatch at index 0.\n");
    NOTIFY_TEST_FAIL(circuidDef.m_gateIDs[1] == 0, "CreateQSim test failed: circuitDef.gateID mismatch at index 1.\n");
    NOTIFY_TEST_FAIL(circuidDef.m_gateIDs[2] == 1, "CreateQSim test failed: circuitDef.gateID mismatch at index 2.\n");

    QSimRun(&qsim);

    NOTIFY_TEST_FAIL(ComplexIsEqualTo(ComplexVectorGetElement(&qsim.m_finalState, 0), CreateComplex(-0.5f, 0.5f)), "CreateQSim test failed: finalState mismatch at index 0.\n");
    NOTIFY_TEST_FAIL(ComplexIsEqualTo(ComplexVectorGetElement(&qsim.m_finalState, 1), CreateComplex(-0.5f, -0.5f)), "CreateQSim test failed: finalState mismatch at index 1.\n");

    PRINT_SUCCESS("CreateQSim test passed!\n");

    QSimFree(&qsim);
}

int main() 
{
    printf("--------Complex tests--------\n");

    test_CreateComplex();
    test_ComplexAdd();
    test_ComplexSubtract();
    test_ComplexMultiply();
    test_ComplexDivide();
    test_ComplexConjugate();
    test_ComplexMagnitude();
    test_ComplexArgument();
    test_ComplexIsEqualTo();

    printf("--------ComplexVector tests--------\n");

    test_CreateComplexVector();
    test_SetGetComplexVectorElement();
    test_ComplexVectorAdd();
    test_ComplexVectorSubtract();
    test_ComplexVectorScalarMultiply();
    test_ComplexVectorDotProduct();
    test_ComplexVectorMagnitude();
    test_ComplexVectorTransform();

    printf("--------ComplexMatrix tests--------\n");

    test_CreateComplexMatrix();
    test_SetGetComplexMatrixElement();
    test_ComplexMatrixDot();
    test_ComplexMatrixMultiply();

    printf("--------QSim tests--------\n");

    test_CreateQSim();

    return 0;
}