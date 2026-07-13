/*
 * Entry: 005b7e7c
 * Name: luaO_log2
 * Namespace: Global
 * Signature: int luaO_log2(uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaO_log2(uint param_1)

{
  int iVar1;
  
  iVar1 = -1;
  for (; 0xff < param_1; param_1 = param_1 >> 8) {
    iVar1 = iVar1 + 8;
  }
  return (uint)""[param_1] + iVar1;
}
