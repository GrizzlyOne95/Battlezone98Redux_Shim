/*
 * Entry: 0052d61e
 * Name: DispenserClass::DispenserClass
 * Namespace: DispenserClass
 * Signature: DispenserClass * DispenserClass(DispenserClass * this, DispenserClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DispenserClass * __thiscall
DispenserClass::DispenserClass(DispenserClass *this,DispenserClass *param_1,long64 param_2)

{
  DispenserClass *pDVar1;
  GameObjectClass *pGVar2;
  uint unaff_ESI;
  undefined4 unaff_EDI;
  int in_stack_00000008;
  
  pDVar1 = param_1;
  WeaponClass::WeaponClass
            ((WeaponClass *)this,(WeaponClass *)param_1,CONCAT44(unaff_EDI,(int)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0xd60ea600,0xfab4528a,(long64 *)&stack0x00000008,
                   (ulonglong)unaff_ESI << 0x20);
  if (in_stack_00000008 != 0 || (int)param_2 != 0) {
    pGVar2 = GameObjectClass::Find(CONCAT44((int)param_2,in_stack_00000008));
    this->_padding_ = (int)pGVar2;
  }
  ParameterDB::Get((ParameterDB *)&param_1,0xd60ea600,0xd9356908,&this->shotDelay,pDVar1->shotDelay)
  ;
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
