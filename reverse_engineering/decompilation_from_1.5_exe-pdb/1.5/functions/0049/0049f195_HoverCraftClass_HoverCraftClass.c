/*
 * Entry: 0049f195
 * Name: HoverCraftClass::HoverCraftClass
 * Namespace: HoverCraftClass
 * Signature: HoverCraftClass * HoverCraftClass(HoverCraftClass * this, HoverCraftClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HoverCraftClass * __thiscall
HoverCraftClass::HoverCraftClass(HoverCraftClass *this,HoverCraftClass *param_1,long64 param_2)

{
  HoverCraftClass *pHVar1;
  undefined4 unaff_EDI;
  
  pHVar1 = param_1;
  CraftClass::CraftClass
            ((CraftClass *)this,(CraftClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0x4f358485,&this->setAltitude,
                   pHVar1->setAltitude);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0x6b8ecf11,&this->accelDragStop,
                   pHVar1->accelDragStop);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0x8ec6e538,&this->accelDragFull,
                   pHVar1->accelDragFull);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0xaa814a2c,&this->alphaTrack,
                   pHVar1->alphaTrack);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0x473d5031,&this->pitchPitch,
                   pHVar1->pitchPitch);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0xb8add2a,&this->alphaDamp,pHVar1->alphaDamp);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0xdd47602d,&this->pitchThrust,
                   pHVar1->pitchThrust);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0xb09a0677,&this->rollStrafe,
                   pHVar1->rollStrafe);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0x4b7eca45,&this->rollSteer,pHVar1->rollSteer)
  ;
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0x169afba3,this->rollStrafRotator,
                   pHVar1->rollStrafRotator[0]);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0x9410fcff,&this->velocForward,
                   pHVar1->velocForward);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0x2a47387c,&this->velocReverse,
                   pHVar1->velocReverse);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0x1462ec61,&this->velocStrafe,
                   pHVar1->velocStrafe);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0xe94c7c19,&this->accelThrust,
                   pHVar1->accelThrust);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0x13dfdbf6,&this->accelBrake,
                   pHVar1->accelBrake);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0x73accd30,&this->omegaSpin,pHVar1->omegaSpin)
  ;
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0x4ad4b447,&this->omegaTurn,pHVar1->omegaTurn)
  ;
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0x19b84820,&this->alphaSteer,
                   pHVar1->alphaSteer);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0xd4247e4f,&this->accelJump,pHVar1->accelJump)
  ;
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0xd79059b4,this->rollStrafRotator + 1,
                   pHVar1->rollStrafRotator[1]);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0x1d0e24af,this->rollSteerFin,
                   pHVar1->rollSteerFin[0]);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0xfda2e861,this->rollSteerFin + 1,
                   pHVar1->rollSteerFin[1]);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0xd7dbcc30,this->pitchThrotNacelle,
                   pHVar1->pitchThrotNacelle[0]);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0x23237367,this->pitchThrotNacelle + 1,
                   pHVar1->pitchThrotNacelle[1]);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0x12ffdb56,this->pitchSteerNacelle,
                   pHVar1->pitchSteerNacelle[0]);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0x7b5dc653,this->pitchSteerNacelle + 1,
                   pHVar1->pitchSteerNacelle[1]);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0x6f33e86a,(float *)this->soundThrust,
                   *(float *)pHVar1->soundThrust);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0x48b2e796,this->soundThrust + 4,0x10,
                   pHVar1->soundThrust + 4);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0x30e300b0,this->soundTurbo + 4,0x10,
                   pHVar1->soundTurbo + 4);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0xf15a9d35,this->soundFly + 4,0x10,
                   pHVar1->soundFly + 4);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0xec9b4117,this->soundDeploy + 4,0x10,
                   pHVar1->soundDeploy + 4);
  ParameterDB::Get((ParameterDB *)&param_1,0xc9835423,0xf17a53cc,this->soundUndeploy + 4,0x10,
                   pHVar1->soundUndeploy + 4);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
