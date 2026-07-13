/*
 * Entry: 005b892f
 * Name: restore_stack_limit
 * Namespace: Global
 * Signature: void restore_stack_limit(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl restore_stack_limit(lua_State *param_1)

{
  lua_State *in_ECX;
  
  if (20000 < in_ECX->size_ci) {
    if (((int)in_ECX->ci - (int)in_ECX->base_ci) / 0x18 + 1 < 20000) {
      luaD_reallocCI(in_ECX,20000);
    }
  }
  return;
}
