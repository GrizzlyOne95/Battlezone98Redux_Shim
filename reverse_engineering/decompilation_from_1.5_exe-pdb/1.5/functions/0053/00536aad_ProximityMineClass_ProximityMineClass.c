/*
 * Entry: 00536aad
 * Name: ProximityMineClass::ProximityMineClass
 * Namespace: ProximityMineClass
 * Signature: ProximityMineClass * ProximityMineClass(ProximityMineClass * this, ProximityMineClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ProximityMineClass * __thiscall
ProximityMineClass::ProximityMineClass
          (ProximityMineClass *this,ProximityMineClass *param_1,long64 param_2)

{
  ProximityMineClass *pPVar1;
  ExplosionClass *pEVar2;
  uint unaff_ESI;
  undefined4 unaff_EDI;
  int in_stack_00000008;
  
  pPVar1 = param_1;
  MineClass::MineClass((MineClass *)this,(MineClass *)param_1,CONCAT44(unaff_EDI,(int)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0xecd6fb3,0xe3635ff7,&this->searchRadius,
                   pPVar1->searchRadius);
  ParameterDB::Get((ParameterDB *)&param_1,0xecd6fb3,0x73a2de0,&this->searchPeriod,
                   pPVar1->searchPeriod);
  ParameterDB::Get((ParameterDB *)&param_1,0xecd6fb3,0xd61bc22b,(long64 *)&stack0x00000008,
                   (ulonglong)unaff_ESI << 0x20);
  if (in_stack_00000008 == 0 && (int)param_2 == 0) {
    pEVar2 = pPVar1->xplClass;
  }
  else {
    pEVar2 = ExplosionClass::Find(CONCAT44((int)param_2,in_stack_00000008));
  }
  this->xplClass = pEVar2;
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
