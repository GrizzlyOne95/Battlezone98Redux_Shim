/*
 * Entry: 005b7e64
 * Name: luaO_fb2int
 * Namespace: Global
 * Signature: int luaO_fb2int(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaO_fb2int(int param_1)

{
  uint uVar1;
  
  uVar1 = param_1 >> 3 & 0x1f;
  if (uVar1 != 0) {
    param_1 = (param_1 & 7U) + 8 << ((char)uVar1 - 1U & 0x1f);
  }
  return param_1;
}
