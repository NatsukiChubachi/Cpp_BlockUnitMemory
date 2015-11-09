
#include <tchar.h>
#include <stdio.h>

// ブロック単位メモリ確保クラス
#include "BlockUnitMemory.h"

// メモリリーク検出用
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// メイン関数
int _tmain(int argc, _TCHAR* argv[])
{
	// メモリリーク検出
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	// ブロック単位メモリ確保処理
	CBlockUnitMemory<int> bum;
	bum.AllocMemory( 1000 );
	bum.GetAt( 0 ) = 0;
	bum.GetAt( 1 ) = 100;
	bum.GetAt( 2 ) = 200;

	printf( "num = %d \n", bum.GetAt(0) );
	printf( "num = %d \n", bum.GetAt(1) );
	printf( "num = %d \n", bum.GetAt(2) );

	bum.ClearMemory();

	// キー待ち処理
	printf( "program end.\n" );
	getchar();

	return 0;
}

