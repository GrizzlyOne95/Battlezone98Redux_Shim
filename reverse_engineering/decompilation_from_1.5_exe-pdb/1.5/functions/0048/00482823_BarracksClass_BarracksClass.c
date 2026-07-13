/*
 * Entry: 00482823
 * Name: BarracksClass::BarracksClass
 * Namespace: BarracksClass
 * Signature: BarracksClass * BarracksClass(BarracksClass * this, BarracksClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

BarracksClass * __thiscall
BarracksClass::BarracksClass(BarracksClass *this,BarracksClass *param_1,long64 param_2)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  GameObjectClass *pGVar4;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  ParameterDB local_24;
  int local_20;
  int local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  BuildingClass::BuildingClass
            ((BuildingClass *)this,(BuildingClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2))
  ;
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB(&local_24,(char *)&this->_padding_);
  ParameterDB::Get(&local_24,0x66e9b4de,0x8588af8c,&this->pilotHold,param_1->pilotHold);
  local_1c = 0x6f6c;
  local_20 = CONCAT31(0x697073,(char)this->_padding_);
  ParameterDB::Get(&local_24,0x66e9b4de,0xde331a5a,(long64 *)&local_20,CONCAT44(unaff_ESI,0x6f6c));
  if (local_20 == 0 && local_1c == 0) {
    this->pilotClass = (GameObjectClass *)0x0;
    goto LAB_00482923;
  }
  sprintf(local_18,"%.8s.odf",&local_20);
  if (((char)local_20 == 'a') || ((char)local_20 == 's')) {
LAB_004828e3:
    iVar3 = ItemExists(local_18);
    if (iVar3 == 0) goto LAB_004828f1;
  }
  else {
    bVar2 = Net::IsNetGame();
    if ((!bVar2) || (Net::bNations != false)) goto LAB_004828e3;
LAB_004828f1:
    cVar1 = (char)this->_padding_;
    if ((cVar1 == 'c') || (local_20 = CONCAT31(local_20._1_3_,0x61), cVar1 == 's')) {
      local_20 = CONCAT31(local_20._1_3_,0x73);
    }
  }
  pGVar4 = GameObjectClass::Find(CONCAT44(local_1c,local_20));
  this->pilotClass = pGVar4;
LAB_00482923:
  ParameterDB::~ParameterDB(&local_24);
  return this;
}
