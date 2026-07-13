/*
 * Entry: 005b700a
 * Name: luaL_addlstring
 * Namespace: Global
 * Signature: void luaL_addlstring(luaL_Buffer * param_1, char * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaL_addlstring(luaL_Buffer *param_1,char *param_2,uint param_3)

{
  if (param_3 != 0) {
    do {
      param_3 = param_3 - 1;
      if (param_1 + 1 <= (luaL_Buffer *)param_1->p) {
        luaL_prepbuffer(param_1);
      }
      *param_1->p = *param_2;
      param_1->p = param_1->p + 1;
      param_2 = param_2 + 1;
    } while (param_3 != 0);
  }
  return;
}
