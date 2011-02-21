/**
 * @file   Matrix.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "Matrix.h"
#include "Vector.h"

namespace stf { 
namespace datatype {

Matrix::Matrix()
{
}

Matrix::Matrix(int rows, int cols)
{
	this->rows_ = rows;
	this->cols_ = cols;//ArgoUMLの制約がなければ初期化子でやるほうが低コスト
	this->value_  = new Vector[rows];
	for(int i = 0; i < rows; i++)
		this->value_[i].initVector(cols,0.0);
}

Matrix::Matrix(const Matrix &rhs)
{
	this->rows_ = rhs.rows_;
	this->cols_ = rhs.cols_;
	value_ = new Vector[rows_];
	for(int i = 0; i < rows_; i++)
		value_[i].initVector(cols_,0.0);
	for(int i = 0; i < rows_; i++)
		for(int j = 0; j < cols_; j++)
			value_[i].value_[j] = rhs[i].value_[j];
}

Matrix::~Matrix()
{
	delete[] this->value_;
}

Matrix &Matrix::unitize()
{
	//assert(rows_ == cols_);
	for(int i = 0; i < rows_; i++)
		for(int j = 0; j < cols_; j++)
			if(i == j) value_[i][j] = 1.0;
			else       value_[i][j] = 0.0;
	return *this;	
}

double Matrix::det() const 
{
	assert(cols_ == rows_);
	assert(cols_ <= 3);//とりあえず3次まで定義

	if(cols_ == 2){
		return value_[0][0] * value_[1][1] - value_[0][1] * value_[1][0];
	}
	if(cols_ == 3){
		return value_[0][0] * value_[1][1] * value_[2][2] + 
			value_[0][1] * value_[1][2] * value_[2][0] + 
			value_[0][2] * value_[1][0] * value_[2][1] -
			value_[0][0] * value_[1][2] * value_[2][1] -
			value_[0][1] * value_[1][0] * value_[2][2] -
			value_[0][2] * value_[1][1] * value_[2][0];
	}
	if(cols_ == 1){
		return value_[0][0];
	}
	assert(0);
	return 0;
}

double Matrix::trace() const
{
	assert(cols_ == rows_); 
	double v = 0;
	for(int i = 0; i < rows_; i++)
		v += value_[i][i];
	return v;
}

Matrix Matrix::trans() const 
{
	//assert(rows_ == cols_);
	Matrix temp(cols_,rows_);
	for(int i = 0; i < rows_; i++)
		for(int j = 0; j < cols_; j++)
			temp[j][i] = value_[i][j];
	return temp;
}

Matrix Matrix::inverse() const 
{
	int i, j, k;
	double a1, a2;
	//result = false;
	if(rows_ != cols_) return Matrix(rows_,cols_);

	Matrix tempmat(rows_,cols_);
	for(int i = 0; i < rows_; i++) tempmat[i][i] = 1.0;
	Matrix m = *this;//副作用を生じないように現インスタンスのコピーで計算

	for (k = 0; k < rows_; k++)
	{
		int indx = pivot(m,k);
		assert(indx != -1);
		if (indx != 0)
		{
			double* temp = tempmat.value_[k].value_;
			tempmat.value_[k].value_ = tempmat.value_[indx].value_;
			tempmat.value_[indx].value_ = temp;
		}
		a1 = m[k][k];
		for (j = 0; j < m.rows_; j++)
		{
			m[k][j] /= a1;
			tempmat[k][j] /= a1;
		}
		for (i = 0; i < m.rows_; i++)
			if (i != k)
			{
				a2 = m[i][k];
				for (j=0; j < m.rows_; j++)
				{
					m[i][j] -= a2 * m[k][j];
					tempmat[i][j] -= a2 * tempmat[k][j];
				}
			}
	}
	//result = true;
	return tempmat;
}

bool Matrix::isSquare()
{
	if(this->rows_ == this->cols_ && this->rows_ > 0) return true;
	return false;
}

int Matrix::pivot(Matrix &m, int row) const 
{
    return 0;
}

Matrix &Matrix::operator=(const Matrix &rhs)
{
	if(this == &rhs) return *this;//自己参照によるメモリリークを防ぐ
	if(rows_ == rhs.rows_ && cols_ == rhs.cols_){
		for(int i = 0; i < rows_; i++)
		  for(int j = 0; j < cols_ ; j++)
			value_[i][j] = rhs[i][j];
	}else{
		this->rows_ = rhs.rows_;
		this->cols_ = rhs.cols_;
		value_ = new Vector[rows_];
		for(int i = 0; i < rows_; i++)
			value_[i].initVector(cols_,0.0);
		for(int i = 0; i < rows_; i++)
			for(int j = 0; j < cols_; j++)
				value_[i][j] = rhs[i][j];
	}
	return *this;
}

Matrix &Matrix::operator+=(const Matrix &rhs)
{
	assert(rows_ == rhs.rows_);
	assert(cols_ == rhs.cols_);
	for(int rows = 0;rows < rows_; rows++) 
	  for(int cols = 0;cols < cols_; cols++)
		value_[rows][cols] += rhs[rows][cols];
	return *this;
}

Matrix &Matrix::operator-=(const Matrix &rhs)
{
	assert(rows_ == rhs.rows_);
	assert(cols_ == rhs.cols_);
		for(int rows = 0; rows < rows_; rows++) 
		  for(int cols = 0; cols < cols_; cols++)
			value_[rows][cols] -= rhs[rows][cols];
	return *this;
}

Matrix &Matrix::operator*=(const Matrix &rhs)
{
	assert(cols_ == rhs.rows_);
	Matrix tempmat = *this * rhs;
	*this = tempmat;
	return *this;
}

Matrix &Matrix::operator*=(double rhs)
{
	for(int rows = 0; rows < rows_; rows++) 
	  for(int cols = 0; cols < cols_; cols++)
		value_[rows][cols] *= rhs;
	return *this;
}

Matrix &Matrix::operator/=(double rhs)
{
	for(int rows = 0;rows < rows_; rows++) 
	  for(int cols = 0; cols < cols_; cols++)
		value_[rows ][cols ] /= rhs;
	return *this;
}

bool Matrix::operator==(const Matrix &rhs) const 
{
	if(rows_ != rhs.rows_) return false;
	if(cols_ != rhs.cols_) return false;
	for (int i = 0; i < rows_; i++)
		for(int j = 0; j < cols_; j++)
			if(this->value_[i][j] != rhs[i][j]) return false;
	return true;
}

bool Matrix::operator!=(const Matrix &rhs) const 
{
	return !(*this == rhs);
}

} /* End of namespace stf::datatype */
} /* End of namespace stf */
