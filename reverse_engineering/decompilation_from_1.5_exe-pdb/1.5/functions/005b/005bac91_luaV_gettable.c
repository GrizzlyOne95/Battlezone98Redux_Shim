/*
 * Entry: 005bac91
 * Name: luaV_gettable
 * Namespace: Global
 * Signature: void luaV_gettable(lua_State * param_1, lua_TValue * param_2, lua_TValue * param_3, lua_TValue * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
luaV_gettable(lua_State *param_1,lua_TValue *param_2,lua_TValue *param_3,lua_TValue *param_4)

{
  GCObject *pGVar1;
  Table *pTVar2;
  lua_TValue *plVar3;
  lua_TValue *plVar4;
  lua_TValue *unaff_EBX;
  lua_TValue *unaff_ESI;
  lua_TValue *unaff_EDI;
  int local_8;
  
  local_8 = 0;
  do {
    if (param_2->tt == 5) {
      pGVar1 = (param_2->value).gc;
      plVar3 = luaH_get(&pGVar1->h,param_3);
      if ((((plVar3->tt != 0) || (pTVar2 = (pGVar1->h).metatable, pTVar2 == (Table *)0x0)) ||
          ((pTVar2->flags & 1) != 0)) ||
         (plVar4 = luaT_gettm(pTVar2,TM_INDEX,param_1->l_G->tmname[0]), plVar4 == (lua_TValue *)0x0)
         ) {
        (param_4->value).gc = (plVar3->value).gc;
        *(undefined4 *)((int)&param_4->value + 4) = *(undefined4 *)((int)&plVar3->value + 4);
        param_4->tt = plVar3->tt;
        return;
      }
    }
    else {
      plVar4 = luaT_gettmbyobj(param_1,param_2,TM_INDEX);
      if (plVar4->tt == 0) {
        luaG_typeerror(param_1,param_2,"index");
      }
    }
    param_2 = plVar4;
    if (param_2->tt == 6) {
      callTMres(param_1,param_2,unaff_EDI,unaff_ESI,unaff_EBX);
      return;
    }
    local_8 = local_8 + 1;
  } while (local_8 < 100);
  luaG_runerror(param_1,"loop in gettable");
  return;
}
