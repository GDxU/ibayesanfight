#include 	"inc\dictsys.h"
#include	"mtower.h"

extern U8	g_GameMTReadKey,g_GameMTTimeOut,g_GameMTTopFloor;
extern U16	g_GameMTKBState;
extern U8	g_GameMTMapX,g_GameMTMapY,g_GameMTHeroX,g_GameMTHeroY,g_GameMTJuidgeX,g_GameMTJuidgeY;
extern U8	g_GameMTBuf[1900],g_GameMTKey[3];
extern U16	g_GameMTHeroDamige,g_GameMTHeroDefence,g_GameMTHeroMoney,g_GameMTHeroExp;
extern U8	g_GameMTHeroDir,g_GameMTFloor,*g_GameMTCurMap;
extern U32 g_GameMTHeroLife;

extern	U8	GameMTUnitPic[][32];
extern	U8	GameMTWorkPad[];
extern	U8	GameMTTalkData[][20];
extern	U8	GameMTTalkSide[];
extern	U8	GameMTTalkDown[];
extern	U8	GameMTTalkUp[];
extern	U8	GameMTTalkSigh[][26];
extern	U8	GameMTHeroPic[][32];
extern	U8	GameMTNum39[];
extern	U8	GameMTNum35[];
extern	U8	GameMTNum78[];
extern	U8	GameMTBattlePad[];
extern	U8	GameMTMonName[][10];
extern	U16	GameMTMonData[][5];
extern	U8	GameMTVictory[];
extern	U8	GameMTStartPoint[][4];

