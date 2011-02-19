/**
 * @file   matrixvector.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
/* 簡易ベクトル・行列演算ライブラリー */
/* matrixvector.h : ヘッダーファイル */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* 次の2行と最後の行の #endif はおまじない*/
#if !defined(___MATRIXVECTOR___)
#define ___MATRIXVECTOR___

namespace sgp4 {
//配列の要素をベクトル要素表記で表示
template <class Type>
int PrintVector(const Type* x, int size)
{
	cout << "(";
	for(int i=0;i<size-1;i++) {
		cout.width(10);
		cout << x[i];
		cout << ",";
	}
	cout.width(10);
	cout << x[size-1];
	cout << ")" << endl;

	return 0;
}

//行列を表示
template <class Type>
int PrintMatrix(const Type** x, int gyou, int retsu)
{
	for (int j=0;j<gyou;j++) {
		cout << "(";
		for(int i=0;i<retsu-1;i++) {
			cout.width(10);
			cout << x[j][i];
		}
		cout.width(10);
		cout << x[j][retsu-1];
		cout << ")\n";
	}
	cout << endl;

	return 0;
}


/***************************************/
/* ベクトル操作・演算用関数                 */
/***************************************/

/* dim次元のベクトルを配列として動的に確保する */
/* 注意: この関数で作ったベクトルは必ずFreeVec関数で解法しなければならない */
double* AllocVec(int dim);

/* 上のAllocVec関数で動的確保されたベクトルのメモリを解放する */
void FreeVec(double* v);

/* ベクトルva[]の中身をベクトルvb[]にコピーする */
void CopyVec(double* va, double* vb, int dim);

/* ベクトルv[]の各要素を定数a倍する */
void MultConstVec(double a, double* v, int dim);

/* 2つのベクトルva[]とvb[]の線形和 (a*va[]+b*vb[])を求め、結果をvc[]に入れる */
void LinCombVec(double a, double* va, double b,
		double* vb, double* vc, int dim);

/* ベクトルの大きさ(ノルム)を計算する */
double NormVec(double* v, int dim);

/* 2つのベクトルの内積を計算する */
double InProdVec(double* va, double* vb, int dim);


/***************************************/
/* 行列操作・演算用関数                    */
/***************************************/

/* nrow行 ncol列の行列を動的に確保する */
/* (注意: 実際には1次元配列として確保してから2次元配列に見せかけている) */
/* この関数で確保した行列は必ずFreeMat関数で解放しなければならない */
double** AllocMat(int nrow, int ncol);

/* 上のAllocMat関数で確保した行列のメモリを解放 */
void FreeMat(double** m);

/* 行列ma[][]の中身を行列mb[][]にコピーする */
void CopyMat(double** ma, double** mb, int nrow, int ncol);

/* nrc行nrc列の正方行列m[][]を単位行列Iにする */
void UnitMat(double** m, int nrc);

/* 行列m[][]の各要素を定数a倍にする */
void MultConstMat(double a, double** m, int nrow, int ncol);

//[ncol,nrow]行列を[nrow,ncol]行列に
/* 行列m[][]の転置行列mt[]を求める */
void TransMat(double** m, double** mt, int nrow,  int ncol);

/* 2つの行列ma[][]とmb[][]の線形和 (a*ma[][]+b*mb[][])を求め、結果をmc[]に入れる */
void LinCombMat(double a, double** ma, double b, double** mb, 
		double** mc, int nrow, int ncol);

/* 2つの行列ma[][]とmb[][]の積 (ma[][]*mb[][])を求め、結果をmc[]に入れる */
/* 注意: ma[][]はnra行nca列、mb[][]はnca行ncb列、mc[]はnra[]行ncb列になる */
void MultMatMat(double** ma, double** mb, double** mc, int  nra, 
		int nca, int ncb);

/* ガウス・ジョルダン法でm[][]の逆行列minv[]を求める */
void InvMatGJ(double** m, double** minv, int nrc);


/***************************************/
/* 行列・ベクトルの演算関数                 */
/***************************************/

/* 行列m[][]とベクトルva[]の積を求め、vb[]に入れる */
void MultMatVec(double** m, double* va, double* vb, int nraw, int ncol);

/* 連立一次方程式 m[][]*vx[] = va[] をガウスの消去法で解く */
void SolvLinEqGauss(double** m, double* va, double* vx, int nrc);

}

#endif

