/*
 * Entry: 005bf997
 * Name: math_random
 * Namespace: Global
 * Signature: int math_random(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl math_random(lua_State *param_1)

{
  double dVar1;
  int iVar2;
  int iVar3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  float10 fVar4;
  
  iVar2 = rand();
  dVar1 = (double)(iVar2 % 0x7fff) * 3.051850947599719e-05;
  iVar2 = lua_gettop(param_1);
  if (iVar2 == 0) {
    fVar4 = (float10)dVar1;
  }
  else {
    if (iVar2 != 1) {
      if (iVar2 == 2) {
        iVar2 = luaL_checkinteger(param_1,1);
        iVar3 = luaL_checkinteger(param_1,2);
        if (iVar3 < iVar2) {
          luaL_argerror(param_1,2,"interval is empty");
        }
        fVar4 = (float10)floor((double)((iVar3 - iVar2) + 1) * dVar1);
        lua_pushnumber(param_1,(double)CONCAT44(unaff_ESI,
                                                (int)((ulonglong)(double)(fVar4 + (float10)iVar2) >>
                                                     0x20)));
        return 1;
      }
      iVar2 = luaL_error(param_1,"wrong number of arguments");
      return iVar2;
    }
    iVar2 = luaL_checkinteger(param_1,1);
    if (iVar2 < 1) {
      luaL_argerror(param_1,1,"interval is empty");
    }
    fVar4 = (float10)floor((double)iVar2 * dVar1);
    fVar4 = fVar4 + (float10)1.0;
  }
  lua_pushnumber(param_1,(double)CONCAT44(unaff_EDI,(int)((ulonglong)(double)fVar4 >> 0x20)));
  return 1;
}