/***********************************************************************
 * 函数名:	GameMTGetTalk(U16 number,U8	*chars)
 * 说明:		将对话数据装入内存
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR void GameMTGetTalk(U16 number,U8	*chars)
{
	switch(number)
	{
		/*case 246:		SysMemcpy(chars,"勇士：是啊，公主，",20);break;
		case 247:		SysMemcpy(chars,"我是奉国王的命令来",20);break;
		case 248:		SysMemcpy(chars,"救你的，请你快随我",20);break;
		case 249:		SysMemcpy(chars,"出去吧。          ",20);break;
		case 250:		SysMemcpy(chars,"公主：不，我还不想",20);break;
		case 251:		SysMemcpy(chars,"走。              ",20);break;
		case 252:		SysMemcpy(chars,"勇士：为什么？这里",20);break;
		case 253:		SysMemcpy(chars,"面到处都是恶魔。  ",20);break;
		case 254:		SysMemcpy(chars,"公主：正是因为这里",20);break;
		case 255:		SysMemcpy(chars,"到处都是恶魔，所以",20);break;
		case 256:		SysMemcpy(chars,"才不可以就这样出去",20);break;
		case 257:		SysMemcpy(chars,"，我要看着那个大恶",20);break;
		case 258:		SysMemcpy(chars,"魔被杀死。勇士，  ",20);break;
		case 259:		SysMemcpy(chars,"如果你能够将那个大",20);break;
		case 260:		SysMemcpy(chars,"恶魔杀死，我就和你",20);break;
		case 261:		SysMemcpy(chars,"一起出去。        ",20);break;
		case 262:		SysMemcpy(chars,"勇士：大恶魔？我已",20);break;
		case 263:		SysMemcpy(chars,"经杀死了一个魔王。",20);break;
		case 264:		SysMemcpy(chars,"                  ",20);break;
		case 265:		SysMemcpy(chars,"公主：大恶魔在这座",20);break;
		case 266:		SysMemcpy(chars,"塔的最顶层，你杀死",20);break;
		case 267:		SysMemcpy(chars,"的可能是一个小队长",20);break;
		case 268:		SysMemcpy(chars,"之类的恶魔。      ",20);break;
		case 269:		SysMemcpy(chars,"勇士：好，那你等着",20);break;
		case 270:		SysMemcpy(chars,"，等我杀了那个大恶",20);break;
		case 271:		SysMemcpy(chars,"魔再来这里找你。  ",20);break;
		case 272:		SysMemcpy(chars,"公主：大恶魔比你刚",20);break;
		case 273:		SysMemcpy(chars,"才杀死的那个厉害多",20);break;
		case 274:		SysMemcpy(chars,"了，而且它还会变身",20);break;
		case 275:		SysMemcpy(chars,"，变身后后的魔王它",20);break;
		case 276:		SysMemcpy(chars,"的攻击力和防御力  ",20);break;
		case 277:		SysMemcpy(chars,"提升至少一半以上，",20);break;
		case 278:		SysMemcpy(chars,"你要小心，请一定要",20);break;
		case 279:		SysMemcpy(chars,"杀死大魔王。      ",20);break;
		case 280:		SysMemcpy(chars,"公主：你杀死大魔王",20);break;
		case 281:		SysMemcpy(chars,"了吗？            ",20);break;
		case 282:		SysMemcpy(chars,"勇士：还，还没有杀",20);break;
		case 283:		SysMemcpy(chars,"死。              ",20);break;
		case 284:		SysMemcpy(chars,"勇士：大魔王，你的",20);break;
		case 285:		SysMemcpy(chars,"死期到了。        ",20);break;
		case 286:		SysMemcpy(chars,"冥灵魔王：哈哈哈，",20);break;
		case 287:		SysMemcpy(chars,"你也真是有意思，别",20);break;
		case 288:		SysMemcpy(chars,"以为仙女给了你力量",20);break;
		case 289:		SysMemcpy(chars,"就可以打败我，想打",20);break;
		case 290:		SysMemcpy(chars,"败我你还早着呢。  ",20);break;
		case 291:		SysMemcpy(chars,"勇士：废话少说，去",20);break;
		case 292:		SysMemcpy(chars,"死吧。            ",20);break;
		case 293:		SysMemcpy(chars,"冥灵魔王：看不出你",20);break;
		case 294:		SysMemcpy(chars,"还有两下子，有本事",20);break;
		case 295:		SysMemcpy(chars,"的话就来第二十一层",20);break;
		case 296:		SysMemcpy(chars,"。在那里，你就可以",20);break;
		case 297:		SysMemcpy(chars,"见到我真正的实    ",20);break;
		case 298:		SysMemcpy(chars,"力了。你要救的公主",20);break;
		case 299:		SysMemcpy(chars,"会在那里等你的。  ",20);break;
		case 300:		SysMemcpy(chars,"公主(远方传来)：啊",20);break;
		case 301:		SysMemcpy(chars,"！救命啊。        ",20);break;
		case 302:		SysMemcpy(chars,"公主：你终于来了，",20);break;
		case 303:		SysMemcpy(chars,"快杀死大恶魔了。  ",20);break;
		case 304:		SysMemcpy(chars,"勇士：好，公主，你",20);break;
		case 305:		SysMemcpy(chars,"等着。            ",20);break;
		case 306:		SysMemcpy(chars,"勇士：杰克，你可以",20);break;
		case 307:		SysMemcpy(chars,"帮我打开旁边那神秘",20);break;
		case 308:		SysMemcpy(chars,"的门吗？          ",20);break;
		case 309:		SysMemcpy(chars,"杰克：如果你可以让",20);break;
		case 310:		SysMemcpy(chars,"旁边的恶魔解开我身",20);break;
		case 311:		SysMemcpy(chars,"上的定身咒语，我就",20);break;
		case 312:		SysMemcpy(chars,"可以帮你打开门。  ",20);break;
		case 313:		SysMemcpy(chars,"勇士：好，你等一下",20);break;
		case 314:		SysMemcpy(chars,"。                ",20);break;
		case 315:		SysMemcpy(chars,"勇士：大魔王，我来",20);break;
		case 316:		SysMemcpy(chars,"了。              ",20);break;
		case 317:		SysMemcpy(chars,"冥灵魔王：好，你能",20);break;
		case 318:		SysMemcpy(chars,"来到我这里，还真是",20);break;
		case 319:		SysMemcpy(chars,"不简单。          ",20);break;
		case 320:		SysMemcpy(chars,"勇士：哈，要打败你",20);break;
		case 321:		SysMemcpy(chars,"的手下还不是小菜一",20);break;
		case 322:		SysMemcpy(chars,"碟？              ",20);break;
		case 323:		SysMemcpy(chars,"冥灵魔王：我和那些",20);break;
		case 324:		SysMemcpy(chars,"家伙不一样。      ",20);break;
		case 325:		SysMemcpy(chars,"勇士：那杰克是怎么",20);break;
		case 326:		SysMemcpy(chars,"回事？            ",20);break;
		case 327:		SysMemcpy(chars,"冥灵魔王：那是我叫",20);break;
		case 328:		SysMemcpy(chars,"灵法师放的定身咒语",20);break;
		case 329:		SysMemcpy(chars,"。                ",20);break;
		case 330:		SysMemcpy(chars,"勇士：快叫灵法师解",20);break;
		case 331:		SysMemcpy(chars,"开咒语。          ",20);break;
		case 332:		SysMemcpy(chars,"冥灵魔王：很遗憾，",20);break;
		case 333:		SysMemcpy(chars,"两个灵法师刚才都被",20);break;
		case 334:		SysMemcpy(chars,"你打死了。        ",20);break;
		case 335:		SysMemcpy(chars,"勇士：那你亲自解开",20);break;
		case 336:		SysMemcpy(chars,"咒语。            ",20);break;
		case 337:		SysMemcpy(chars,"冥灵魔王：打败我之",20);break;
		case 338:		SysMemcpy(chars,"后自动解开。      ",20);break;
		case 339:		SysMemcpy(chars,"冥灵魔王：啊，怎么",20);break;
		case 340:		SysMemcpy(chars,"可能，我怎么可能会",20);break;
		case 341:		SysMemcpy(chars,"被你打败呢？不，不",20);break;
		case 342:		SysMemcpy(chars,"要这样。          ",20);break;*/
		case 343:		SysMemcpy(chars,"勇士：我现在就要带",20);break;
		case 344:		SysMemcpy(chars,"走公主，你不等阻止",20);break;
		case 345:		SysMemcpy(chars,"我了吧？          ",20);break;
		case 346:		SysMemcpy(chars,"冥灵魔王：哈哈哈，",20);break;
		case 347:		SysMemcpy(chars,"就算你现在带走公主",20);break;
		case 348:		SysMemcpy(chars,"也来不及了，因为我",20);break;
		case 349:		SysMemcpy(chars,"使用了魔法，这座塔",20);break;
		case 350:		SysMemcpy(chars,"还有90秒就倒了，  ",20);break;
		case 351:		SysMemcpy(chars,"我先走了。        ",20);break;
		case 352:		SysMemcpy(chars,"勇士：公主，我们走",20);break;
		case 353:		SysMemcpy(chars,"吧。              ",20);break;
		case 354:		SysMemcpy(chars,"公主：好，快走吧。",20);break;
		case 355:		SysMemcpy(chars,"                  ",20);break;
		case 356:		SysMemcpy(chars,"勇士：杰克，快走吧",20);break;
		case 357:		SysMemcpy(chars,"。                ",20);break;
		case 358:		SysMemcpy(chars,"杰克：好，我去开门",20);break;
		case 359:		SysMemcpy(chars,"。                ",20);break;
		case 360:		SysMemcpy(chars,"杰克：别管我，先去",20);break;
		case 361:		SysMemcpy(chars,"救公主。          ",20);break;
		case 362:		SysMemcpy(chars,"啊，<风之罗盘>不见",20);break;
		case 363:		SysMemcpy(chars,"了，怎么办？      ",20);break;
		case 364:		SysMemcpy(chars,"没有时间了，快走吧",20);break;
		case 365:		SysMemcpy(chars,"。                ",20);break;
		case 366:		SysMemcpy(chars,"大魔头被打败了，公",20);break;
		case 367:		SysMemcpy(chars,"主也被救出了塔，由",20);break;
		case 368:		SysMemcpy(chars,"于仙女能力的恢复，",20);break;
		case 369:		SysMemcpy(chars,"魔法消除了，魔塔也",20);break;
		case 370:		SysMemcpy(chars,"没有倒。当勇士和  ",20);break;
		case 371:		SysMemcpy(chars,"公主一起走出塔来的",20);break;
		case 372:		SysMemcpy(chars,"时候，国王也带着军",20);break;
		case 373:		SysMemcpy(chars,"队来到了岛外。一切",20);break;
		case 374:		SysMemcpy(chars,"都是那么的平常。  ",20);break;
		case 375:		SysMemcpy(chars,"回国后，国王为勇士",20);break;
		case 376:		SysMemcpy(chars,"和公主举行了隆重而",20);break;
		case 377:		SysMemcpy(chars,"盛大的婚礼，并且宣",20);break;
		case 378:		SysMemcpy(chars,"布由勇士继承国王的",20);break;
		case 379:		SysMemcpy(chars,"位置。            ",20);break;
		case 380:		SysMemcpy(chars,"从此以后，勇士和公",20);break;
		case 381:		SysMemcpy(chars,"主就幸福地生活在一",20);break;
		case 382:		SysMemcpy(chars,"起了。            ",20);break;
		case 383:		SysMemcpy(chars,"突然传来了一阵巨响",20);break;
		case 384:		SysMemcpy(chars,"，魔塔倒了，勇士和",20);break;
		case 385:		SysMemcpy(chars,"公主却没有逃出塔外",20);break;
		case 386:		SysMemcpy(chars,"。                ",20);break;
		case 387:		SysMemcpy(chars,"勇士请重新再来过吧",20);break;
		case 388:		SysMemcpy(chars,"。                ",20);break;
		case 389:		SysMemcpy(chars,"{得到三种钥匙各一 ",20);break;
		case 390:		SysMemcpy(chars,"把}               ",20);break;
		case 391:		SysMemcpy(chars,"{得到<三号钥匙>： ",20);break;
		case 392:		SysMemcpy(chars,"可以打开三号门}   ",20);break;
		case 393:		SysMemcpy(chars,"{得到<一号钥匙>： ",20);break;
		case 394:		SysMemcpy(chars,"可以打开一号门}   ",20);break;
		case 395:		SysMemcpy(chars,"{得到<青锋剑>：   ",20);break;
		case 396:		SysMemcpy(chars,"攻击 + 70}        ",20);break;
		case 397:		SysMemcpy(chars,"{得到<黄金盾>：   ",20);break;
		case 398:		SysMemcpy(chars,"防御 + 85}        ",20);break;
		case 399:		SysMemcpy(chars,"{得到<小飞羽>：   ",20);break;
		case 400:		SysMemcpy(chars,"等级提升一级。}   ",20);break;
		case 401:		SysMemcpy(chars,"{得到<大金币>：   ",20);break;
		case 402:		SysMemcpy(chars,"金币 + 300}       ",20);break;
		case 403:		SysMemcpy(chars,"{得到<幸运十字架> ",20);break;
		case 404:		SysMemcpy(chars,"把它交给仙女，可以",20);break;
		case 405:		SysMemcpy(chars,"将自身的所有能力提",20);break;
		case 406:		SysMemcpy(chars,"升一些，包括攻击、",20);break;
		case 407:		SysMemcpy(chars,"防御和生命。}     ",20);break;
		case 408:		SysMemcpy(chars,"{得到<钢剑>： 攻击",20);break;
		case 409:		SysMemcpy(chars,"+ 50}             ",20);break;
		case 410:		SysMemcpy(chars,"{得到<钢盾>： 防御",20);break;
		case 411:		SysMemcpy(chars,"+ 30}             ",20);break;
		case 412:		SysMemcpy(chars,"{得到<星光神榔>： ",20);break;
		case 413:		SysMemcpy(chars,"把它交给第四层的杰",20);break;
		case 414:		SysMemcpy(chars,"克，杰克会用它打开",20);break;
		case 415:		SysMemcpy(chars,"第十八层的隐藏地面",20);break;
		case 416:		SysMemcpy(chars,"。}               ",20);break;
		case 417:		SysMemcpy(chars,"{得到<大飞羽>：   ",20);break;
		case 418:		SysMemcpy(chars,"等级提升三级。}   ",20);break;
		case 419:		SysMemcpy(chars,"{得到<圣水瓶>：   ",20);break;
		case 420:		SysMemcpy(chars,"可以将你的体质增加",20);break;
		case 421:		SysMemcpy(chars,"一倍(生命加倍)。} ",20);break;
		case 422:		SysMemcpy(chars,"                  ",20);break;
		case 423:		SysMemcpy(chars,"{得到<圣光剑>：   ",20);break;
		case 424:		SysMemcpy(chars,"攻击 + 120}       ",20);break;
		case 425:		SysMemcpy(chars,"{得到<圣光盾>：   ",20);break;
		case 426:		SysMemcpy(chars,"防御 + 120}       ",20);break;
		case 427:		SysMemcpy(chars,"{得到<星光神剑>： ",20);break;
		case 428:		SysMemcpy(chars,"攻击 + 150}       ",20);break;
		case 429:		SysMemcpy(chars,"{得到<光芒神盾>： ",20);break;
		case 430:		SysMemcpy(chars,"防御 + 190    }   ",20);break;
		case 431:		SysMemcpy(chars,"{得到<风之罗盘>： ",20);break;
		case 432:		SysMemcpy(chars,"该宝物可以随意在已",20);break;
		case 433:		SysMemcpy(chars,"经走过的楼层间自由",20);break;
		case 434:		SysMemcpy(chars,"上下，按下键盘上的",20);break;
		case 435:		SysMemcpy(chars,"[输入]就可以使用  ",20);break;
		case 436:		SysMemcpy(chars,"{得到<圣光徽>}：  ",20);break;
		case 437:		SysMemcpy(chars,"该宝物可以查看当前",20);break;
		case 438:		SysMemcpy(chars,"怪物的基本情况。按",20);break;
		case 439:		SysMemcpy(chars,"下键盘上的[查找]就",20);break;
		case 440:		SysMemcpy(chars,"可以进行查看。    ",20);break;
		case 441:		SysMemcpy(chars,"怪物认为你能力太低",20);break;
		case 442:		SysMemcpy(chars,"，拒绝战斗。      ",20);break;
		case 443:		SysMemcpy(chars,"怪物认为你生命太低",20);break;
		case 444:		SysMemcpy(chars,"，拒绝战斗。      ",20);break;
		case 445:		SysMemcpy(chars,"{得到<二号钥匙>： ",20);break;
		case 446:		SysMemcpy(chars,"可以打开二号门}   ",20);break;
		case 447:		SysMemcpy(chars,"你好，英雄的人类，",20);break;
		case 448:		SysMemcpy(chars,"只要你有足够的经验",20);break;
		case 449:		SysMemcpy(chars,"，我就可以让你变得",20);break;
		case 450:		SysMemcpy(chars,"更强大：          ",20);break;
		case 451:		SysMemcpy(chars,"提升一级(需100点) ",20);break;
		case 452:		SysMemcpy(chars,"增加攻击5(需30点) ",20);break;
		case 453:		SysMemcpy(chars,"增加防御5(需30点) ",20);break;
		case 454:		SysMemcpy(chars,"     离  开       ",20);break;
		case 455:		SysMemcpy(chars,"提升三级(需270点) ",20);break;
		case 456:		SysMemcpy(chars,"增加攻击17(需95点)",20);break;
		case 457:		SysMemcpy(chars,"增加防御17(需95点)",20);break;
		case 458:		SysMemcpy(chars,"相信你一定有特殊的",20);break;
		case 459:		SysMemcpy(chars,"需要，只要你有金币",20);break;
		case 460:		SysMemcpy(chars,"，我就可以帮你：  ",20);break;
		case 461:		SysMemcpy(chars,"购买1号钥匙($10)  ",20);break;
		case 462:		SysMemcpy(chars,"购买2号钥匙($50)  ",20);break;
		case 463:		SysMemcpy(chars,"购买3号钥匙($100) ",20);break;
		case 464:		SysMemcpy(chars,"相信你一定有特殊的",20);break;
		case 465:		SysMemcpy(chars,"需要，只要你有钥匙",20);break;
		case 466:		SysMemcpy(chars,"，我就可以帮你：  ",20);break;
		case 467:		SysMemcpy(chars,"卖出1号钥匙($7)   ",20);break;
		case 468:		SysMemcpy(chars,"卖出2号钥匙($35)  ",20);break;
		case 469:		SysMemcpy(chars,"卖出3号钥匙($70)  ",20);break;
		case 470:		SysMemcpy(chars,"想增加你的能力吗？",20);break;
		case 471:		SysMemcpy(chars,"如果你有25个金币，",20);break;
		case 472:		SysMemcpy(chars,"你可以任意选一项：",20);break;
		case 473:		SysMemcpy(chars,"   增加800点生命  ",20);break;
		case 474:		SysMemcpy(chars,"   增加4点攻击    ",20);break;
		case 475:		SysMemcpy(chars,"   增加4点防御    ",20);break;
		case 476:		SysMemcpy(chars,"想要增加你的能力吗",20);break;
		case 477:		SysMemcpy(chars,"？如果你有 100个金",20);break;
		case 478:		SysMemcpy(chars,"币，你可以任意选一",20);break;
		case 479:		SysMemcpy(chars,"项：              ",20);break;
		case 480:		SysMemcpy(chars,"  增加4000点生命  ",20);break;
		case 481:		SysMemcpy(chars,"  增加20点攻击    ",20);break;
		case 482:		SysMemcpy(chars,"  增加20点防御    ",20);break;
		case 483:		SysMemcpy(chars,"{得到<铁剑>： 攻击",20);break;
		case 484:		SysMemcpy(chars,"+ 10}             ",20);break;
		case 485:		SysMemcpy(chars,"{得到<铁盾>： 防御",20);break;
		case 486:		SysMemcpy(chars,"+ 10}             ",20);break;	
		case 487:		SysMemcpy(chars,"开发团队：        ",20);break;
		case 488:		SysMemcpy(chars,"   华中科技大学   ",20);break;
		case 489:		SysMemcpy(chars,"    计算机协会    ",20);break;
		case 490:		SysMemcpy(chars,"程序设计：        ",20);break;
		case 491:		SysMemcpy(chars,"罗博明(SavageKing)",20);break;
		case 492:		SysMemcpy(chars,"策划：            ",20);break;
		case 493:		SysMemcpy(chars,"      王青海      ",20);break;
		case 494:		SysMemcpy(chars,"哎呀，风之罗盘怎么",20);break;
		case 495:		SysMemcpy(chars,"不见了？          ",20);break;
	}
}

