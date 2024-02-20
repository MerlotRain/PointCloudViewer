#ifndef __PCV_MATRIX_H__
#define __PCV_MATRIX_H__

namespace pcv {

template<class T>
class MatrixT
{
    T m_mat[16];
};

typedef MatrixT<float> Matrix;
typedef MatrixT<double> Matrixd;

}// namespace pcv

#endif//__PCV_MATRIX_H__