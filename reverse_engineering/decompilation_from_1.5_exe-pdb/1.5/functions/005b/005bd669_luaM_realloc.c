/*
 * Entry: 005bd669
 * Name: luaM_realloc_
 * Namespace: Global
 * Signature: void * luaM_realloc_(lua_State * param_1, void * param_2, uint param_3, uint param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl luaM_realloc_(lua_State *param_1,void *param_2,uint param_3,uint param_4)

{
  global_State *pgVar1;
  void *pvVar2;
  
  pgVar1 = param_1->l_G;
  pvVar2 = (*pgVar1->frealloc)(pgVar1->ud,param_2,param_3,param_4);
  if ((pvVar2 == (void *)0x0) && (param_4 != 0)) {
                    /* WARNING: Subroutine does not return */
    luaD_throw(param_1,4);
  }
  pgVar1->totalbytes = pgVar1->totalbytes + (param_4 - param_3);
  return pvVar2;
}
