/*
 * Entry: 00539ba8
 * Name: SniperShellClass::SniperShellClass
 * Namespace: SniperShellClass
 * Signature: SniperShellClass * SniperShellClass(SniperShellClass * this, SniperShellClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SniperShellClass * __thiscall
SniperShellClass::SniperShellClass(SniperShellClass *this,SniperShellClass *param_1,long64 param_2)

{
  float *pfVar1;
  undefined4 unaff_EDI;
  
  BulletClass::BulletClass
            ((BulletClass *)this,(BulletClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_2,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_2,0x40400f60,0x935b6321,&this->killLength,
                   param_1->killLength);
  pfVar1 = &this->killRadius;
  ParameterDB::Get((ParameterDB *)&param_2,0x40400f60,0x6981c907,pfVar1,param_1->killRadius);
  if (0.5 < *pfVar1) {
    *pfVar1 = 0.5;
  }
  if (10.0 < this->killLength) {
    this->killLength = 10.0;
  }
  ParameterDB::~ParameterDB((ParameterDB *)&param_2);
  return this;
}
