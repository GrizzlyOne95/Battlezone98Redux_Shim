/*
 * Entry: 0047e59c
 * Name: APCClass::APCClass
 * Namespace: APCClass
 * Signature: APCClass * APCClass(APCClass * this, APCClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

APCClass * __thiscall APCClass::APCClass(APCClass *this,APCClass *param_1,long64 param_2)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  GameObjectClass *pGVar4;
  uint unaff_ESI;
  undefined4 unaff_EDI;
  int local_24;
  int local_20;
  ParameterDB local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  HoverCraftClass::HoverCraftClass
            ((HoverCraftClass *)this,(HoverCraftClass *)param_1,
             CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB(&local_1c,(char *)&this->_padding_);
  ParameterDB::Get(&local_1c,0x6b75762f,0x9fa4327,(float *)&this->soldierClass,
                   (float)param_1->soldierClass);
  ParameterDB::Get(&local_1c,0x6b75762f,0x74c3a47c,(float *)&this->soldierCount,
                   (float)param_1->soldierCount);
  ParameterDB::Get(&local_1c,0x6b75762f,0x1ee0b4c4,(long *)&this->reloadRange,
                   (long)param_1->reloadRange);
  ParameterDB::Get(&local_1c,0x6b75762f,0xe28bf4c8,&this->reloadDelay,param_1->reloadDelay);
  ParameterDB::Get(&local_1c,0x6b75762f,0x9c6f5edd,(long64 *)&local_24,(ulonglong)unaff_ESI << 0x20)
  ;
  if (local_24 == 0 && local_20 == 0) {
    this->soldierDelay = 0.0;
    goto LAB_0047e6e1;
  }
  sprintf(local_18,"%.8s.odf",&local_24);
  if (((char)local_24 == 'a') || ((char)local_24 == 's')) {
LAB_0047e6a1:
    iVar3 = ItemExists(local_18);
    if (iVar3 == 0) goto LAB_0047e6af;
  }
  else {
    bVar2 = Net::IsNetGame();
    if ((!bVar2) || (Net::bNations != false)) goto LAB_0047e6a1;
LAB_0047e6af:
    cVar1 = (char)this->_padding_;
    if ((cVar1 == 'c') || (local_24 = CONCAT31(local_24._1_3_,0x61), cVar1 == 's')) {
      local_24 = CONCAT31(local_24._1_3_,0x73);
    }
  }
  pGVar4 = GameObjectClass::Find(CONCAT44(local_20,local_24));
  this->soldierDelay = (float)pGVar4;
LAB_0047e6e1:
  ParameterDB::Get(&local_1c,0x6b75762f,0x1d0683f1,&this->reloadReset,param_1->reloadReset);
  ParameterDB::Get(&local_1c,0x6b75762f,0x282bd2cb,(float *)(this + 1),(float)param_1[1]._padding_);
  ParameterDB::Get(&local_1c,0x6b75762f,0xcafc923b,(float *)&this[1]._padding_,
                   (float)param_1[1]._padding_);
  ParameterDB::~ParameterDB(&local_1c);
  return this;
}
