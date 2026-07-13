/*
 * Entry: 005c59b2
 * Name: luaU_header
 * Namespace: Global
 * Signature: void luaU_header(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaU_header(char *param_1)

{
  builtin_strncpy(param_1,"\x1bLuaQ",6);
  builtin_strncpy(param_1 + 6,"\x01\x04\x04\x04\b",6);
  return;
}
