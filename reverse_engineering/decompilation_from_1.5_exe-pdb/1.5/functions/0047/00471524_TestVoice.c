/*
 * Entry: 00471524
 * Name: TestVoice
 * Namespace: Global
 * Signature: void TestVoice(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl TestVoice(long param_1)

{
  _gas_object *p_Var1;
  GAS_CTRL local_34;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  InitGASCtrl(&local_34);
  local_34.flags = 0x14;
  p_Var1 = FindGASObjectActiveList("avconsv9.wav",(_OBJ76 *)0x0);
  StopGASEvent(p_Var1);
  SetGASMasterVolumes(-2,-2,param_1);
  StartGASEvent("avconsv9.wav",(_OBJ76 *)0x0,&local_34,(GAS_PREP_INFO *)0x0);
  return;
}
