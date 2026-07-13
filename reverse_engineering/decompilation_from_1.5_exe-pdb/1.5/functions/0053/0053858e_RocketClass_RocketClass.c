/*
 * Entry: 0053858e
 * Name: RocketClass::RocketClass
 * Namespace: RocketClass
 * Signature: RocketClass * RocketClass(RocketClass * this, RocketClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

RocketClass * __thiscall
RocketClass::RocketClass(RocketClass *this,RocketClass *param_1,long64 param_2)

{
  int iVar1;
  undefined4 unaff_EDI;
  ParameterDB local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  BulletClass::BulletClass
            ((BulletClass *)this,(BulletClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB(&local_1c,(char *)&this->_padding_);
  ParameterDB::Get(&local_1c,0xbfed7b6f,0x278d7166,&this->flameRadius,param_1->flameRadius);
  ParameterDB::Get(&local_1c,0xbfed7b6f,0xf7c7cb9c,&this->flameLength,param_1->flameLength);
  ParameterDB::Get(&local_1c,0xbfed7b6f,0xb051e2db,local_18,0x10,(char *)0x0);
  if (local_18[0] == '\0') {
    iVar1 = param_1->flameIndex;
  }
  else {
    iVar1 = GetSpriteIndex(local_18);
  }
  this->flameIndex = iVar1;
  ParameterDB::Get(&local_1c,0xbfed7b6f,0x5d27caba,&this->flameCount,param_1->flameCount);
  ParameterDB::Get(&local_1c,0xbfed7b6f,0x1ceb10c5,&this->flareRadius,param_1->flareRadius);
  ParameterDB::Get(&local_1c,0xbfed7b6f,0x14e4e216,local_18,0x10,(char *)0x0);
  if (local_18[0] == '\0') {
    iVar1 = param_1->flareIndex;
  }
  else {
    iVar1 = GetSpriteIndex(local_18);
  }
  this->flareIndex = iVar1;
  ParameterDB::Get(&local_1c,0xbfed7b6f,0x91cf383d,&this->flareCount,param_1->flareCount);
  ParameterDB::Get(&local_1c,0xbfed7b6f,0xf3e8cfc6,&this->smokeDevRadial,param_1->smokeDevRadial);
  ParameterDB::Get(&local_1c,0xbfed7b6f,0x80c3efaa,&this->smokeDevAxial,param_1->smokeDevAxial);
  ParameterDB::Get(&local_1c,0xbfed7b6f,0x40a86add,&this->smokeInherit,param_1->smokeInherit);
  ParameterDB::Get(&local_1c,0xbfed7b6f,0x8566cba4,&this->smokeRadius,param_1->smokeRadius);
  ParameterDB::Get(&local_1c,0xbfed7b6f,0x1f6a810,&this->smokePause,
                   this->smokeRadius / (float)param_1->_padding_);
  ParameterDB::Get(&local_1c,0xbfed7b6f,0x78049c9,&this->smokeRate,1.0 / param_1->smokeRate);
  this->smokeRate = 1.0 / this->smokeRate;
  ParameterDB::Get(&local_1c,0xbfed7b6f,0x88f1ef89,local_18,0x10,(char *)0x0);
  if (local_18[0] == '\0') {
    iVar1 = param_1->smokeIndex;
  }
  else {
    iVar1 = GetSpriteIndex(local_18);
  }
  this->smokeIndex = iVar1;
  ParameterDB::Get(&local_1c,0xbfed7b6f,0xdd33060c,&this->smokeCount,param_1->smokeCount);
  ParameterDB::~ParameterDB(&local_1c);
  return this;
}
