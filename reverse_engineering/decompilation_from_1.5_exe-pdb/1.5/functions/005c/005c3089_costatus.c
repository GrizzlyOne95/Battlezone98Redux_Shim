/*
 * Entry: 005c3089
 * Name: costatus
 * Namespace: Global
 * Signature: int costatus(lua_State * param_1, lua_State * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl costatus(lua_State *param_1,lua_State *param_2)

{
  int iVar1;
  lua_State *unaff_ESI;
  lua_Debug local_6c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_1 == unaff_ESI) {
    iVar1 = 0;
  }
  else {
    iVar1 = lua_status(unaff_ESI);
    if (iVar1 == 0) {
      iVar1 = lua_getstack(unaff_ESI,0,&local_6c);
      if (iVar1 < 1) {
        iVar1 = lua_gettop(unaff_ESI);
        iVar1 = (-(uint)(iVar1 != 0) & 0xfffffffe) + 3;
      }
      else {
        iVar1 = 2;
      }
    }
    else if (iVar1 == 1) {
      iVar1 = 1;
    }
    else {
      iVar1 = 3;
    }
  }
  return iVar1;
}
