/*
 * Entry: 004aca71
 * Name: ProducerClass::ProducerClass
 * Namespace: ProducerClass
 * Signature: ProducerClass * ProducerClass(ProducerClass * this, ProducerClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ProducerClass * __thiscall
ProducerClass::ProducerClass(ProducerClass *this,ProducerClass *param_1,long64 param_2)

{
  char cVar1;
  ProducerClass *pPVar2;
  bool bVar3;
  GameObjectClass *pGVar4;
  GameObjectClass **ppGVar5;
  ProducerClass *unaff_ESI;
  undefined4 unaff_EDI;
  ProducerClass *local_c;
  ProducerClass *local_8;
  
  pPVar2 = param_1;
  local_c = this;
  local_8 = this;
  HoverCraftClass::HoverCraftClass
            ((HoverCraftClass *)this,(HoverCraftClass *)param_1,CONCAT44(unaff_EDI,(int)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0xdf9ca9e9,0x9fa4327,&this->timeRepair,pPVar2->timeRepair
                  );
  ParameterDB::Get((ParameterDB *)&param_1,0xdf9ca9e9,0x74c3a47c,&this->healthRepair,
                   pPVar2->healthRepair);
  ParameterDB::Get((ParameterDB *)&param_1,0xdf9ca9e9,0xe1bad3b1,(float *)&this->scrapHold,
                   (float)pPVar2->scrapHold);
  ParameterDB::Get((ParameterDB *)&param_1,0xdf9ca9e9,0x42756986,(float *)&this->pilotHold,
                   (float)pPVar2->pilotHold);
  ParameterDB::Get((ParameterDB *)&param_1,0xdf9ca9e9,0x92a6e0eb,(long *)this->buildItem,
                   (long)pPVar2->buildItem[0]);
  ParameterDB::Get((ParameterDB *)&param_1,0xdf9ca9e9,0x8588af8c,(long *)(this->buildItem + 1),
                   (long)pPVar2->buildItem[1]);
  param_2._0_4_ = 0;
  ppGVar5 = this->buildItem + 2;
  do {
    ParameterDB::Get((ParameterDB *)&param_1,0xdf9ca9e9,
                     ((byte)((char)param_2 + 0x31) ^ 0xf1915444) * 0x1000193,(long64 *)&local_c,
                     ZEXT48(unaff_ESI) << 0x20);
    if (local_c == (ProducerClass *)0x0 && local_8 == (ProducerClass *)0x0) {
LAB_004acbcb:
      *ppGVar5 = (GameObjectClass *)0x0;
    }
    else {
      unaff_ESI = local_8;
      pGVar4 = GameObjectClass::Find(CONCAT44(local_8,local_c));
      *ppGVar5 = pGVar4;
      if (pGVar4 != (GameObjectClass *)0x0) {
        unaff_ESI = (ProducerClass *)0x4acba2;
        bVar3 = Net::IsNetGame();
        if ((bVar3) &&
           (((cVar1 = Net::bBarracks, (*ppGVar5)->sig == 0x42415252 ||
             (cVar1 = Net::bCommSat, (*ppGVar5)->sig == 0x434f4d4d)) && (cVar1 == '\0'))))
        goto LAB_004acbcb;
      }
    }
    param_2._0_4_ = (int)param_2 + 1;
    ppGVar5 = ppGVar5 + 1;
    if (8 < (int)param_2) {
      ParameterDB::Get((ParameterDB *)&param_1,0xdf9ca9e9,0x29afb604,this->soundBuild + 8,0x10,
                       (char *)0x0);
      ParameterDB::Get((ParameterDB *)&param_1,0xdf9ca9e9,0xa8198ee3,this->soundFinish + 8,0x10,
                       (char *)0x0);
      ParameterDB::Get((ParameterDB *)&param_1,0xdf9ca9e9,0xdd64817d,this->blockedGeyserMsg + 8,0x10
                       ,(char *)0x0);
      ParameterDB::~ParameterDB((ParameterDB *)&param_1);
      return this;
    }
  } while( true );
}
