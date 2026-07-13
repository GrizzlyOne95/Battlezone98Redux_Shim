/*
 * Entry: 005c16d9
 * Name: auxsort
 * Namespace: Global
 * Signature: void auxsort(lua_State * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl auxsort(lua_State *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int unaff_EBP;
  int iVar3;
  int unaff_ESI;
  lua_State *unaff_EDI;
  int iVar4;
  
  iVar3 = param_2;
  if (param_2 < param_3) {
    do {
      lua_rawgeti(param_1,1,iVar3);
      lua_rawgeti(param_1,1,param_3);
      iVar1 = sort_comp(unaff_EDI,unaff_ESI,unaff_EBP);
      if (iVar1 == 0) {
        lua_settop(param_1,-3);
      }
      else {
        set2(param_1,iVar3,param_3);
      }
      if (param_3 - iVar3 == 1) {
        return;
      }
      iVar4 = (param_3 + iVar3) / 2;
      lua_rawgeti(param_1,1,iVar4);
      lua_rawgeti(param_1,1,iVar3);
      iVar2 = sort_comp(unaff_EDI,unaff_ESI,unaff_EBP);
      iVar1 = iVar3;
      if (iVar2 == 0) {
        lua_settop(param_1,-2);
        lua_rawgeti(param_1,1,param_3);
        iVar2 = sort_comp(unaff_EDI,unaff_ESI,unaff_EBP);
        iVar1 = param_3;
        if (iVar2 != 0) goto LAB_005c1792;
        lua_settop(param_1,-3);
      }
      else {
LAB_005c1792:
        set2(param_1,iVar4,iVar1);
      }
      if (param_3 - iVar3 == 2) {
        return;
      }
      lua_rawgeti(param_1,1,iVar4);
      lua_pushvalue(param_1,-1);
      lua_rawgeti(param_1,1,param_3 + -1);
      set2(param_1,iVar4,param_3 + -1);
      param_2 = param_3 + -1;
      iVar1 = iVar3;
      while( true ) {
        iVar1 = iVar1 + 1;
        lua_rawgeti(param_1,1,iVar1);
        while (iVar2 = sort_comp(unaff_EDI,unaff_ESI,unaff_EBP), iVar2 != 0) {
          if (param_3 < iVar1) {
            luaL_error(param_1,"invalid order function for sorting");
          }
          lua_settop(param_1,-2);
          iVar1 = iVar1 + 1;
          lua_rawgeti(param_1,1,iVar1);
        }
        param_2 = param_2 + -1;
        lua_rawgeti(param_1,1,param_2);
        while (iVar2 = sort_comp(unaff_EDI,unaff_ESI,unaff_EBP), iVar2 != 0) {
          if (param_2 < iVar3) {
            luaL_error(param_1,"invalid order function for sorting");
          }
          lua_settop(param_1,-2);
          param_2 = param_2 + -1;
          lua_rawgeti(param_1,1,param_2);
        }
        if (param_2 < iVar1) break;
        set2(param_1,iVar1,param_2);
      }
      lua_settop(param_1,-4);
      lua_rawgeti(param_1,1,param_3 + -1);
      lua_rawgeti(param_1,1,iVar1);
      set2(param_1,param_3 + -1,iVar1);
      if (iVar1 - iVar3 < param_3 - iVar1) {
        iVar2 = iVar3;
        iVar4 = param_3;
        iVar3 = iVar1 + 1;
        param_3 = iVar1 + -1;
      }
      else {
        iVar2 = iVar1 + 1;
        iVar4 = iVar1 + -1;
      }
      auxsort(param_1,iVar2,param_3);
      param_3 = iVar4;
    } while (iVar3 < iVar4);
  }
  return;
}
