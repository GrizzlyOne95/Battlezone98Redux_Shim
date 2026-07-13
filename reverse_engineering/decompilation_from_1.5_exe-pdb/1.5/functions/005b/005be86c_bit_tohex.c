/*
 * Entry: 005be86c
 * Name: bit_tohex
 * Namespace: Global
 * Signature: int bit_tohex(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl bit_tohex(lua_State *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char local_10 [8];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  uVar1 = barg(param_1,1);
  iVar2 = lua_type(param_1,2);
  if (iVar2 == -1) {
    uVar3 = 8;
  }
  else {
    uVar3 = barg(param_1,2);
  }
  pcVar5 = "0123456789abcdef";
  if ((int)uVar3 < 0) {
    uVar3 = -uVar3;
    pcVar5 = "0123456789ABCDEF";
  }
  uVar4 = uVar3;
  if (8 < (int)uVar3) {
    uVar3 = 8;
    uVar4 = uVar3;
  }
  while (-1 < (int)(uVar3 - 1)) {
    (&stack0xffffffef)[uVar3] = pcVar5[uVar1 & 0xf];
    uVar1 = uVar1 >> 4;
    uVar3 = uVar3 - 1;
  }
  lua_pushlstring(param_1,local_10,uVar4);
  return 1;
}
