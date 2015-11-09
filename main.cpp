
#include <tchar.h>
#include <stdio.h>

// �u���b�N�P�ʃ������m�ۃN���X
#include "BlockUnitMemory.h"

// ���������[�N���o�p
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// ���C���֐�
int _tmain(int argc, _TCHAR* argv[])
{
	// ���������[�N���o
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	// �u���b�N�P�ʃ������m�ۏ���
	CBlockUnitMemory<int> bum;
	bum.AllocMemory( 1000 );
	bum.GetAt( 0 ) = 0;
	bum.GetAt( 1 ) = 100;
	bum.GetAt( 2 ) = 200;

	printf( "num = %d \n", bum.GetAt(0) );
	printf( "num = %d \n", bum.GetAt(1) );
	printf( "num = %d \n", bum.GetAt(2) );

	bum.ClearMemory();

	// �L�[�҂�����
	printf( "program end.\n" );
	getchar();

	return 0;
}

