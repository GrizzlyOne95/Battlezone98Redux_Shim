/*
 * Entry: 0052fc56
 * Name: FlareMineClass::FlareMineClass
 * Namespace: FlareMineClass
 * Signature: FlareMineClass * FlareMineClass(FlareMineClass * this, FlareMineClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FlareMineClass * __thiscall
FlareMineClass::FlareMineClass(FlareMineClass *this,FlareMineClass *param_1,long64 param_2)

{
  FlareMineClass *pFVar1;
  OrdnanceClass *pOVar2;
  uint unaff_ESI;
  undefined4 unaff_EDI;
  int in_stack_00000008;
  
  pFVar1 = param_1;
  MineClass::MineClass((MineClass *)this,(MineClass *)param_1,CONCAT44(unaff_EDI,(int)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x2a1e42e4,0x19d3ebc6,(long64 *)&stack0x00000008,
                   (ulonglong)unaff_ESI << 0x20);
  if (in_stack_00000008 == 0 && (int)param_2 == 0) {
    pOVar2 = pFVar1->payloadClass;
  }
  else {
    pOVar2 = OrdnanceClass::Find(CONCAT44((int)param_2,in_stack_00000008));
  }
  this->payloadClass = pOVar2;
  ParameterDB::Get((ParameterDB *)&param_1,0x2a1e42e4,0xcfde2fc0,this->fireSound,0x10,
                   pFVar1->fireSound);
  ParameterDB::Get((ParameterDB *)&param_1,0x2a1e42e4,0x682cd2b2,&this->triggerDelay,
                   pFVar1->triggerDelay);
  ParameterDB::Get((ParameterDB *)&param_1,0x2a1e42e4,0xd9356908,&this->shotDelay,pFVar1->shotDelay)
  ;
  ParameterDB::Get((ParameterDB *)&param_1,0x2a1e42e4,0x22c3372e,&this->shotVariance,
                   pFVar1->shotVariance);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
