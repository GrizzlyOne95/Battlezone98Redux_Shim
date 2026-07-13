/*
 * Entry: 005b9df4
 * Name: info_tailcall
 * Namespace: Global
 * Signature: void info_tailcall(lua_Debug * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl info_tailcall(lua_Debug *param_1)

{
  int unaff_ESI;
  
  *(undefined4 *)(unaff_ESI + 0x14) = 0xffffffff;
  *(undefined4 *)(unaff_ESI + 0x1c) = 0xffffffff;
  *(undefined4 *)(unaff_ESI + 0x20) = 0xffffffff;
  *(char **)(unaff_ESI + 8) = "";
  *(char **)(unaff_ESI + 4) = "";
  *(char **)(unaff_ESI + 0x10) = "=(tail call)";
  *(char **)(unaff_ESI + 0xc) = "tail";
  luaO_chunkid((char *)(unaff_ESI + 0x24),"=(tail call)",0x3c);
  *(undefined4 *)(unaff_ESI + 0x18) = 0;
  return;
}
