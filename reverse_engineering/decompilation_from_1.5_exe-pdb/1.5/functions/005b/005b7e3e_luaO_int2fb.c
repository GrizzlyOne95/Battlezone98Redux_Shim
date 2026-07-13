/*
 * Entry: 005b7e3e
 * Name: luaO_int2fb
 * Namespace: Global
 * Signature: int luaO_int2fb(uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaO_int2fb(uint param_1)

{
  int iVar1;
  
  iVar1 = 0;
  for (; 0xf < param_1; param_1 = param_1 + 1 >> 1) {
    iVar1 = iVar1 + 1;
  }
  if (param_1 < 8) {
    return param_1;
  }
  return iVar1 * 8 + 8U | param_1 - 8;
}
