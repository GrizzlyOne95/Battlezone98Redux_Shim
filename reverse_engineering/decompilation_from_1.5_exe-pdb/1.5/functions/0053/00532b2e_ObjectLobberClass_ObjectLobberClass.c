/*
 * Entry: 00532b2e
 * Name: ObjectLobberClass::ObjectLobberClass
 * Namespace: ObjectLobberClass
 * Signature: ObjectLobberClass * ObjectLobberClass(ObjectLobberClass * this, ObjectLobberClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ObjectLobberClass * __thiscall
ObjectLobberClass::ObjectLobberClass
          (ObjectLobberClass *this,ObjectLobberClass *param_1,long64 param_2)

{
  ObjectLobberClass *pOVar1;
  undefined4 unaff_EDI;
  
  pOVar1 = param_1;
  WeaponClass::WeaponClass
            ((WeaponClass *)this,(WeaponClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x111cf854,0xd9356908,&this->shotDelay,pOVar1->shotDelay)
  ;
  ParameterDB::Get((ParameterDB *)&param_1,0x111cf854,0xcafe92d0,&this->shotSpeed,pOVar1->shotSpeed)
  ;
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
