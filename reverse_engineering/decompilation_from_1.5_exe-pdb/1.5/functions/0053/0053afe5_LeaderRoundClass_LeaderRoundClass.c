/*
 * Entry: 0053afe5
 * Name: LeaderRoundClass::LeaderRoundClass
 * Namespace: LeaderRoundClass
 * Signature: LeaderRoundClass * LeaderRoundClass(LeaderRoundClass * this, LeaderRoundClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LeaderRoundClass * __thiscall
LeaderRoundClass::LeaderRoundClass(LeaderRoundClass *this,LeaderRoundClass *param_1,long64 param_2)

{
  LeaderRoundClass *pLVar1;
  undefined4 unaff_EDI;
  
  pLVar1 = param_1;
  RocketClass::RocketClass
            ((RocketClass *)this,(RocketClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x4d75381c,0x43d9e250,&this->homingTime,
                   pLVar1->homingTime);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
