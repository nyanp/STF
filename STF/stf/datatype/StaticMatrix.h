/**
 * @file   StaticMatrix.h
 * @brief  テンプレートを用いた固定要素数の行列計算クラス
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_datatype_StaticMatrix_h
#define stf_datatype_StaticMatrix_h

#include <assert.h>
#include "StaticVector.h"

namespace stf { 
namespace datatype {

//! テンプレートを用いた固定要素数の行列計算クラス
/*!  */
template<int rows, int cols>
class StaticMatrix {
public:
	StaticMatrix(){}
    StaticMatrix(const StaticMatrix<rows,cols> &rhs);
	~StaticMatrix(){}
    inline const StaticVector<cols> &operator[](int index) const;
    inline StaticVector<cols> &operator[](int index);
    StaticMatrix &unitize();
    StaticMatrix<cols,rows> trans() const ;
    StaticMatrix inverse() const ;
    bool isSquare();
    int pivot(StaticMatrix &m, int row) const ;
	double trace() const ;//Trace
	double det() const ; //行列式
    StaticMatrix &operator=(const StaticMatrix &rhs);
    StaticMatrix &operator+=(const StaticMatrix &rhs);
    StaticMatrix &operator-=(const StaticMatrix &rhs);
    StaticMatrix &operator*=(const StaticMatrix<cols,cols> &rhs);
    StaticMatrix &operator*=(double rhs);
    StaticMatrix &operator/=(double rhs);
    bool operator==(const StaticMatrix &rhs) const ;
    bool operator!=(const StaticMatrix &rhs) const ;
	virtual void reset(){ for(int i = 0; i < rows; i++) value_[i].reset(); }
protected:
	StaticVector<cols> value_[rows];
};

//////////////////////////////////////
//  Inline Methods for StaticMatrix //
//////////////////////////////////////

template<int rows, int cols>
inline const StaticVector<cols> &StaticMatrix<rows,cols>::operator[](int index) const
{
	assert(index >= 0 && index < rows);
	return value_[index];
}

template<int rows, int cols>
inline StaticVector<cols> &StaticMatrix<rows,cols>::operator[](int index)
{
	assert(index >= 0 && index < rows);
	return value_[index];
}

//行列の加算
template<int rows, int cols>
const StaticMatrix<rows,cols> operator + (const StaticMatrix<rows,cols>& oper1, const StaticMatrix<rows,cols>& oper2){
	StaticMatrix<rows,cols> mat = oper1;
	mat += oper2;
	return mat;
}

//行列の減算
template<int rows, int cols>
inline const StaticMatrix<rows,cols> operator - (const StaticMatrix<rows,cols>& oper1, const StaticMatrix<rows,cols>& oper2){
	StaticMatrix<rows,cols> mat = oper1;
	mat -= oper2;
	return mat;		
}

//行列の積算
template<int rows1, int cols1, int cols2>
inline const StaticMatrix<rows1,cols2> operator * (const StaticMatrix<rows1,cols1>& oper1, const StaticMatrix<cols1,cols2>& oper2){
	StaticMatrix<rows1,cols2> mat;

	for(int r = 0;r < rows1; r++)
	  for(int c = 0;c < cols2; c++)
		for(int index = 0;index < cols1; index ++)
			mat[r][c] += oper1[r][index] * oper2[index][c];
		  //mat[rows][cols] += oper1[rows][index] * oper2[index][cols];
	return mat;
}

//行列を右から定数倍
template<int rows, int cols>
inline const StaticMatrix<rows,cols> operator * (const StaticMatrix<rows,cols>& oper, double factor){
	StaticMatrix<rows,cols> mat = oper;
	mat *= factor;
	return mat;
}

//行列を左から定数倍
template<int rows, int cols>
inline const StaticMatrix<rows,cols> operator * (double factor, const StaticMatrix<rows,cols>& oper){
	return oper * factor;
}

//行列の定数除算
template<int rows, int cols>
inline const StaticMatrix<rows,cols> operator / (const StaticMatrix<rows,cols>& oper, double factor){
	StaticMatrix<rows,cols> mat = oper;
	mat /= factor;
	return mat;
}

//行列とベクトルの積
template<int rows, int cols>
inline const StaticVector<rows> operator * (const StaticMatrix<rows,cols>& mat, const StaticVector<cols>& vec){
	StaticVector<rows> temp;

	for(int i = 0; i < rows; i++)
		for(int index = 0; index < cols; index ++)
			temp[i] += mat[i][index] * vec[index];
	return temp;
}


//////////////////////
// Member Function  //
//////////////////////

template<int rows, int cols>
StaticMatrix<rows,cols>::StaticMatrix(const StaticMatrix<rows,cols> &rhs)
{
	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			value_[i][j] = rhs[i][j];
}

template<int rows, int cols>
StaticMatrix<rows,cols> &StaticMatrix<rows,cols>::unitize()
{
	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			if(i == j) value_[i][j] = 1.0;
			else       value_[i][j] = 0.0;
	return *this;	
}

