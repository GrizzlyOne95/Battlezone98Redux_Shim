/*
 * Entry: 005bd1c1
 * Name: luaF_getlocalname
 * Namespace: Global
 * Signature: char * luaF_getlocalname(Proto * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl luaF_getlocalname(Proto *param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < param_1->sizelocvars) {
    piVar1 = &param_1->locvars->endpc;
    do {
      if (param_3 < piVar1[-1]) {
        return (char *)0x0;
      }
      if ((param_3 < *piVar1) && (param_2 = param_2 + -1, param_2 == 0)) {
        return (char *)(param_1->locvars[iVar2].varname + 1);
      }
      iVar2 = iVar2 + 1;
      piVar1 = piVar1 + 3;
    } while (iVar2 < param_1->sizelocvars);
  }
  return (char *)0x0;
}
