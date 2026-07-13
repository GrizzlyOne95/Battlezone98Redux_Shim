/*
 * Entry: 005b9f0e
 * Name: luaG_checkopenop
 * Namespace: Global
 * Signature: int luaG_checkopenop(uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaG_checkopenop(uint param_1)

{
  uint uVar1;
  
  uVar1 = param_1 & 0x3f;
  if ((0x1b < uVar1) && ((uVar1 < 0x1f || (uVar1 == 0x22)))) {
    return (uint)((param_1 & 0xff800000) == 0);
  }
  return 0;
}