template<int rows, int cols>
double StaticMatrix<rows,cols>::det() const 
{
	assert(cols == rows);
	assert(cols <= 3);//とりあえず3次まで定義

	if(cols == 2){
		return value_[0][0] * value_[1][1] - value_[0][1] * value_[1][0];
	}
	if(cols == 3){
		return value_[0][0] * value_[1][1] * value_[2][2] + 
			value_[0][1] * value_[1][2] * value_[2][0] + 
			value_[0][2] * value_[1][0] * value_[2][1] -
			value_[0][0] * value_[1][2] * value_[2][1] -
			value_[0][1] * value_[1][0] * value_[2][2] -
			value_[0][2] * value_[1][1] * value_[2][0];
	}
	if(cols == 1){
		return value_[0][0];
	}
	assert(0);
}

template<int rows, int cols>
double StaticMatrix<rows,cols>::trace() const
{
	double v = 0;
	for(int i = 0; i < rows; i++)
		v += value_[i][i];
	return v;
}

template<int rows, int cols>
StaticMatrix<cols,rows> StaticMatrix<rows,cols>::trans() const 
{
	StaticMatrix<cols,rows> temp;
	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			temp[j][i] = value_[i][j];
	return temp;
}

template<int rows, int cols>
StaticMatrix<rows,cols> StaticMatrix<rows,cols>::inverse() const 
{
	int i, j, k;
	double a1, a2;
	//result = false;
	assert(rows == cols);

	StaticMatrix<rows,cols> tempmat;
	for(int i = 0; i < rows; i++) tempmat[i][i] = 1.0;
	StaticMatrix<rows,cols> m = *this;//副作用を生じないように現インスタンスのコピーで計算

	for (k = 0; k < rows; k++)
	{
		int indx = pivot(m,k);
		assert(indx != -1);
		if (indx != 0)
		{
			StaticVector<cols> temp = tempmat.value_[k];
			tempmat.value_[k] = tempmat.value_[indx];
			tempmat.value_[indx] = temp;
		}
		a1 = m[k][k];
		for (j = 0; j < rows; j++)
		{
			m[k][j] /= a1;
			tempmat[k][j] /= a1;
		}
		for (i = 0; i < rows; i++)
			if (i != k)
			{
				a2 = m[i][k];
				for (j=0; j < rows; j++)
				{
					m[i][j] -= a2 * m[k][j];
					tempmat[i][j] -= a2 * tempmat[k][j];
				}
			}
	}
	//result = true;
	return tempmat;
}

template<int rows, int cols>
bool StaticMatrix<rows,cols>::isSquare()
{
	if(rows == cols && rows > 0) return true;
	return false;
}

template<int rows, int cols>
int StaticMatrix<rows,cols>::pivot(StaticMatrix &m, int row) const 
{
    return 0;
}

template<int rows, int cols>
StaticMatrix<rows,cols> &StaticMatrix<rows,cols>::operator=(const StaticMatrix<rows,cols> &rhs)
{
	if(this == &rhs) return *this;//自己参照によるメモリリークを防ぐ

		for(int r = 0; r < rows; r++) 
		  for(int c = 0; c < cols; c++)
			value_[r][c] = rhs[r][c];
	return *this;
}

template<int rows, int cols>
StaticMatrix<rows,cols> &StaticMatrix<rows,cols>::operator+=(const StaticMatrix<rows,cols> &rhs)
{
	for(int r = 0; r < rows; r++) 
	  for(int c = 0; c < cols; c++)
			value_[r][c] += rhs[r][c];
	return *this;
}

template<int rows, int cols>
StaticMatrix<rows,cols> &StaticMatrix<rows,cols>::operator-=(const StaticMatrix<rows,cols> &rhs)
{
	for(int r = 0; r < rows; r++) 
	  for(int c = 0; c < cols; c++)
			value_[r][c] -= rhs[r][c];
	return *this;
}

template<int rows, int cols>
StaticMatrix<rows,cols> &StaticMatrix<rows,cols>::operator*=(const StaticMatrix<cols,cols> &rhs)
{
	StaticMatrix<rows,cols> mat;

	for(int r = 0;r < rows; r++)
	  for(int c = 0;c < cols; c++)
		for(int index = 0;index < cols; index ++)
			mat[r][c] += value_[r][index] * rhs[index][c];

	*this = mat;
	return *this;
}

template<int rows, int cols>
StaticMatrix<rows,cols> &StaticMatrix<rows,cols>::operator*=(double rhs)
{
	for(int r = 0; r < rows; r++) 
	  for(int c = 0; c < cols; c++)
		value_[r][c] *= rhs;
	return *this;
}

template<int rows, int cols>
StaticMatrix<rows,cols> &StaticMatrix<rows,cols>::operator/=(double rhs)
{
	for(int r = 0; r < rows; r++) 
	  for(int c = 0; c < cols; c++)
		value_[r][c] /= rhs;
	return *this;
}

template<int rows, int cols>
bool StaticMatrix<rows,cols>::operator==(const StaticMatrix<rows,cols> &rhs) const 
{
	for (int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			if(this->value_[i][j] != rhs[i][j]) return false;
	return true;
}

template<int rows, int cols>
bool StaticMatrix<rows,cols>::operator!=(const StaticMatrix<rows,cols> &rhs) const 
{
	return !(*this == rhs);
}
} /* End of namespace stf::datatype */
} /* End of namespace stf */

#endif // stf_datatype_StaticMatrix_h
