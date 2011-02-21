/**
 * @file   matrixvector.cpp
 * @brief  NJHILSから持ってきた軌道計算関係モジュールを，sgp4名前空間でラップして使用．
 *
 * @author 
 * @date   2011.02.16
 */

/* 簡易ベクトル・行列演算ライブラリー */
/* matrixvector.c : 実装ファイル */


#include "matrixvector.h"

namespace sgp4 {

/***************************************/
/* ベクトル操作・演算用関数                 */
/***************************************/

/* dim次元のベクトルを配列として動的に確保する */
/* 注意: この関数で作ったベクトルは必ずFreeVec関数で解法しなければならない */
double* AllocVec(int dim)
{
  double* vec;
  int i;
  vec = (double*)malloc(dim * sizeof(double)); /* メモリを確保する */

  /* きちんとメモリが確保されたかをチェック */
  if (vec == NULL) {
    fprintf(stderr,"Vector was not allocated \n");
    exit(1);
  }

  /*全ての要素を0に初期化する(必須ではない) */
  for (i=0;i<dim;i++)
    vec[i] = 0.0;

  return vec; /* 確保したメモリの先頭アドレスを返す */
}

/* 上のAllocVec関数で動的確保されたベクトルのメモリを解放する */
void FreeVec(double* v)
{
  free(v);
}

/* ベクトルva[]の中身をベクトルvb[]にコピーする */
void CopyVec(double* va, double* vb, int dim)
{
  int i;
  for (i=0;i<dim;i++)
    vb[i] = va[i];
}


/* ベクトルv[]の各要素を定数a倍する */
void MultConstVec(double a, double* v, int dim)
{
  int i;
  for (i=0;i<dim;i++)
    v[i] *= a;
}

/* 以下のベクトル操作関数は各自実装すること。 */
/* 線形結合 a*va+b*vc を計算し vc に入れる  */
void LinCombVec(double a, double* va, double b, double* vb, double* vc, int dim)
{
	int i;
	for (i=0;i<dim;i++)
		vc[i] = a * va[i] + b * vb[i];
}

/* ノルムを計算 */
double NormVec(double* v, int dim)
{
	int i;
	double sum = 0.0; /* ノルムの平方 */
	for (i=0;i<dim;i++)
		sum += v[i] * v[i];
	sum = sqrt(sum);
	return sum;
}

/* 2つのベクトルの内積を計算 */
double InProdVec(double* va, double* vb, int dim)
{
	int i;
	double sum = 0 ; /* 内積 */
	for (i=0;i<dim;i++)
		sum += va[i] * vb[i];
	return sum;
}

/***************************************/
/* 行列操作・演算用関数                    */
/***************************************/
/* nrow行 ncol列の行列を動的に確保する */
/* この関数で確保した行列は必ずFreeMat関数で解放しなければならない */
double** AllocMat(int nrow, int ncol)
{
  double** m;
  int i;
  /* 各行の先頭ポインタを納める配列 */
  m = (double**)malloc(nrow * sizeof(double*)); 

  /* 実際のデータを納める領域を1次元配列として確保 */
  m[0] = (double*)malloc(nrow*ncol*sizeof(double));
  /* 必須ではないが要素を全て0.0に設定 */
  for (i=0;i<nrow*ncol;i++)
    m[0][i] = 0.0;

  /* 各m[i]にi行目のデータの先頭ポインタを格納 */
  for (i=1;i<nrow;i++)
    m[i] = &m[0][i*ncol];

  return m;
}

/* 上のAllocMat関数で確保した行列のメモリを解放 */
void FreeMat(double** m)
{
  free(m[0]);
  free(m);
}

/* 以下の行列演算関数は各自実装 */

/* ma[][]の中身をmb[][]にコピーする */
void CopyMat(double** ma, double** mb, int nrow, int ncol)
{
	int i, j;
	for (i=0;i<nrow;i++){
		for (j=0;j<ncol;j++)
			mb[i][j] = ma[i][j];
	}
}

/* nrc行nrc列の行列m[][]を単位行列Iにする */
void UnitMat(double** m, int nrc)
{
	int i, j;
	for (i=0;i<nrc;i++){
		for (j=0;j<nrc;j++){
			if (i==j)
				m[i][j] = 1;
			else
				m[i][j] = 0;
		}
	}
}

/* 行列 m[][] の各要素を定数a倍にする */
void MultConstMat(double a, double** m, int nrow, int ncol)
{
	int i,j;
	for (i=0;i<nrow;i++)
		for (j=0;j<ncol;j++)
			m[i][j] *= a;
}

/*
// 行列 m[][] の転置行列mt[][]を求める
void TransMat2(double** m, double** mt, int nrow,  int ncol)
{
	int i,j;
	for (i=0;i<nrow;i++)
		for (j=0;j<ncol;j++)
			mt[j][i] = m[i][j];
}
*/

//[ncol,nrow]行列を[nrow,ncol]行列に
/* 行列m[][]の転置行列mt[]を求める*/
void TransMat(double** m, double** mt, int nrow,  int ncol)
{ 
	int i,j;
	for (i=0;i<nrow;i++){
		for (j=0;j<ncol;j++)
		 mt[i][j] = m[j][i];
	}
}

/* 2つの行列ma[][]とmb[][]の線形和 (a*ma[][]+b*mb[][])を求め、結果をmc[]に入れる */
void LinCombMat(double a, double** ma, double b, double** mb, double** mc, int nrow, int ncol)
{
	int i,j;
	for (i=0;i<nrow;i++)
		for (j=0;j<ncol;j++)
			mc[i][j] = a * ma[i][j] + b * mb[i][j];
}


/* 2つの行列ma[][]とmb[][]の積 (ma[][]*mb[][])を求め、結果をmc[]に入れる */
/* 注意: ma[][]はnra行nca列、mb[][]はnca行ncb列、mc[]はnra[]行ncb列になる */

void MultMatMat(double** ma, double** mb, double** mc, int  nra, int nca, int ncb)
{
	int i,j,k;

	for (i=0;i<nra;i++){
		for (j=0;j<ncb;j++){
			mc[i][j] = 0;
			for (k=0;k<nca;k++){
				mc[i][j] += ma[i][k] * mb[k][j];
			}
		}
	}
}

/* ガウス・ジョルダン法でm[][]の逆行列minv[]を求める */

