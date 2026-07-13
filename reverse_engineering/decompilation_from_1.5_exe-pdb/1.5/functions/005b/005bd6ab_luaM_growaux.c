/*
 * Entry: 005bd6ab
 * Name: luaM_growaux_
 * Namespace: Global
 * Signature: void * luaM_growaux_(lua_State * param_1, void * param_2, int * param_3, uint param_4, int param_5, char * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl
luaM_growaux_(lua_State *param_1,void *param_2,int *param_3,uint param_4,int param_5,char *param_6)

{
  int iVar1;
  void *pvVar2;
  
  iVar1 = *param_3;
  if (iVar1 < param_5 / 2) {
    param_5 = iVar1 * 2;
    if (param_5 < 4) {
      param_5 = 4;
    }
  }
  else if (param_5 <= iVar1) {
    luaG_runerror(param_1,param_6);
  }
  if (0xfffffffd / param_4 < param_5 + 1U) {
    pvVar2 = luaM_toobig(param_1);
  }
  else {
    pvVar2 = luaM_realloc_(param_1,param_2,*param_3 * param_4,param_5 * param_4);
  }
  *param_3 = param_5;
  return pvVar2;
}
