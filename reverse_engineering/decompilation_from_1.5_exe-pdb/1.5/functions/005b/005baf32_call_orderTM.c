/*
 * Entry: 005baf32
 * Name: call_orderTM
 * Namespace: Global
 * Signature: int call_orderTM(lua_State * param_1, lua_TValue * param_2, lua_TValue * param_3, TMS param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl call_orderTM(lua_State *param_1,lua_TValue *param_2,lua_TValue *param_3,TMS param_4)

{
  lua_State *in_EAX;
  lua_TValue *plVar1;
  lua_TValue *plVar2;
  int iVar3;
  lua_TValue *unaff_EBP;
  lua_TValue *unaff_ESI;
  lua_TValue *unaff_EDI;
  
  plVar1 = luaT_gettmbyobj(in_EAX,(lua_TValue *)param_1,(TMS)param_3);
  if (plVar1->tt != 0) {
    plVar2 = luaT_gettmbyobj(in_EAX,param_2,(TMS)param_3);
    iVar3 = luaO_rawequalObj(plVar1,plVar2);
    if (iVar3 != 0) {
      callTMres(in_EAX,plVar1,unaff_EDI,unaff_ESI,unaff_EBP);
      iVar3 = in_EAX->top->tt;
      if ((iVar3 != 0) && ((iVar3 != 1 || ((in_EAX->top->value).gc != (GCObject *)0x0)))) {
        return 1;
      }
      return 0;
    }
  }
  return -1;
}
