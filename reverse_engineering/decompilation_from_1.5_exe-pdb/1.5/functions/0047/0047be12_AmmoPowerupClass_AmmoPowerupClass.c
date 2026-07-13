/*
 * Entry: 0047be12
 * Name: AmmoPowerupClass::AmmoPowerupClass
 * Namespace: AmmoPowerupClass
 * Signature: AmmoPowerupClass * AmmoPowerupClass(AmmoPowerupClass * this, AmmoPowerupClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AmmoPowerupClass * __thiscall
AmmoPowerupClass::AmmoPowerupClass(AmmoPowerupClass *this,AmmoPowerupClass *param_1,long64 param_2)

{
  AmmoPowerupClass *pAVar1;
  undefined4 unaff_EDI;
  
  pAVar1 = param_1;
  PowerUpClass::PowerUpClass
            ((PowerUpClass *)this,(PowerUpClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x6222caa7,0x1ee6ddfa,&this->ammoUp,pAVar1->ammoUp);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
