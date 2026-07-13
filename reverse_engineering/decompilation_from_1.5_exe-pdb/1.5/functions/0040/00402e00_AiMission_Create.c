/*
 * Entry: 00402e00
 * Name: AiMission::Create
 * Namespace: AiMission
 * Signature: AiMission * Create(long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

AiMission * __cdecl AiMission::Create(long64 param_1)

{
  AiMission *pAVar1;
  long64 local_1c;
  char local_14 [8];
  undefined1 local_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_1c = param_1;
  strncpy(local_14,(char *)&local_1c,8);
  local_c = 0;
  pAVar1 = Create(local_14);
  return pAVar1;
}
