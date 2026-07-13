/*
 * Entry: 004a7975
 * Name: PersonClass::PersonClass
 * Namespace: PersonClass
 * Signature: PersonClass * PersonClass(PersonClass * this, PersonClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PersonClass * __thiscall
PersonClass::PersonClass(PersonClass *this,PersonClass *param_1,long64 param_2)

{
  PersonClass *pPVar1;
  char (*pacVar2) [16];
  undefined4 unaff_EDI;
  uint local_8;
  
  pPVar1 = param_1;
  CraftClass::CraftClass((CraftClass *)this,(CraftClass *)param_1,CONCAT44(unaff_EDI,(int)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xed315e04,&this->parameters[0].alphaDamp,
                   pPVar1->parameters[0].alphaDamp);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xd2a79ef5,&this->parameters[0].alphaTrack,
                   pPVar1->parameters[0].alphaTrack);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xa1d381e8,&this->parameters[0].pitchPitch,
                   pPVar1->parameters[0].pitchPitch);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xd76b553a,&this->parameters[0].pitchThrust,
                   pPVar1->parameters[0].pitchThrust);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x88f5bc00,&this->parameters[0].rollStrafe,
                   pPVar1->parameters[0].rollStrafe);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xaf7b8b02,&this->parameters[0].velocForward,
                   pPVar1->parameters[0].velocForward);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x5d02411f,&this->parameters[0].velocReverse,
                   pPVar1->parameters[0].velocReverse);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x3cf570d4,&this->parameters[0].velocStrafe,
                   pPVar1->parameters[0].velocStrafe);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xbbe6098c,&this->parameters[0].accelThrust,
                   pPVar1->parameters[0].accelThrust);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x86e9f09b,&this->parameters[0].omegaSpin,
                   pPVar1->parameters[0].omegaSpin);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xf5a0ce6a,&this->parameters[0].omegaTurn,
                   pPVar1->parameters[0].omegaTurn);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xa9363c6b,&this->parameters[0].alphaSteer,
                   pPVar1->parameters[0].alphaSteer);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x3cca2705,&this->parameters[0].velocJump,
                   pPVar1->parameters[0].velocJump);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x8b38b03e,&this->parameters[1].alphaDamp,
                   pPVar1->parameters[1].alphaDamp);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xe8a5238b,&this->parameters[1].alphaTrack,
                   pPVar1->parameters[1].alphaTrack);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xd4ae3872,&this->parameters[1].pitchPitch,
                   pPVar1->parameters[1].pitchPitch);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x81506bd0,&this->parameters[1].pitchThrust,
                   pPVar1->parameters[1].pitchThrust);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x15add84a,&this->parameters[1].rollStrafe,
                   pPVar1->parameters[1].rollStrafe);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x111cd7d8,&this->parameters[1].velocForward,
                   pPVar1->parameters[1].velocForward);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xe4c48139,&this->parameters[1].velocReverse,
                   pPVar1->parameters[1].velocReverse);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xce60418e,&this->parameters[1].velocStrafe,
                   pPVar1->parameters[1].velocStrafe);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x2d7ae386,&this->parameters[1].accelThrust,
                   pPVar1->parameters[1].accelThrust);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x67a2fe05,&this->parameters[1].omegaSpin,
                   pPVar1->parameters[1].omegaSpin);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x571c8880,&this->parameters[1].omegaTurn,
                   pPVar1->parameters[1].omegaTurn);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x85f92215,&this->parameters[1].alphaSteer,
                   pPVar1->parameters[1].alphaSteer);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xdcf0a9db,&this->parameters[1].velocJump,
                   pPVar1->parameters[1].velocJump);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x1c690706,&this->parameters[2].alphaDamp,
                   pPVar1->parameters[2].alphaDamp);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xd60bd973,&this->parameters[2].alphaTrack,
                   pPVar1->parameters[2].alphaTrack);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x69ab3d1a,&this->parameters[2].pitchPitch,
                   pPVar1->parameters[2].pitchPitch);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x8f715b4c,&this->parameters[2].pitchThrust,
                   pPVar1->parameters[2].pitchThrust);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xaad1ec62,&this->parameters[2].rollStrafe,
                   pPVar1->parameters[2].rollStrafe);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x3fb64e04,&this->parameters[2].velocForward,
                   pPVar1->parameters[2].velocForward);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x1268530d,&this->parameters[2].velocReverse,
                   pPVar1->parameters[2].velocReverse);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xa445b4b6,&this->parameters[2].velocStrafe,
                   pPVar1->parameters[2].velocStrafe);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xbe842ade,&this->parameters[2].accelThrust,
                   pPVar1->parameters[2].accelThrust);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xf6a7c509,&this->parameters[2].omegaSpin,
                   pPVar1->parameters[2].omegaSpin);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xe81986dc,&this->parameters[2].omegaTurn,
                   pPVar1->parameters[2].omegaTurn);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x57d66d39,&this->parameters[2].alphaSteer,
                   pPVar1->parameters[2].alphaSteer);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x481c47a3,&this->parameters[2].velocJump,
                   pPVar1->parameters[2].velocJump);
  local_8 = 0;
  pacVar2 = this->painSound;
  param_2._0_4_ = (int)pPVar1 - (int)this;
  do {
    ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,
                     ((byte)((char)local_8 + 0x31) ^ 0x258b0684) * 0x1000193,*pacVar2,0x10,
                     *pacVar2 + (int)param_2);
    local_8 = local_8 + 1;
    pacVar2 = pacVar2 + 1;
  } while (local_8 < 6);
  local_8 = 0;
  pacVar2 = this->burnSound;
  do {
    ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,
                     ((byte)((char)local_8 + 0x31) ^ 0xa1e21157) * 0x1000193,*pacVar2,0x10,
                     *pacVar2 + (int)param_2);
    local_8 = local_8 + 1;
    pacVar2 = pacVar2 + 1;
  } while (local_8 < 2);
  local_8 = 0;
  pacVar2 = this->dieSound;
  do {
    ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,
                     ((byte)((char)local_8 + 0x31) ^ 0x42d28de8) * 0x1000193,*pacVar2,0x10,
                     *pacVar2 + (int)param_2);
    local_8 = local_8 + 1;
    pacVar2 = pacVar2 + 1;
  } while (local_8 < 5);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x998b67ab,this->crushSound,0x10,
                   pPVar1->crushSound);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x580dc4ec,this->jumpSound,0x10,
                   pPVar1->jumpSound);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xad3e89e3,this->landSound,0x10,
                   pPVar1->landSound);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0xbfbb2816,this->stepSound,0x10,
                   pPVar1->stepSound);
  ParameterDB::Get((ParameterDB *)&param_1,0xefaec898,0x91936a92,&this->animRate,pPVar1->animRate);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
