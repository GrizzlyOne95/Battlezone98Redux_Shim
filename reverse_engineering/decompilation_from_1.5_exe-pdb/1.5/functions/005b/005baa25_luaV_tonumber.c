/*
 * Entry: 005baa25
 * Name: luaV_tonumber
 * Namespace: Global
 * Signature: lua_TValue * luaV_tonumber(lua_TValue * param_1, lua_TValue * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

lua_TValue * __cdecl luaV_tonumber(lua_TValue *param_1,lua_TValue *param_2)

{
  Value VVar1;
  int iVar2;
  undefined4 local_c;
  undefined4 uStack_8;
  
  if (param_1->tt != 3) {
    if (param_1->tt == 4) {
      iVar2 = luaO_str2d((char *)((param_1->value).b + 0x10),(double *)&local_c);
      if (iVar2 != 0) {
        VVar1._4_4_ = uStack_8;
        VVar1.gc = (GCObject *)local_c;
        param_2->value = VVar1;
        param_2->tt = 3;
        return param_2;
      }
    }
    param_1 = (lua_TValue *)0x0;
  }
  return param_1;
}