/***********************************************************************
 * 函数名:	GameMTGetMapData()
 * 说明:		将地图数据装入内存
 * 输入参数:	无 
 * 返回值  :	无
 * 修改历史:
 *              姓名              日期             说明
 *             ------          ----------      -------------
 *             罗博明           2005.1.25        完成基本功能
***********************************************************************/
FAR void GameMTGetMapData()
{
	SysMemcpy(g_GameMTCurMap,"32222,2222332222(2222332222(2222332222(2222332222(2222332222(2222333222(2223333333)33333m3m3(8(3m3mmmmmm(mmmmmmmmmm(mmmmm,(IkQk(((((3333333333(E([)(3EIE3(I[?3(3EIE3(3)33(333U3(I2(3()jki3(>(J3(33333(3)33((((((((2(33+333)3E9I3K((3IeJE@I3(1(3III13(X(3?>IK3(3>393?>IJ3(3I3I3?>IY3(3I3I3333)3(3(3((()((3(3)33)33)33(n((((3(Y(((3)33*30303(3I39E3(3(3(3I39E3(3(3,3?39E37363CQI3/.-3333QI(3(((3(i(I[(33)33(3(3)33([(3I3Q(((333(3I3ik3(iQi(3I3Qk33333(((3((((((33)33(3333i3Q(Q3(3((((3>iI3(1(3333?9I3,(U(3(5(3(U()3)3(((3)3)(3(33033(3((3[3PhP3[3(i3E3>P>3E3ii3E33+33E3iQ3E3eOe3E3Q(3(3?e?3(3((3(33*33(3((3(3I(I3(3(,3(U(((U(31L3E39j((jIJ(3?3j((((jIP3(32(33)33()j3B23(e26P3(3333(((2?3(((i[((((>33U3333((((73U3(((eO(333i3)3*3)3((3(3i3>)(31(i(((3I3,3DZ3>3ITo399ZI3?3(IT3d9Ih*(*h(I3(d((3O3(((3f(333+33333)3((R(III(R(((3333333333(3P)P(((((3(3)3)3333*3(3P3((33((3(((3,())(13,(((((((33333(h3*3Z(333(h>3N3?Z(3((3330333((((*N0H0N*(((333303333((3E?3N3>E3((3IE3*3EI3((33JJ9JJ33(((333+333((3(()1(()((313((((3(IZ((3(33)3)33((3(3((*((3?(3(3_333P3UP3(3E3,((3Uh3>3E33333(P3U3(((3(h((3U333O3)33(3(Z(3Z3((((333)3(333(((_((3(TNT(:I(333(((3(I(f)(((3()Z3)33(333(3I(((3(3(((3I(((+(313(3E3*33(333(33>V?3_3,3(3E3)33((()(3IZEZ33*33(3I*ZE3d_d3()Z<*Z)9d93(3((33>f3f?33(((33)3)33(d(((((3(((d9(3(33333(33P3((III((3Ih3(3333)33IP3(0(13()h((333333)33((3E>?3(h(3I(3E>?+_3_3I,3E>?3J3J3EE3I3J3K39;9E3I3J3K3OOOE3I3J3K3(O()3)3)3)33*3(((((3((((()33*333*33)>3(b9g9b(3?>3f33333f3?>3f3/.-3f3?33+3E(E3+331(((((((((,6>3(YXY(39G?(3(3)3(3(9((3(3X3(3(((g3(3I3(3^(gc3(3I3(3]^3*3(3E3(3*3((((3E3((((333(333(333>g)ccScc)g?33333*33333,(((((((((1(g(((((3(c((33333)3(3((3((b((3(3(93+333(3(3(Y3((c3b3?3(X3(`03S3?3(Y3c073b3?3>(33333(3(3>(Y(3(((c(3>33(3933333(1((*(,3M`)(3(^L,(((((33(9333339(33(3333333(33(333A333(33(3330333(33(E33c33E(33(223`322(33(223c322(33(223*322(33bSb*(*bSb333333133333((((12,(((((222222222((223333322((233736332((233>3>332((233?3?332((223(3(322((223)3)322((222(((222((2222+2222((((((((((((22222(1222222222(2222222222(2222222223+3222222233(3322222233W3322222233(3322222233,332222222333222222222222222222222222222^`(((((((^2`22222222(2(2^((((((^2(2(22222222(2(2^(((^22(2^((222(22(22222^(^22`22212(2222^`(l(2^((^2222222222(,(l(((((((^22222222222222222222222222222222222223332222222334332222223303322222233+3322222223+3222222222222222222222222221((((((((((((((((((((((2(22222(2((2(22222(2((2(22,22(2((2(22(22(2((2W22(22W2((2022a2202((2F22(22=2((2222(2222((2222(2222(((((((((((1l?NE`K`EN?l92I2J2J2I292>N(^(^(N>2E2I2(1(2I2E`J^(((((^J`K2(2(2(2(2K`J^(((((^J`E2I2(,(2I2E2>N(^(^(N>292I2J2J2I29l?NE`K`EN?l2222222222222(42a25(222((22]22((22(((2]2(((222(((((((2222(((((((22222((2((2222222n1n2222222222222222222222222222222222222",2662);
	g_GameMTCurMap[177]=92;
	g_GameMTCurMap[210]=92;
	g_GameMTCurMap[631]=92;
	g_GameMTCurMap[643]=92;
	g_GameMTCurMap[647]=92;
	g_GameMTCurMap[659]=92;
}