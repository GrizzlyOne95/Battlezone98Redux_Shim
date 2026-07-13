/*
 * Entry: 005c54ae
 * Name: error
 * Namespace: Global
 * Signature: void error(LoadState * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl error(LoadState *param_1,char *param_2)

{
  undefined4 *unaff_ESI;
  
  luaO_pushfstring((lua_State *)*unaff_ESI,"%s: %s in precompiled chunk");
                    /* WARNING: Subroutine does not return */
  luaD_throw((lua_State *)*unaff_ESI,3);
}
