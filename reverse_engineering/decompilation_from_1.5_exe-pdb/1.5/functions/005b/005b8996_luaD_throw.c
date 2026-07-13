/*
 * Entry: 005b8996
 * Name: luaD_throw
 * Namespace: Global
 * Signature: void luaD_throw(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaD_throw(lua_State *param_1,int param_2)

{
  int unaff_ESI;
  
  if (param_1->errorJmp != (lua_longjmp *)0x0) {
    param_1->errorJmp->status = param_2;
                    /* WARNING: Subroutine does not return */
    longjmp(param_1->errorJmp->b,1);
  }
  param_1->status = (uchar)param_2;
  if (param_1->l_G->panic != (_func___cdecl_int_lua_State_ptr *)0x0) {
    resetstack((lua_State *)param_2,unaff_ESI);
    (*param_1->l_G->panic)(param_1);
  }
                    /* WARNING: Subroutine does not return */
  exit(1);
}
