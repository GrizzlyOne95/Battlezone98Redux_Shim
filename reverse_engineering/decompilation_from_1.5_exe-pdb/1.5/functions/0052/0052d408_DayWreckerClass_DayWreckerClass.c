/*
 * Entry: 0052d408
 * Name: DayWreckerClass::DayWreckerClass
 * Namespace: DayWreckerClass
 * Signature: DayWreckerClass * DayWreckerClass(DayWreckerClass * this, DayWreckerClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DayWreckerClass * __thiscall
DayWreckerClass::DayWreckerClass(DayWreckerClass *this,DayWreckerClass *param_1,long64 param_2)

{
  DayWreckerClass *pDVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  ushort uVar6;
  ExplosionClass *pEVar7;
  ushort uVar8;
  uint unaff_ESI;
  undefined4 unaff_EDI;
  int local_1c;
  int local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  pDVar1 = param_1;
  PowerUpClass::PowerUpClass
            ((PowerUpClass *)this,(PowerUpClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_2,(char *)&this->_padding_);
  this->xplClass = param_1->xplClass;
  *(undefined2 *)&this->craterDepth = *(undefined2 *)&param_1->craterDepth;
  bVar2 = ParameterDB::Get((ParameterDB *)&param_2,0x2db342a,0x5be2a777,&local_8,0.0);
  bVar3 = ParameterDB::Get((ParameterDB *)&param_2,0x2db342a,0x52fd4a53,&local_10,0.0);
  bVar4 = ParameterDB::Get((ParameterDB *)&param_2,0x2db342a,0x38720d72,&local_14,0.0);
  bVar5 = ParameterDB::Get((ParameterDB *)&param_2,0x2db342a,0x7c8a1300,&local_c,0.0);
  if (bVar5 || (bVar4 || (bVar2 || bVar3))) {
    this->xplClass = (ExplosionClass *)(local_14 + local_10 + local_c + local_8);
    if (local_c == 0.0) {
      uVar8 = 0;
    }
    else {
      uVar8 = 2;
    }
    if (local_10 == 0.0) {
      param_1._0_2_ = 0;
    }
    else {
      param_1._0_2_ = 4;
    }
    if (local_14 == 0.0) {
      uVar6 = 0;
    }
    else {
      uVar6 = 8;
    }
    *(ushort *)&this->craterDepth = local_8 != 0.0 | uVar8 | (ushort)param_1 | uVar6;
  }
  ParameterDB::Get((ParameterDB *)&param_2,0x2db342a,0xd61bc22b,(long64 *)&local_1c,
                   (ulonglong)unaff_ESI << 0x20);
  if (local_1c == 0 && local_18 == 0) {
    pEVar7 = (ExplosionClass *)pDVar1[1]._padding_;
  }
  else {
    pEVar7 = ExplosionClass::Find(CONCAT44(local_18,local_1c));
  }
  this[1]._padding_ = (int)pEVar7;
  ParameterDB::Get((ParameterDB *)&param_2,0x2db342a,0x1aa6522f,(float *)&this[1]._padding_,
                   (float)pDVar1[1]._padding_);
  ParameterDB::~ParameterDB((ParameterDB *)&param_2);
  return this;
}
