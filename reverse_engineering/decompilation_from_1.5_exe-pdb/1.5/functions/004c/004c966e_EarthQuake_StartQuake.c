/*
 * Entry: 004c966e
 * Name: EarthQuake::StartQuake
 * Namespace: EarthQuake
 * Signature: void StartQuake(EarthQuake * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall EarthQuake::StartQuake(EarthQuake *this,float param_1)

{
  GAS_PREP_INFO local_50;
  GAS_CTRL local_34;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  this->scale = param_1;
  InitGASCtrl(&local_34);
  local_34.flags = 1;
  InitGASPrep(&local_50);
  local_50.loopMode = 1;
  local_50.pri = 0x41;
  _ftol2_sse();
  StartGASEvent("gquak01.wav",(_OBJ76 *)0x0,&local_34,&local_50);
  return;
}
