/*
 * Entry: 004194ea
 * Name: UnpackTable
 * Namespace: Global
 * Signature: void UnpackTable(char * * param_1, lua_State * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UnpackTable(char **param_1,lua_State *param_2)

{
  char *pcVar1;
  lua_State *unaff_EBX;
  uint uVar2;
  char **unaff_EDI;
  
  pcVar1 = *unaff_EDI;
  uVar2 = (int)pcVar1[-1] & 0x1f;
  if (uVar2 == 0x1f) {
    uVar2 = (uint)*pcVar1;
    *unaff_EDI = pcVar1 + 1;
  }
  lua_createtable(unaff_EBX,0,0);
  if (0 < (int)uVar2) {
    do {
      UnpackValue(unaff_EDI,unaff_EBX);
      UnpackValue(unaff_EDI,unaff_EBX);
      lua_rawset(unaff_EBX,-3);
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
  return;
}
