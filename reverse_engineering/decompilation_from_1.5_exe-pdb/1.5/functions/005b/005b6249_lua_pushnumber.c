/*
 * Entry: 005b6249
 * Name: lua_pushnumber
 * Namespace: Global
 * Signature: void lua_pushnumber(lua_State * param_1, double param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_pushnumber(lua_State *param_1,double param_2)

{
  lua_TValue *plVar1;
  Value VVar2;
  undefined4 in_stack_00000008;
  
  VVar2._4_4_ = param_2._0_4_;
  VVar2.gc = (GCObject *)in_stack_00000008;
  plVar1 = param_1->top;
  plVar1->value = VVar2;
  plVar1->tt = 3;
  param_1->top = param_1->top + 1;
  return;
}
