/*
 * Entry: 005b71eb
 * Name: getF
 * Namespace: Global
 * Signature: char * getF(lua_State * param_1, void * param_2, uint * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl getF(lua_State *param_1,void *param_2,uint *param_3)

{
  int iVar1;
  size_t sVar2;
  
  if (*(int *)param_2 != 0) {
    *(undefined4 *)param_2 = 0;
    *param_3 = 1;
    return "\n";
  }
  iVar1 = feof(*(FILE **)((int)param_2 + 4));
  if (iVar1 != 0) {
    return (char *)0x0;
  }
  sVar2 = fread((void *)((int)param_2 + 8),1,0x200,*(FILE **)((int)param_2 + 4));
  *param_3 = sVar2;
  return (char *)(-(uint)(sVar2 != 0) & (uint)((int)param_2 + 8));
}
