/*
 * Entry: 004b8c20
 * Name: WalkerClass::WalkerClass
 * Namespace: WalkerClass
 * Signature: WalkerClass * WalkerClass(WalkerClass * this, WalkerClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WalkerClass * __thiscall
WalkerClass::WalkerClass(WalkerClass *this,WalkerClass *param_1,long64 param_2)

{
  WalkerClass *pWVar1;
  undefined4 unaff_EDI;
  
  pWVar1 = param_1;
  CraftClass::CraftClass
            ((CraftClass *)this,(CraftClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xed315e04,&this->parameters[0].alphaDamp,
                   pWVar1->parameters[0].alphaDamp);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xd2a79ef5,&this->parameters[0].alphaTrack,
                   pWVar1->parameters[0].alphaTrack);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xa1d381e8,&this->parameters[0].pitchPitch,
                   pWVar1->parameters[0].pitchPitch);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xd76b553a,&this->parameters[0].pitchThrust,
                   pWVar1->parameters[0].pitchThrust);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x88f5bc00,&this->parameters[0].rollStrafe,
                   pWVar1->parameters[0].rollStrafe);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xaf7b8b02,&this->parameters[0].velocForward,
                   pWVar1->parameters[0].velocForward);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x5d02411f,&this->parameters[0].velocReverse,
                   pWVar1->parameters[0].velocReverse);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x3cf570d4,&this->parameters[0].velocStrafe,
                   pWVar1->parameters[0].velocStrafe);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xbbe6098c,&this->parameters[0].accelThrust,
                   pWVar1->parameters[0].accelThrust);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x86e9f09b,&this->parameters[0].omegaSpin,
                   pWVar1->parameters[0].omegaSpin);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xf5a0ce6a,&this->parameters[0].omegaTurn,
                   pWVar1->parameters[0].omegaTurn);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xa9363c6b,&this->parameters[0].alphaSteer,
                   pWVar1->parameters[0].alphaSteer);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x3cca2705,&this->parameters[0].velocJump,
                   pWVar1->parameters[0].velocJump);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x8b38b03e,&this->parameters[1].alphaDamp,
                   pWVar1->parameters[1].alphaDamp);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xe8a5238b,&this->parameters[1].alphaTrack,
                   pWVar1->parameters[1].alphaTrack);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xd4ae3872,&this->parameters[1].pitchPitch,
                   pWVar1->parameters[1].pitchPitch);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x81506bd0,&this->parameters[1].pitchThrust,
                   pWVar1->parameters[1].pitchThrust);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x15add84a,&this->parameters[1].rollStrafe,
                   pWVar1->parameters[1].rollStrafe);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x111cd7d8,&this->parameters[1].velocForward,
                   pWVar1->parameters[1].velocForward);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xe4c48139,&this->parameters[1].velocReverse,
                   pWVar1->parameters[1].velocReverse);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xce60418e,&this->parameters[1].velocStrafe,
                   pWVar1->parameters[1].velocStrafe);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x2d7ae386,&this->parameters[1].accelThrust,
                   pWVar1->parameters[1].accelThrust);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x67a2fe05,&this->parameters[1].omegaSpin,
                   pWVar1->parameters[1].omegaSpin);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x571c8880,&this->parameters[1].omegaTurn,
                   pWVar1->parameters[1].omegaTurn);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x85f92215,&this->parameters[1].alphaSteer,
                   pWVar1->parameters[1].alphaSteer);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xdcf0a9db,&this->parameters[1].velocJump,
                   pWVar1->parameters[1].velocJump);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x1c690706,&this->parameters[2].alphaDamp,
                   pWVar1->parameters[2].alphaDamp);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xd60bd973,&this->parameters[2].alphaTrack,
                   pWVar1->parameters[2].alphaTrack);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x69ab3d1a,&this->parameters[2].pitchPitch,
                   pWVar1->parameters[2].pitchPitch);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x8f715b4c,&this->parameters[2].pitchThrust,
                   pWVar1->parameters[2].pitchThrust);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xaad1ec62,&this->parameters[2].rollStrafe,
                   pWVar1->parameters[2].rollStrafe);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x3fb64e04,&this->parameters[2].velocForward,
                   pWVar1->parameters[2].velocForward);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x1268530d,&this->parameters[2].velocReverse,
                   pWVar1->parameters[2].velocReverse);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xa445b4b6,&this->parameters[2].velocStrafe,
                   pWVar1->parameters[2].velocStrafe);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xbe842ade,&this->parameters[2].accelThrust,
                   pWVar1->parameters[2].accelThrust);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xf6a7c509,&this->parameters[2].omegaSpin,
                   pWVar1->parameters[2].omegaSpin);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xe81986dc,&this->parameters[2].omegaTurn,
                   pWVar1->parameters[2].omegaTurn);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x57d66d39,&this->parameters[2].alphaSteer,
                   pWVar1->parameters[2].alphaSteer);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x481c47a3,&this->parameters[2].velocJump,
                   pWVar1->parameters[2].velocJump);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x580dc4ec,this->jumpSound,0x10,
                   pWVar1->jumpSound);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xad3e89e3,this->landSound,0x10,
                   pWVar1->landSound);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0xbfbb2816,this->stepSound,0x10,
                   pWVar1->stepSound);
  ParameterDB::Get((ParameterDB *)&param_1,0x75e86529,0x91936a92,&this->animRate,pWVar1->animRate);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
