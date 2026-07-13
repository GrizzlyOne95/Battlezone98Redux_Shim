/*
 * Entry: 00419400
 * Name: UnpackString
 * Namespace: Global
 * Signature: void UnpackString(char * * param_1, lua_State * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UnpackString(char **param_1,lua_State *param_2)

{
  char *pcVar1;
  uint uVar2;
  int *unaff_EDI;
  
  pcVar1 = (char *)*unaff_EDI;
  uVar2 = (int)pcVar1[-1] & 0x1f;
  if (uVar2 == 0x1f) {
    uVar2 = (uint)*pcVar1;
    *unaff_EDI = (int)(pcVar1 + 1);
  }
  lua_pushlstring((lua_State *)param_1,(char *)*unaff_EDI,uVar2);
  *unaff_EDI = *unaff_EDI + uVar2;
  return;
}
