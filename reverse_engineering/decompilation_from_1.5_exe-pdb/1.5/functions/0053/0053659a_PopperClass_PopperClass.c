/*
 * Entry: 0053659a
 * Name: PopperClass::PopperClass
 * Namespace: PopperClass
 * Signature: PopperClass * PopperClass(PopperClass * this, PopperClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PopperClass * __thiscall
PopperClass::PopperClass(PopperClass *this,PopperClass *param_1,long64 param_2)

{
  PopperClass *pPVar1;
  ExplosionClass *pEVar2;
  OrdnanceClass *pOVar3;
  uint unaff_EBX;
  uint unaff_ESI;
  undefined4 unaff_EDI;
  int in_stack_00000008;
  
  pPVar1 = param_1;
  GrenadeClass::GrenadeClass
            ((GrenadeClass *)this,(GrenadeClass *)param_1,CONCAT44(unaff_EDI,(int)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x25bbee79,0x6a1b2cdd,&this->scanRange,pPVar1->scanRange)
  ;
  ParameterDB::Get((ParameterDB *)&param_1,0x25bbee79,0x43506756,(long64 *)&stack0x00000008,
                   (ulonglong)unaff_ESI << 0x20);
  if (in_stack_00000008 == 0 && (int)param_2 == 0) {
    pEVar2 = pPVar1->launchXpl;
  }
  else {
    pEVar2 = ExplosionClass::Find(CONCAT44((int)param_2,in_stack_00000008));
  }
  this->launchXpl = pEVar2;
  ParameterDB::Get((ParameterDB *)&param_1,0x25bbee79,0x5eaf51ed,(long64 *)&stack0x00000008,
                   (ulonglong)unaff_EBX << 0x20);
  if (in_stack_00000008 == 0 && (int)param_2 == 0) {
    pOVar3 = pPVar1->launchOrd;
  }
  else {
    pOVar3 = OrdnanceClass::Find(CONCAT44((int)param_2,in_stack_00000008));
  }
  this->launchOrd = pOVar3;
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
