/*
 * Entry: 004cdac0
 * Name: EngineSplash::PreLoad
 * Namespace: EngineSplash
 * Signature: void PreLoad(EngineSplash * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall EngineSplash::PreLoad(EngineSplash *this)

{
  int iVar1;
  ParameterDB local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  ParameterDB::ParameterDB(&local_1c,"engsplsh.odf");
  ParameterDB::Get(&local_1c,0xb571e03c,0x7caf4e69,local_18,0x10,"splash.0");
  iVar1 = GetSpriteIndex(local_18);
  this->splashTexture = iVar1;
  ParameterDB::Get(&local_1c,0xb571e03c,0xc4ca506c,&this->splashFrames,0xe);
  ParameterDB::Get(&local_1c,0xb571e03c,0x16194e31,&this->splashVariance,3);
  ParameterDB::Get(&local_1c,0xb571e03c,0xb421904,&this->splashRadius,1.5);
  this->splashIndex = 0;
  this->splashPtr = this->splashList;
  ParameterDB::~ParameterDB(&local_1c);
  return;
}
