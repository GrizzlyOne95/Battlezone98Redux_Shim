/*
 * Entry: 005370b1
 * Name: QuakeBlastClass::QuakeBlastClass
 * Namespace: QuakeBlastClass
 * Signature: QuakeBlastClass * QuakeBlastClass(QuakeBlastClass * this, QuakeBlastClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

QuakeBlastClass * __thiscall
QuakeBlastClass::QuakeBlastClass(QuakeBlastClass *this,QuakeBlastClass *param_1,long64 param_2)

{
  QuakeBlastClass *pQVar1;
  OrdnanceClass *pOVar2;
  uint unaff_ESI;
  undefined4 unaff_EDI;
  int in_stack_00000008;
  
  pQVar1 = param_1;
  ExplosionClass::ExplosionClass
            ((ExplosionClass *)this,(ExplosionClass *)param_1,CONCAT44(unaff_EDI,(int)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x8630865c,0x46b7241d,&this->quakeCount,
                   pQVar1->quakeCount);
  ParameterDB::Get((ParameterDB *)&param_1,0x8630865c,0x3bc0709e,(long64 *)&stack0x00000008,
                   (ulonglong)unaff_ESI << 0x20);
  if (in_stack_00000008 == 0 && (int)param_2 == 0) {
    pOVar2 = pQVar1->quakeClass;
  }
  else {
    pOVar2 = OrdnanceClass::Find(CONCAT44((int)param_2,in_stack_00000008));
  }
  this->quakeClass = pOVar2;
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
