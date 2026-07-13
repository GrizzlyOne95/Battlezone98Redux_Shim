/*
 * Entry: 005b89e0
 * Name: growCI
 * Namespace: Global
 * Signature: CallInfo * growCI(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CallInfo * __cdecl growCI(lua_State *param_1)

{
  lua_State *unaff_ESI;
  
  if (20000 < unaff_ESI->size_ci) {
                    /* WARNING: Subroutine does not return */
    luaD_throw(unaff_ESI,5);
  }
  luaD_reallocCI(unaff_ESI,unaff_ESI->size_ci * 2);
  if (20000 < unaff_ESI->size_ci) {
    luaG_runerror(unaff_ESI,"stack overflow");
  }
  unaff_ESI->ci = unaff_ESI->ci + 1;
  return unaff_ESI->ci;
}
