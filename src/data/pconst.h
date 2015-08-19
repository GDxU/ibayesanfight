enum {
    /* 程序常量数据文件 */
    /* 兵种攻击范围(按兵种排序) */
    dFgtAtRange = 1,
    /* 兵种策略(按兵种排序) */
    dFgtJNArray,
    /* 各种地形对不同兵种的移动力影响 */
    dFgtLandR,
    /* 各种地形对不同兵种的战力量影响
     草地 平原 山地 森林 村庄 城池 营寨 河流 */
    dFgtLandF,
    
    /* 战斗初始化坐标 攻击方*8+防守方 */
    dFgtIntPos,
    
    /* 城市数组 */
    dCityPos,
    
    /*  */
    GOODS_PRO_WID,
    PERSON_PRO_WID,
    /*  */
    DirectP,
    /* 指令消耗体力		任 开 招 搜 治 出 招 处 流 赏 没 交 宴 输 移 离 招 策 反 劝 无 无 无 侦 征 分 掠 出 */
    ConsumeThew,
    /* 指令消耗金钱		 任  开  招  搜  治  出  招  处  流  赏  没  交  宴  输  移  离  招  策  反  劝  无  无  无  侦  征  分  掠  出 */
    ConsumeMoney,
    KingTacticOddsIH,
    KingTacticOddsD,
    C_MAP,
    dCityMapId
};