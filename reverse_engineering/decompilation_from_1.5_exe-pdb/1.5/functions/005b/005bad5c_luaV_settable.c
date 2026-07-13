/*
 * Entry: 005bad5c
 * Name: luaV_settable
 * Namespace: Global
 * Signature: void luaV_settable(lua_State * param_1, lua_TValue * param_2, lua_TValue * param_3, lua_TValue * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
luaV_settable(lua_State *param_1,lua_TValue *param_2,lua_TValue *param_3,lua_TValue *param_4)

{
  GCObject *pGVar1;
  Table *pTVar2;
  lua_TValue *plVar3;
  lua_State *plVar4;
  lua_TValue *unaff_EBX;
  lua_TValue *unaff_ESI;
  lua_TValue *unaff_EDI;
  undefined4 in_stack_ffffffe8;
  int local_8;
  
  local_8 = 0;
  do {
    if (param_2->tt == 5) {
      pGVar1 = (param_2->value).gc;
      plVar3 = luaH_set(param_1,&pGVar1->h,param_3);
      if ((((plVar3->tt != 0) || (pTVar2 = (pGVar1->h).metatable, pTVar2 == (Table *)0x0)) ||
          ((pTVar2->flags & 2) != 0)) ||
         (plVar4 = (lua_State *)luaT_gettm(pTVar2,TM_NEWINDEX,param_1->l_G->tmname[1]),
         plVar4 == (lua_State *)0x0)) {
        (plVar3->value).gc = (param_4->value).gc;
        *(undefined4 *)((int)&plVar3->value + 4) = *(undefined4 *)((int)&param_4->value + 4);
        plVar3->tt = param_4->tt;
        (pGVar1->h).flags = '\0';
        if (param_4->tt < 4) {
          return;
        }
        if ((*(byte *)((param_4->value).b + 5) & 3) == 0) {
          return;
        }
        if (((pGVar1->gch).marked & 4) == 0) {
          return;
        }
        luaC_barrierback(param_1,&pGVar1->h);
        return;
      }
    }
    else {
      plVar4 = (lua_State *)luaT_gettmbyobj(param_1,param_2,TM_NEWINDEX);
      if (plVar4->top == (lua_TValue *)0x0) {
        luaG_typeerror(param_1,param_2,"index");
      }
    }
    if (plVar4->top == (lua_TValue *)0x6) {
      callTM(plVar4,unaff_EDI,unaff_ESI,unaff_EBX,(lua_TValue *)in_stack_ffffffe8);
      return;
    }
    in_stack_ffffffe8 = plVar4->next;
    local_8 = local_8 + 1;
    param_2 = (lua_TValue *)&stack0xffffffe8;
  } while (local_8 < 100);
  luaG_runerror(param_1,"loop in settable");
  return;
}
