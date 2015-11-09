
/**
 * @note
 * �傫�ȗe�ʂ��m�ۂ���ۂɃ��������u���b�N�P�ʂŊm�ۂ�
 * �ꊇ�m�ۂōs�����ꍇ�ɐ����郁�����m�ێ��s�̃P�[�X��h�~���邽�߂̃N���X�ł�
 * �u���b�N�T�C�Y�͕ύX���邱�Ƃ��ł��܂����A���������̏ꍇ�̓����b�g�͏��Ȃ��ł�
 * 
 * ��Tips
 * �u�C���X�^���X�̐����A�u���b�N�T�C�Y�̌���A�������m�ہA�g�p�A����v�̏��Ŏg�p���܂�
 * �e���v���[�g�N���X�̂��߁A�K�v�ɉ�����TYPE�����߂Ďg�p���Ă�������
 *
 * ���g�p���@
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
 * �u���b�N�P�ʃ������m�ۃN���X
 */
template <typename TYPE> 
class CBlockUnitMemory
{
private:

	// ��`
	static const int m_iDefBlockUnitSize;	// �u���b�N�P�ʂ̃T�C�Y

public:

	// �R���X�g���N�^�^�f�X�g���N�^
	CBlockUnitMemory<TYPE>();
	~CBlockUnitMemory<TYPE>();

	// �u���b�N�P�ʌ���
	void SetBlockUnitSize( const int iBlockSize ){ this->m_iBlockUnitSize = iBlockSize; }

	// �������m��
	bool AllocMemory( const int iMemorySize );

	// ���������
	void ClearMemory();

	// �������A�N�Z�X
	TYPE &GetAt( const int iIndex );

private:

	// �����o�ϐ�
	int m_iBlockUnitSize;					// 1�u���b�N�̃������T�C�Y
	int m_iBlockCount;						// �m�ۃ������̃u���b�N��

	TYPE **m_pBuffer;						// �o�b�t�@
};


/**
 * ��`
 */
template<typename TYPE>
const int CBlockUnitMemory<TYPE>::m_iDefBlockUnitSize = 100000;	// �u���b�N�P�ʂ̃T�C�Y

/**
 * �R���X�g���N�^
 */
template<class TYPE>
CBlockUnitMemory<TYPE>::CBlockUnitMemory()
	: m_iBlockUnitSize( m_iDefBlockUnitSize )
	, m_iBlockCount( 0 )
	, m_pBuffer( NULL )
{
}

/**
 * �f�X�g���N�^
 */
template<typename TYPE>
CBlockUnitMemory<TYPE>::~CBlockUnitMemory()
{
	// ���������
	this->ClearMemory();
}

/**
 * �������m��
 */
template<class TYPE>
bool CBlockUnitMemory<TYPE>::AllocMemory( const int iMemorySize )
{
	bool bResult = true;

	// ��U�������
	this->ClearMemory();

	// �m�ۃu���b�N���̌���
	this->m_iBlockCount = ( iMemorySize / this->m_iBlockUnitSize ) + 1;

	// �u���b�N���̊m�ۊJ�n
	this->m_pBuffer = new TYPE*[ this->m_iBlockCount ];

	// �u���b�N�P�ʂ̊m��
	int iIndex = 0;
	for ( int i = this->m_iBlockCount - 1; i >= 0; --i )
	{
		iIndex = (this->m_iBlockCount - 1) - i;
		this->m_pBuffer[ iIndex ] = new TYPE[ this->m_iBlockUnitSize ];
	}

	return bResult;
}

/**
 * ���������
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
 * �������A�N�Z�X
 */
template<class TYPE>
TYPE &CBlockUnitMemory<TYPE>::GetAt( const int iIndex )
{
	// �A�N�Z�X�C���f�b�N�X�̌���
	const int iAccessBlock = iIndex / this->m_iBlockUnitSize;
	const int iAccessIndex = iIndex % this->m_iBlockUnitSize;

	// �A�N�Z�X
	if ( this->m_pBuffer )
	{
		return this->m_pBuffer[ iAccessBlock ][ iAccessIndex ];
	}

	// �A�N�Z�X�ᔽ
	assert( false );
}

