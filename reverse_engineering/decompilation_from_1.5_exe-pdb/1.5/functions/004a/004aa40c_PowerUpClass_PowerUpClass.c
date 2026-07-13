/*
 * Entry: 004aa40c
 * Name: PowerUpClass::PowerUpClass
 * Namespace: PowerUpClass
 * Signature: PowerUpClass * PowerUpClass(PowerUpClass * this, PowerUpClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PowerUpClass * __thiscall
PowerUpClass::PowerUpClass(PowerUpClass *this,PowerUpClass *param_1,long64 param_2)

{
  PowerUpClass *pPVar1;
  undefined4 unaff_EDI;
  
  pPVar1 = param_1;
  GameObjectClass::GameObjectClass
            ((GameObjectClass *)this,(GameObjectClass *)param_1,
             CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x94ed882d,0xc7620108,this->soundPickup,0x10,
                   pPVar1->soundPickup);
  ParameterDB::Get((ParameterDB *)&param_1,0x94ed882d,0xf8742e8f,this->soundReject,0x10,
                   pPVar1->soundReject);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
