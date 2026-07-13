/*
 * Entry: 005b7410
 * Name: getS
 * Namespace: Global
 * Signature: char * getS(lua_State * param_1, void * param_2, uint * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl getS(lua_State *param_1,void *param_2,uint *param_3)

{
  if (*(uint *)((int)param_2 + 4) == 0) {
    return (char *)0x0;
  }
  *param_3 = *(uint *)((int)param_2 + 4);
  *(undefined4 *)((int)param_2 + 4) = 0;
  return *(char **)param_2;
}
