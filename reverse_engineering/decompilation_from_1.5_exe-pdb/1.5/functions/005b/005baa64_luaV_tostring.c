/*
 * Entry: 005baa64
 * Name: luaV_tostring
 * Namespace: Global
 * Signature: int luaV_tostring(lua_State * param_1, lua_TValue * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl luaV_tostring(lua_State *param_1,lua_TValue *param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  GCObject *pGVar4;
  char local_28 [32];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_2->tt == 3) {
    sprintf(local_28,"%.14g",(param_2->value).n);
    pcVar3 = local_28;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    pGVar4 = (GCObject *)luaS_newlstr(param_1,local_28,(int)pcVar3 - (int)(local_28 + 1));
    (param_2->value).gc = pGVar4;
    param_2->tt = 4;
    iVar2 = 1;
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}
