
/**
 * @note
 * 大きな容量を確保する際にメモリをブロック単位で確保し
 * 一括確保で行った場合に生じるメモリ確保失敗のケースを防止するためのクラスです
 * ブロックサイズは変更することができますが、ごく少数の場合はメリットは少ないです
 * 
 * ※Tips
 * 「インスタンスの生成、ブロックサイズの決定、メモリ確保、使用、解放」の順で使用します
 * テンプレートクラスのため、必要に応じてTYPEを決めて使用してください
 *
 * ※使用方法
 * CBlockUnitMemory<int> bum;
 * bum.SetBlockUnitSize( 100 );
 * bum.AllocMemory( 1000 );
 * bum.GetAt(0) = 100;
 * bum.GetAt(1) = 101;
 * ...
 * bum.ClearMemory();
 *
 */

#pragma once

#include <cassert>

/**
 * ブロック単位メモリ確保クラス
 */
template <typename TYPE> 
class CBlockUnitMemory
{
private:

	// 定義
	static const int m_iDefBlockUnitSize;	// ブロック単位のサイズ

public:

	// コンストラクタ／デストラクタ
	CBlockUnitMemory<TYPE>();
	~CBlockUnitMemory<TYPE>();

	// ブロック単位決定
	void SetBlockUnitSize( const int iBlockSize ){ this->m_iBlockUnitSize = iBlockSize; }

	// メモリ確保
	bool AllocMemory( const int iMemorySize );

	// メモリ解放
	void ClearMemory();

	// メモリアクセス
	TYPE &GetAt( const int iIndex );

private:

	// メンバ変数
	int m_iBlockUnitSize;					// 1ブロックのメモリサイズ
	int m_iBlockCount;						// 確保メモリのブロック数

	TYPE **m_pBuffer;						// バッファ
};


/**
 * 定義
 */
template<typename TYPE>
const int CBlockUnitMemory<TYPE>::m_iDefBlockUnitSize = 100000;	// ブロック単位のサイズ

/**
 * コンストラクタ
 */
template<class TYPE>
CBlockUnitMemory<TYPE>::CBlockUnitMemory()
	: m_iBlockUnitSize( m_iDefBlockUnitSize )
	, m_iBlockCount( 0 )
	, m_pBuffer( NULL )
{
}

/**
 * デストラクタ
 */
template<typename TYPE>
CBlockUnitMemory<TYPE>::~CBlockUnitMemory()
{
	// メモリ解放
	this->ClearMemory();
}

/**
 * メモリ確保
 */
template<class TYPE>
bool CBlockUnitMemory<TYPE>::AllocMemory( const int iMemorySize )
{
	bool bResult = true;

	// 一旦解放する
	this->ClearMemory();

	// 確保ブロック数の決定
	this->m_iBlockCount = ( iMemorySize / this->m_iBlockUnitSize ) + 1;

	// ブロック数の確保開始
	this->m_pBuffer = new TYPE*[ this->m_iBlockCount ];

	// ブロック単位の確保
	int iIndex = 0;
	for ( int i = this->m_iBlockCount - 1; i >= 0; --i )
	{
		iIndex = (this->m_iBlockCount - 1) - i;
		this->m_pBuffer[ iIndex ] = new TYPE[ this->m_iBlockUnitSize ];
	}

	return bResult;
}

/**
 * メモリ解放
 */
template<class TYPE>
void CBlockUnitMemory<TYPE>::ClearMemory()
{
	if ( this->m_pBuffer )
	{
		for ( int i = this->m_iBlockCount - 1; i >= 0; --i )
		{
			delete[] this->m_pBuffer[ i ];
		}

		delete[] this->m_pBuffer;
		this->m_pBuffer = NULL;
	}
}

/**
 * メモリアクセス
 */
template<class TYPE>
TYPE &CBlockUnitMemory<TYPE>::GetAt( const int iIndex )
{
	// アクセスインデックスの決定
	const int iAccessBlock = iIndex / this->m_iBlockUnitSize;
	const int iAccessIndex = iIndex % this->m_iBlockUnitSize;

	// アクセス
	if ( this->m_pBuffer )
	{
		return this->m_pBuffer[ iAccessBlock ][ iAccessIndex ];
	}

	// アクセス違反
	assert( false );
}

