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
 * ������:	GameMTGetTalk(U16 number,U8	*chars)
 * ˵��:		���Ի�����װ���ڴ�
 * �������:	�� 
 * ����ֵ  :	��
 * �޸���ʷ:
 *              ����              ����             ˵��
 *             ------          ----------      -------------
 *             �޲���           2005.1.25        ��ɻ�������
***********************************************************************/
FAR void GameMTGetTalk(U16 number,U8	*chars)
{
	switch(number)
	{
		/*case 246:		SysMemcpy(chars,"��ʿ���ǰ���������",20);break;
		case 247:		SysMemcpy(chars,"���Ƿ������������",20);break;
		case 248:		SysMemcpy(chars,"����ģ����������",20);break;
		case 249:		SysMemcpy(chars,"��ȥ�ɡ�          ",20);break;
		case 250:		SysMemcpy(chars,"�����������һ�����",20);break;
		case 251:		SysMemcpy(chars,"�ߡ�              ",20);break;
		case 252:		SysMemcpy(chars,"��ʿ��Ϊʲô������",20);break;
		case 253:		SysMemcpy(chars,"�浽�����Ƕ�ħ��  ",20);break;
		case 254:		SysMemcpy(chars,"������������Ϊ����",20);break;
		case 255:		SysMemcpy(chars,"�������Ƕ�ħ������",20);break;
		case 256:		SysMemcpy(chars,"�Ų����Ծ�������ȥ",20);break;
		case 257:		SysMemcpy(chars,"����Ҫ�����Ǹ����",20);break;
		case 258:		SysMemcpy(chars,"ħ��ɱ������ʿ��  ",20);break;
		case 259:		SysMemcpy(chars,"������ܹ����Ǹ���",20);break;
		case 260:		SysMemcpy(chars,"��ħɱ�����Ҿͺ���",20);break;
		case 261:		SysMemcpy(chars,"һ���ȥ��        ",20);break;
		case 262:		SysMemcpy(chars,"��ʿ�����ħ������",20);break;
		case 263:		SysMemcpy(chars,"��ɱ����һ��ħ����",20);break;
		case 264:		SysMemcpy(chars,"                  ",20);break;
		case 265:		SysMemcpy(chars,"���������ħ������",20);break;
		case 266:		SysMemcpy(chars,"������㣬��ɱ��",20);break;
		case 267:		SysMemcpy(chars,"�Ŀ�����һ��С�ӳ�",20);break;
		case 268:		SysMemcpy(chars,"֮��Ķ�ħ��      ",20);break;
		case 269:		SysMemcpy(chars,"��ʿ���ã��������",20);break;
		case 270:		SysMemcpy(chars,"������ɱ���Ǹ����",20);break;
		case 271:		SysMemcpy(chars,"ħ�����������㡣  ",20);break;
		case 272:		SysMemcpy(chars,"���������ħ�����",20);break;
		case 273:		SysMemcpy(chars,"��ɱ�����Ǹ�������",20);break;
		case 274:		SysMemcpy(chars,"�ˣ��������������",20);break;
		case 275:		SysMemcpy(chars,"���������ħ����",20);break;
		case 276:		SysMemcpy(chars,"�Ĺ������ͷ�����  ",20);break;
		case 277:		SysMemcpy(chars,"��������һ�����ϣ�",20);break;
		case 278:		SysMemcpy(chars,"��ҪС�ģ���һ��Ҫ",20);break;
		case 279:		SysMemcpy(chars,"ɱ����ħ����      ",20);break;
		case 280:		SysMemcpy(chars,"��������ɱ����ħ��",20);break;
		case 281:		SysMemcpy(chars,"����            ",20);break;
		case 282:		SysMemcpy(chars,"��ʿ��������û��ɱ",20);break;
		case 283:		SysMemcpy(chars,"����              ",20);break;
		case 284:		SysMemcpy(chars,"��ʿ����ħ�������",20);break;
		case 285:		SysMemcpy(chars,"���ڵ��ˡ�        ",20);break;
		case 286:		SysMemcpy(chars,"ڤ��ħ������������",20);break;
		case 287:		SysMemcpy(chars,"��Ҳ��������˼����",20);break;
		case 288:		SysMemcpy(chars,"��Ϊ��Ů����������",20);break;
		case 289:		SysMemcpy(chars,"�Ϳ��Դ���ң����",20);break;
		case 290:		SysMemcpy(chars,"�����㻹�����ء�  ",20);break;
		case 291:		SysMemcpy(chars,"��ʿ���ϻ���˵��ȥ",20);break;
		case 292:		SysMemcpy(chars,"���ɡ�            ",20);break;
		case 293:		SysMemcpy(chars,"ڤ��ħ������������",20);break;
		case 294:		SysMemcpy(chars,"���������ӣ��б���",20);break;
		case 295:		SysMemcpy(chars,"�Ļ������ڶ�ʮһ��",20);break;
		case 296:		SysMemcpy(chars,"���������Ϳ���",20);break;
		case 297:		SysMemcpy(chars,"������������ʵ    ",20);break;
		case 298:		SysMemcpy(chars,"���ˡ���Ҫ�ȵĹ���",20);break;
		case 299:		SysMemcpy(chars,"�����������ġ�  ",20);break;
		case 300:		SysMemcpy(chars,"����(Զ������)����",20);break;
		case 301:		SysMemcpy(chars,"����������        ",20);break;
		case 302:		SysMemcpy(chars,"���������������ˣ�",20);break;
		case 303:		SysMemcpy(chars,"��ɱ�����ħ�ˡ�  ",20);break;
		case 304:		SysMemcpy(chars,"��ʿ���ã���������",20);break;
		case 305:		SysMemcpy(chars,"���š�            ",20);break;
		case 306:		SysMemcpy(chars,"��ʿ���ܿˣ������",20);break;
		case 307:		SysMemcpy(chars,"���Ҵ��Ա�������",20);break;
		case 308:		SysMemcpy(chars,"������          ",20);break;
		case 309:		SysMemcpy(chars,"�ܿˣ�����������",20);break;
		case 310:		SysMemcpy(chars,"�ԱߵĶ�ħ�⿪����",20);break;
		case 311:		SysMemcpy(chars,"�ϵĶ�������Ҿ�",20);break;
		case 312:		SysMemcpy(chars,"���԰�����š�  ",20);break;
		case 313:		SysMemcpy(chars,"��ʿ���ã����һ��",20);break;
		case 314:		SysMemcpy(chars,"��                ",20);break;
		case 315:		SysMemcpy(chars,"��ʿ����ħ��������",20);break;
		case 316:		SysMemcpy(chars,"�ˡ�              ",20);break;
		case 317:		SysMemcpy(chars,"ڤ��ħ�����ã�����",20);break;
		case 318:		SysMemcpy(chars,"���������������",20);break;
		case 319:		SysMemcpy(chars,"���򵥡�          ",20);break;
		case 320:		SysMemcpy(chars,"��ʿ������Ҫ�����",20);break;
		case 321:		SysMemcpy(chars,"�����»�����С��һ",20);break;
		case 322:		SysMemcpy(chars,"����              ",20);break;
		case 323:		SysMemcpy(chars,"ڤ��ħ�����Һ���Щ",20);break;
		case 324:		SysMemcpy(chars,"�һﲻһ����      ",20);break;
		case 325:		SysMemcpy(chars,"��ʿ���ǽܿ�����ô",20);break;
		case 326:		SysMemcpy(chars,"���£�            ",20);break;
		case 327:		SysMemcpy(chars,"ڤ��ħ���������ҽ�",20);break;
		case 328:		SysMemcpy(chars,"�鷨ʦ�ŵĶ�������",20);break;
		case 329:		SysMemcpy(chars,"��                ",20);break;
		case 330:		SysMemcpy(chars,"��ʿ������鷨ʦ��",20);break;
		case 331:		SysMemcpy(chars,"�����          ",20);break;
		case 332:		SysMemcpy(chars,"ڤ��ħ�������ź���",20);break;
		case 333:		SysMemcpy(chars,"�����鷨ʦ�ղŶ���",20);break;
		case 334:		SysMemcpy(chars,"������ˡ�        ",20);break;
		case 335:		SysMemcpy(chars,"��ʿ���������Խ⿪",20);break;
		case 336:		SysMemcpy(chars,"���            ",20);break;
		case 337:		SysMemcpy(chars,"ڤ��ħ���������֮",20);break;
		case 338:		SysMemcpy(chars,"���Զ��⿪��      ",20);break;
		case 339:		SysMemcpy(chars,"ڤ��ħ����������ô",20);break;
		case 340:		SysMemcpy(chars,"���ܣ�����ô���ܻ�",20);break;
		case 341:		SysMemcpy(chars,"�������أ�������",20);break;
		case 342:		SysMemcpy(chars,"Ҫ������          ",20);break;*/
		case 343:		SysMemcpy(chars,"��ʿ�������ھ�Ҫ��",20);break;
		case 344:		SysMemcpy(chars,"�߹������㲻����ֹ",20);break;
		case 345:		SysMemcpy(chars,"���˰ɣ�          ",20);break;
		case 346:		SysMemcpy(chars,"ڤ��ħ������������",20);break;
		case 347:		SysMemcpy(chars,"���������ڴ��߹���",20);break;
		case 348:		SysMemcpy(chars,"Ҳ�������ˣ���Ϊ��",20);break;
		case 349:		SysMemcpy(chars,"ʹ����ħ����������",20);break;
		case 350:		SysMemcpy(chars,"����90��͵��ˣ�  ",20);break;
		case 351:		SysMemcpy(chars,"�������ˡ�        ",20);break;
		case 352:		SysMemcpy(chars,"��ʿ��������������",20);break;
		case 353:		SysMemcpy(chars,"�ɡ�              ",20);break;
		case 354:		SysMemcpy(chars,"�������ã����߰ɡ�",20);break;
		case 355:		SysMemcpy(chars,"                  ",20);break;
		case 356:		SysMemcpy(chars,"��ʿ���ܿˣ����߰�",20);break;
		case 357:		SysMemcpy(chars,"��                ",20);break;
		case 358:		SysMemcpy(chars,"�ܿˣ��ã���ȥ����",20);break;
		case 359:		SysMemcpy(chars,"��                ",20);break;
		case 360:		SysMemcpy(chars,"�ܿˣ�����ң���ȥ",20);break;
		case 361:		SysMemcpy(chars,"�ȹ�����          ",20);break;
		case 362:		SysMemcpy(chars,"����<��֮����>����",20);break;
		case 363:		SysMemcpy(chars,"�ˣ���ô�죿      ",20);break;
		case 364:		SysMemcpy(chars,"û��ʱ���ˣ����߰�",20);break;
		case 365:		SysMemcpy(chars,"��                ",20);break;
		case 366:		SysMemcpy(chars,"��ħͷ������ˣ���",20);break;
		case 367:		SysMemcpy(chars,"��Ҳ���ȳ���������",20);break;
		case 368:		SysMemcpy(chars,"����Ů�����Ļָ���",20);break;
		case 369:		SysMemcpy(chars,"ħ�������ˣ�ħ��Ҳ",20);break;
		case 370:		SysMemcpy(chars,"û�е�������ʿ��  ",20);break;
		case 371:		SysMemcpy(chars,"����һ���߳�������",20);break;
		case 372:		SysMemcpy(chars,"ʱ�򣬹���Ҳ���ž�",20);break;
		case 373:		SysMemcpy(chars,"�������˵��⡣һ��",20);break;
		case 374:		SysMemcpy(chars,"������ô��ƽ����  ",20);break;
		case 375:		SysMemcpy(chars,"�ع��󣬹���Ϊ��ʿ",20);break;
		case 376:		SysMemcpy(chars,"�͹���������¡�ض�",20);break;
		case 377:		SysMemcpy(chars,"ʢ��Ļ��񣬲�����",20);break;
		case 378:		SysMemcpy(chars,"������ʿ�̳й�����",20);break;
		case 379:		SysMemcpy(chars,"λ�á�            ",20);break;
		case 380:		SysMemcpy(chars,"�Ӵ��Ժ���ʿ�͹�",20);break;
		case 381:		SysMemcpy(chars,"�����Ҹ���������һ",20);break;
		case 382:		SysMemcpy(chars,"���ˡ�            ",20);break;
		case 383:		SysMemcpy(chars,"ͻȻ������һ�����",20);break;
		case 384:		SysMemcpy(chars,"��ħ�����ˣ���ʿ��",20);break;
		case 385:		SysMemcpy(chars,"����ȴû���ӳ�����",20);break;
		case 386:		SysMemcpy(chars,"��                ",20);break;
		case 387:		SysMemcpy(chars,"��ʿ��������������",20);break;
		case 388:		SysMemcpy(chars,"��                ",20);break;
		case 389:		SysMemcpy(chars,"{�õ�����Կ�׸�һ ",20);break;
		case 390:		SysMemcpy(chars,"��}               ",20);break;
		case 391:		SysMemcpy(chars,"{�õ�<����Կ��>�� ",20);break;
		case 392:		SysMemcpy(chars,"���Դ�������}   ",20);break;
		case 393:		SysMemcpy(chars,"{�õ�<һ��Կ��>�� ",20);break;
		case 394:		SysMemcpy(chars,"���Դ�һ����}   ",20);break;
		case 395:		SysMemcpy(chars,"{�õ�<��潣>��   ",20);break;
		case 396:		SysMemcpy(chars,"���� + 70}        ",20);break;
		case 397:		SysMemcpy(chars,"{�õ�<�ƽ��>��   ",20);break;
		case 398:		SysMemcpy(chars,"���� + 85}        ",20);break;
		case 399:		SysMemcpy(chars,"{�õ�<С����>��   ",20);break;
		case 400:		SysMemcpy(chars,"�ȼ�����һ����}   ",20);break;
		case 401:		SysMemcpy(chars,"{�õ�<����>��   ",20);break;
		case 402:		SysMemcpy(chars,"��� + 300}       ",20);break;
		case 403:		SysMemcpy(chars,"{�õ�<����ʮ�ּ�> ",20);break;
		case 404:		SysMemcpy(chars,"����������Ů������",20);break;
		case 405:		SysMemcpy(chars,"�����������������",20);break;
		case 406:		SysMemcpy(chars,"��һЩ������������",20);break;
		case 407:		SysMemcpy(chars,"������������}     ",20);break;
		case 408:		SysMemcpy(chars,"{�õ�<�ֽ�>�� ����",20);break;
		case 409:		SysMemcpy(chars,"+ 50}             ",20);break;
		case 410:		SysMemcpy(chars,"{�õ�<�ֶ�>�� ����",20);break;
		case 411:		SysMemcpy(chars,"+ 30}             ",20);break;
		case 412:		SysMemcpy(chars,"{�õ�<�ǹ�����>�� ",20);break;
		case 413:		SysMemcpy(chars,"�����������Ĳ�Ľ�",20);break;
		case 414:		SysMemcpy(chars,"�ˣ��ܿ˻�������",20);break;
		case 415:		SysMemcpy(chars,"��ʮ�˲�����ص���",20);break;
		case 416:		SysMemcpy(chars,"��}               ",20);break;
		case 417:		SysMemcpy(chars,"{�õ�<�����>��   ",20);break;
		case 418:		SysMemcpy(chars,"�ȼ�����������}   ",20);break;
		case 419:		SysMemcpy(chars,"{�õ�<ʥˮƿ>��   ",20);break;
		case 420:		SysMemcpy(chars,"���Խ������������",20);break;
		case 421:		SysMemcpy(chars,"һ��(�����ӱ�)��} ",20);break;
		case 422:		SysMemcpy(chars,"                  ",20);break;
		case 423:		SysMemcpy(chars,"{�õ�<ʥ�⽣>��   ",20);break;
		case 424:		SysMemcpy(chars,"���� + 120}       ",20);break;
		case 425:		SysMemcpy(chars,"{�õ�<ʥ���>��   ",20);break;
		case 426:		SysMemcpy(chars,"���� + 120}       ",20);break;
		case 427:		SysMemcpy(chars,"{�õ�<�ǹ���>�� ",20);break;
		case 428:		SysMemcpy(chars,"���� + 150}       ",20);break;
		case 429:		SysMemcpy(chars,"{�õ�<��â���>�� ",20);break;
		case 430:		SysMemcpy(chars,"���� + 190    }   ",20);break;
		case 431:		SysMemcpy(chars,"{�õ�<��֮����>�� ",20);break;
		case 432:		SysMemcpy(chars,"�ñ��������������",20);break;
		case 433:		SysMemcpy(chars,"���߹���¥�������",20);break;
		case 434:		SysMemcpy(chars,"���£����¼����ϵ�",20);break;
		case 435:		SysMemcpy(chars,"[����]�Ϳ���ʹ��  ",20);break;
		case 436:		SysMemcpy(chars,"{�õ�<ʥ���>}��  ",20);break;
		case 437:		SysMemcpy(chars,"�ñ�����Բ鿴��ǰ",20);break;
		case 438:		SysMemcpy(chars,"����Ļ����������",20);break;
		case 439:		SysMemcpy(chars,"�¼����ϵ�[����]��",20);break;
		case 440:		SysMemcpy(chars,"���Խ��в鿴��    ",20);break;
		case 441:		SysMemcpy(chars,"������Ϊ������̫��",20);break;
		case 442:		SysMemcpy(chars,"���ܾ�ս����      ",20);break;
		case 443:		SysMemcpy(chars,"������Ϊ������̫��",20);break;
		case 444:		SysMemcpy(chars,"���ܾ�ս����      ",20);break;
		case 445:		SysMemcpy(chars,"{�õ�<����Կ��>�� ",20);break;
		case 446:		SysMemcpy(chars,"���Դ򿪶�����}   ",20);break;
		case 447:		SysMemcpy(chars,"��ã�Ӣ�۵����࣬",20);break;
		case 448:		SysMemcpy(chars,"ֻҪ�����㹻�ľ���",20);break;
		case 449:		SysMemcpy(chars,"���ҾͿ���������",20);break;
		case 450:		SysMemcpy(chars,"��ǿ��          ",20);break;
		case 451:		SysMemcpy(chars,"����һ��(��100��) ",20);break;
		case 452:		SysMemcpy(chars,"���ӹ���5(��30��) ",20);break;
		case 453:		SysMemcpy(chars,"���ӷ���5(��30��) ",20);break;
		case 454:		SysMemcpy(chars,"     ��  ��       ",20);break;
		case 455:		SysMemcpy(chars,"��������(��270��) ",20);break;
		case 456:		SysMemcpy(chars,"���ӹ���17(��95��)",20);break;
		case 457:		SysMemcpy(chars,"���ӷ���17(��95��)",20);break;
		case 458:		SysMemcpy(chars,"������һ���������",20);break;
		case 459:		SysMemcpy(chars,"��Ҫ��ֻҪ���н��",20);break;
		case 460:		SysMemcpy(chars,"���ҾͿ��԰��㣺  ",20);break;
		case 461:		SysMemcpy(chars,"����1��Կ��($10)  ",20);break;
		case 462:		SysMemcpy(chars,"����2��Կ��($50)  ",20);break;
		case 463:		SysMemcpy(chars,"����3��Կ��($100) ",20);break;
		case 464:		SysMemcpy(chars,"������һ���������",20);break;
		case 465:		SysMemcpy(chars,"��Ҫ��ֻҪ����Կ��",20);break;
		case 466:		SysMemcpy(chars,"���ҾͿ��԰��㣺  ",20);break;
		case 467:		SysMemcpy(chars,"����1��Կ��($7)   ",20);break;
		case 468:		SysMemcpy(chars,"����2��Կ��($35)  ",20);break;
		case 469:		SysMemcpy(chars,"����3��Կ��($70)  ",20);break;
		case 470:		SysMemcpy(chars,"���������������",20);break;
		case 471:		SysMemcpy(chars,"�������25����ң�",20);break;
		case 472:		SysMemcpy(chars,"���������ѡһ�",20);break;
		case 473:		SysMemcpy(chars,"   ����800������  ",20);break;
		case 474:		SysMemcpy(chars,"   ����4�㹥��    ",20);break;
		case 475:		SysMemcpy(chars,"   ����4�����    ",20);break;
		case 476:		SysMemcpy(chars,"��Ҫ�������������",20);break;
		case 477:		SysMemcpy(chars,"��������� 100����",20);break;
		case 478:		SysMemcpy(chars,"�ң����������ѡһ",20);break;
		case 479:		SysMemcpy(chars,"�              ",20);break;
		case 480:		SysMemcpy(chars,"  ����4000������  ",20);break;
		case 481:		SysMemcpy(chars,"  ����20�㹥��    ",20);break;
		case 482:		SysMemcpy(chars,"  ����20�����    ",20);break;
		case 483:		SysMemcpy(chars,"{�õ�<����>�� ����",20);break;
		case 484:		SysMemcpy(chars,"+ 10}             ",20);break;
		case 485:		SysMemcpy(chars,"{�õ�<����>�� ����",20);break;
		case 486:		SysMemcpy(chars,"+ 10}             ",20);break;	
		case 487:		SysMemcpy(chars,"�����Ŷӣ�        ",20);break;
		case 488:		SysMemcpy(chars,"   ���пƼ���ѧ   ",20);break;
		case 489:		SysMemcpy(chars,"    �����Э��    ",20);break;
		case 490:		SysMemcpy(chars,"������ƣ�        ",20);break;
		case 491:		SysMemcpy(chars,"�޲���(SavageKing)",20);break;
		case 492:		SysMemcpy(chars,"�߻���            ",20);break;
		case 493:		SysMemcpy(chars,"      ���ຣ      ",20);break;
		case 494:		SysMemcpy(chars,"��ѽ����֮������ô",20);break;
		case 495:		SysMemcpy(chars,"�����ˣ�          ",20);break;
	}
}

/***********************************************************************
 * ������:	GameMTGetMapData()
 * ˵��:		����ͼ����װ���ڴ�
 * �������:	�� 
 * ����ֵ  :	��
 * �޸���ʷ:
 *              ����              ����             ˵��
 *             ------          ----------      -------------
 *             �޲���           2005.1.25        ��ɻ�������
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