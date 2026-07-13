/*
 * Entry: 004cdf78
 * Name: FireballEffect::PreLoad
 * Namespace: FireballEffect
 * Signature: void PreLoad(FireballEffect * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall FireballEffect::PreLoad(FireballEffect *this)

{
  float *pfVar1;
  int iVar2;
  ParameterDB local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  ParameterDB::ParameterDB(&local_1c,"fireball.odf");
  ParameterDB::Get(&local_1c,0x3d017c29,0xbc5e1073,local_18,0x10,"particle.0");
  iVar2 = GetSpriteIndex(local_18);
  this->fireballTexture = iVar2;
  ParameterDB::Get(&local_1c,0x3d017c29,0xd045e882,&this->fireballFrames,0x10);
  ParameterDB::Get(&local_1c,0x3d017c29,0x1ceb4a7a,&this->fireballRate,5.0);
  ParameterDB::Get(&local_1c,0x3d017c29,0x91dcfcce,&this->fireballRadius,1.0);
  pfVar1 = &this->fireballScale;
  ParameterDB::Get(&local_1c,0x3d017c29,0x83a961da,pfVar1,1.0);
  *pfVar1 = ((*pfVar1 - 1.0) * this->fireballRate * this->fireballRadius) /
            (float)this->fireballFrames;
  ParameterDB::Get(&local_1c,0x3d017c29,0x88f1ef89,local_18,0x10,"particle.0");
  iVar2 = GetSpriteIndex(local_18);
  this->smokeTexture = iVar2;
  ParameterDB::Get(&local_1c,0x3d017c29,0xdd33060c,&this->smokeFrames,0x10);
  ParameterDB::Get(&local_1c,0x3d017c29,0x567840fc,&this->smokeLifespan,0.5);
  ParameterDB::Get(&local_1c,0x3d017c29,0x1f6a810,&this->smokePause,0.05);
  ParameterDB::Get(&local_1c,0x3d017c29,0x8566cba4,&this->smokeRadius,0.4);
  ParameterDB::Get(&local_1c,0x3d017c29,0x2a532704,&this->smokeScale,1.0);
  ParameterDB::Get(&local_1c,0x3d017c29,0xbb8ad7d1,&this->smokeVariance,3.0);
  ParameterDB::Get(&local_1c,0x3d017c29,0x40a86add,&this->smokeInherit,0.8);
  this->indexFirst = 0;
  this->indexLast = 0;
  ParameterDB::~ParameterDB(&local_1c);
  return;
}
