/*
 * Entry: 00552d39
 * Name: IsDeathMatch
 * Namespace: Global
 * Signature: int IsDeathMatch(dp_session_t * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl IsDeathMatch(dp_session_t *param_1)

{
  byte bVar1;
  int iVar2;
  byte local_14 [10];
  undefined1 local_a;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar2 = 0;
  do {
    bVar1 = param_1->szUserField[iVar2] & 0x7f;
    local_14[iVar2] = bVar1;
    if (bVar1 == 0x2e) {
      local_14[iVar2] = 0;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 10);
  local_a = 0;
  iVar2 = _strnicmp((char *)local_14,"multDM",6);
  if ((iVar2 != 0) && (iVar2 = _strnicmp((char *)local_14,"mult01",6), iVar2 != 0)) {
    iVar2 = _strnicmp((char *)local_14,"mult03",6);
    return (uint)(iVar2 == 0);
  }
  return 1;
}
