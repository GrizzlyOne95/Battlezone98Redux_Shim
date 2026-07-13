/*
 * Entry: 00419399
 * Name: PackString
 * Namespace: Global
 * Signature: bool PackString(char * * param_1, char * param_2, lua_State * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl PackString(char **param_1,char *param_2,lua_State *param_3,int param_4)

{
  char *pcVar1;
  int *unaff_ESI;
  int iVar2;
  uint local_8;
  
  pcVar1 = lua_tolstring((lua_State *)param_2,(int)param_3,&local_8);
  iVar2 = *unaff_ESI;
  if (local_8 < 0x1f) {
    if ((char **)(iVar2 + local_8) < param_1) {
      *(char *)(iVar2 + -1) = *(char *)(iVar2 + -1) + (char)local_8;
      iVar2 = *unaff_ESI;
LAB_004193ef:
      memcpy(iVar2,pcVar1,local_8);
      *unaff_ESI = *unaff_ESI + local_8;
      return true;
    }
  }
  else if ((char **)(iVar2 + 1 + local_8) < param_1) {
    *(char *)(iVar2 + -1) = *(char *)(iVar2 + -1) + '\x1f';
    *(char *)*unaff_ESI = (char)local_8;
    *unaff_ESI = *unaff_ESI + 1;
    iVar2 = *unaff_ESI;
    goto LAB_004193ef;
  }
  return false;
}
