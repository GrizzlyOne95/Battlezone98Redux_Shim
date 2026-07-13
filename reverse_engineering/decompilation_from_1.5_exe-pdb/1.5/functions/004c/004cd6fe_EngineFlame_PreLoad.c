/*
 * Entry: 004cd6fe
 * Name: EngineFlame::PreLoad
 * Namespace: EngineFlame
 * Signature: void PreLoad(EngineFlame * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall EngineFlame::PreLoad(EngineFlame *this)

{
  int iVar1;
  ParameterDB local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  ParameterDB::ParameterDB(&local_1c,"engflame.odf");
  ParameterDB::Get(&local_1c,0x9e8ab786,0xb051e2db,local_18,0x10,"exhaust_b.0");
  iVar1 = GetSpriteIndex(local_18);
  this->flameTexture = iVar1;
  ParameterDB::Get(&local_1c,0x9e8ab786,0x5d27caba,&this->flameFrames,4);
  ParameterDB::Get(&local_1c,0x9e8ab786,0xf7c7cb9c,&this->flameLength,3.0);
  this->flameIndex = 0;
  this->flamePtr = this->flameList;
  this->field_0x24 = this->field_0x24 & 0xf5 | 5;
  ParameterDB::~ParameterDB(&local_1c);
  return;
}
