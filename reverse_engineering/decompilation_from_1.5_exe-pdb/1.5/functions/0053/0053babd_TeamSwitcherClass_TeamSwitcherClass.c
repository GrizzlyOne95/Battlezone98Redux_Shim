/*
 * Entry: 0053babd
 * Name: TeamSwitcherClass::TeamSwitcherClass
 * Namespace: TeamSwitcherClass
 * Signature: TeamSwitcherClass * TeamSwitcherClass(TeamSwitcherClass * this, TeamSwitcherClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TeamSwitcherClass * __thiscall
TeamSwitcherClass::TeamSwitcherClass
          (TeamSwitcherClass *this,TeamSwitcherClass *param_1,long64 param_2)

{
  TeamSwitcherClass *pTVar1;
  undefined4 unaff_EDI;
  
  pTVar1 = param_1;
  RocketClass::RocketClass
            ((RocketClass *)this,(RocketClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x2dd89c11,0x25401c88,&this->switchTime,
                   pTVar1->switchTime);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
