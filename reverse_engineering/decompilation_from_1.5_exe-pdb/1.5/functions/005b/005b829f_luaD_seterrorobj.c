/*
 * Entry: 005b829f
 * Name: luaD_seterrorobj
 * Namespace: Global
 * Signature: void luaD_seterrorobj(lua_State * param_1, int param_2, lua_TValue * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaD_seterrorobj(lua_State *param_1,int param_2,lua_TValue *param_3)

{
  lua_TValue *plVar1;
  GCObject *pGVar2;
  char *pcVar3;
  uint uVar4;
  
  if (1 < param_2) {
    if (param_2 < 4) {
      plVar1 = param_1->top;
      (param_3->value).gc = plVar1[-1].value.gc;
      *(undefined4 *)((int)&param_3->value + 4) = *(undefined4 *)((int)&plVar1[-1].value + 4);
      param_3->tt = plVar1[-1].tt;
    }
    else {
      if (param_2 == 4) {
        uVar4 = 0x11;
        pcVar3 = "not enough memory";
      }
      else {
        if (param_2 != 5) goto LAB_005b82fa;
        uVar4 = 0x17;
        pcVar3 = "error in error handling";
      }
      pGVar2 = (GCObject *)luaS_newlstr(param_1,pcVar3,uVar4);
      (param_3->value).gc = pGVar2;
      param_3->tt = 4;
    }
  }
LAB_005b82fa:
  param_1->top = param_3 + 1;
  return;
}