 void InvMatGJ(double** m, double** minv, int nrc)
 {
 int i,j,k;
 double a,b;
 double **A;
 A=AllocMat(nrc,nrc);
 CopyMat(m,A,nrc,nrc);
 UnitMat(minv,nrc);
  for(j=0;j<nrc;j++){
  if(A[j][j]!=0){
  a=A[j][j];
  for(i=0;i<nrc;i++){
  A[j][i]/=a;
  minv[j][i]/=a;
  }
  for(i=0;i<nrc;i++){
  if(i!=j){
  b=A[i][j];
  for(k=0;k<nrc;k++){
  A[i][k]-=b*A[j][k];
  minv[i][k]-=b*minv[j][k];
  }
  }
 }
}
}
FreeMat(A);
}


/***************************************/
/* 行列・ベクトルの演算関数                 */
/***************************************/
/* 行列m[][]とベクトルva[]の積を求め、vb[]に入れる */
void MultMatVec(double** m, double* va, double* vb, int nraw, int ncol)
{
  int i,j;

  for (i=0;i<nraw;i++) {
    vb[i] = 0.0;
    for (j=0;j<ncol;j++)
      vb[i] += m[i][j]*va[j];
  }
}

/* 以下の行列・ベクトル演算関数は各自実装 */

/* ガウスの消去法により1次連立方程式を解く */
void SolvLinEqGauss(double** A, double* Va, double* vx, int nrc)
{
	int i,j,k;
	double temp, div, kakeru, sum;
	double *va;
	double **m;
	m = AllocMat(nrc,nrc);
	va = AllocVec(nrc);

	CopyMat(A,m,nrc,nrc);
	CopyVec(Va,va,nrc);

	for (i=0;i<nrc;i++){
		for(j=i+1;j<nrc;j++){ /* ピボット選択（初項の絶対値が最大の行を一番上に持ってくる） */
			if(m[i][i]*m[i][i]<m[j][i]*m[j][i]){
				temp = va[i];
				va[i] = va[j];
				va[j] = temp;
				for(k=i;k<nrc;k++){
					temp = m[i][k];
					m[i][k] = m[j][k];
					m[j][k] = temp;
				}
			}
		}
		/* i行目を1/m[i][i]倍 */
		div = m[i][i];
		va[i] /=div;
		for(j=i;j<nrc;j++)
			m[i][j] /= div;
		/* j行目からi行目のm[j][i]倍を引く */
		for(j=i+1;j<nrc;j++){ 
			kakeru = m[j][i];
			va[j] -= kakeru*va[i];
			for(k=i;k<nrc;k++)
				m[j][k] -= kakeru*m[i][k];
		}
	}
	/* 後退代入により解を求める */
	vx[nrc-1] = va[nrc-1];
	for (j=2;j<=nrc;j++){
		sum = 0;
		for(i = nrc-j+1;i<nrc;i++)
			sum += vx[i]*m[nrc-j][i];
		vx[nrc-j] = va[nrc-j] - sum;
	}

	FreeMat(m);
	FreeVec(va);
}

}
