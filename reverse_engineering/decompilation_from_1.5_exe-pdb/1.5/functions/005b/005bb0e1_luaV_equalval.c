/*
 * Entry: 005bb0e1
 * Name: luaV_equalval
 * Namespace: Global
 * Signature: int luaV_equalval(lua_State * param_1, lua_TValue * param_2, lua_TValue * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaV_equalval(lua_State *param_1,lua_TValue *param_2,lua_TValue *param_3)

{
  int iVar1;
  GCObject *pGVar2;
  lua_TValue *plVar3;
  lua_TValue *unaff_EBX;
  lua_TValue *unaff_ESI;
  Table *unaff_EDI;
  
  iVar1 = param_2->tt;
  if (iVar1 != 0) {
    if ((iVar1 == 1) || (iVar1 == 2)) {
      pGVar2 = (param_2->value).gc;
LAB_005bb16d:
      return (uint)(pGVar2 == (param_3->value).gc);
    }
    if (iVar1 == 3) {
      if ((param_3->value).n != (param_2->value).n) {
        return 0;
      }
    }
    else {
      if (iVar1 == 5) {
        pGVar2 = (GCObject *)(param_2->value).b;
      }
      else {
        pGVar2 = (GCObject *)(param_2->value).b;
        if (iVar1 != 7) goto LAB_005bb16d;
      }
      if (pGVar2 != (GCObject *)(param_3->value).b) {
        plVar3 = get_compTM((lua_State *)(pGVar2->h).metatable,
                            (((GCObject *)(param_3->value).b)->h).metatable,unaff_EDI,(TMS)unaff_ESI
                           );
        if (plVar3 != (lua_TValue *)0x0) {
          callTMres(param_1,plVar3,(lua_TValue *)unaff_EDI,unaff_ESI,unaff_EBX);
          iVar1 = param_1->top->tt;
          if (iVar1 != 0) {
            if (iVar1 != 1) {
              return 1;
            }
            if ((param_1->top->value).gc != (GCObject *)0x0) {
              return 1;
            }
          }
        }
        return 0;
      }
    }
  }
  return 1;
}
