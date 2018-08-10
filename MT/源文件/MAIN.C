#include	"inc\dictsys.h"
#include	"inc\keytable.h"
#include 	"inc\stdlib.h"

const	U8	debug[]="主程序";

FAR U8 GameMagicTower();

void main(void)
{
	U16	newPhyBank,Data_Bank_Bak;
	
	SysLCDVoltage(30);
	GuiMsgBox(debug,200);
	
	GetDataBankNumber(9,&Data_Bank_Bak);	/*获取当前数据页号，作为数据页面恢复用*/
	/*  切换数据Bank */
	newPhyBank = (0xf80000 + 0x50000) >> (U8)12 ;
	DataBankSwitch(9,4,newPhyBank);
	
	GameMagicTower();
	
	DataBankSwitch(9,4,Data_Bank_Bak);	/*恢复菜单的数据区*/	
	GuiMsgBox(debug,200);
	while(1);
}


