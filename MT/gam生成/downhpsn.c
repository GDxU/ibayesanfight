#include	"inc\dictsys.h"
#include 	"inc\stdlib.h"
#include	"inc\shell.h"
#include	"inc\filetype.h"

extern	U16		GameMagicTower;

const	TypeDownAppHead		downAppHead = 
{
	{
		FT_GAME,
		DICT_VER_A600,
		"Ä§    Ëþ",
		STR_CORP_NAME,
		TRUE,
		""
	},
	GameMagicTower,
	0x10000,
};