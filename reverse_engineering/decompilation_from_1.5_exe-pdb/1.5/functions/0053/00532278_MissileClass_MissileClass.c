/*
 * Entry: 00532278
 * Name: MissileClass::MissileClass
 * Namespace: MissileClass
 * Signature: MissileClass * MissileClass(MissileClass * this, MissileClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MissileClass * __thiscall
MissileClass::MissileClass(MissileClass *this,MissileClass *param_1,long64 param_2)

{
  float *pfVar1;
  undefined4 unaff_EDI;
  
  RocketClass::RocketClass
            ((RocketClass *)this,(RocketClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_2,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_2,0x77aa7cd5,0x4ad4b447,&this->omegaTurn,param_1->omegaTurn
                  );
  pfVar1 = &this->shotAccel;
  ParameterDB::Get((ParameterDB *)&param_2,0x77aa7cd5,0x21601063,pfVar1,param_1->shotAccel);
  *pfVar1 = *pfVar1 / (float)this->_padding_;
  ParameterDB::~ParameterDB((ParameterDB *)&param_2);
  return this;
}
