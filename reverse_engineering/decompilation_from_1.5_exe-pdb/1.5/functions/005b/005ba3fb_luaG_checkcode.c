/*
 * Entry: 005ba3fb
 * Name: luaG_checkcode
 * Namespace: Global
 * Signature: int luaG_checkcode(Proto * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaG_checkcode(Proto *param_1)

{
  uint uVar1;
  
  uVar1 = symbexec(param_1,param_1->sizecode,0xff);
  return (uint)(uVar1 != 0);
}
