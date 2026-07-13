/*
 * Entry: 005bb2f0
 * Name: Arith
 * Namespace: Global
 * Signature: void Arith(lua_State * param_1, lua_TValue * param_2, lua_TValue * param_3, lua_TValue * param_4, TMS param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Arith(lua_State *param_1,lua_TValue *param_2,lua_TValue *param_3,lua_TValue *param_4,TMS param_5)

{
  lua_TValue *plVar1;
  lua_TValue *plVar2;
  int iVar3;
  lua_TValue *unaff_ESI;
  float10 fVar4;
  float10 fVar5;
  lua_TValue local_2c;
  double local_1c;
  undefined1 local_14 [16];
  
  plVar1 = luaV_tonumber(param_2,(lua_TValue *)local_14);
  if ((plVar1 == (lua_TValue *)0x0) ||
     (plVar2 = luaV_tonumber(param_3,&local_2c), plVar2 == (lua_TValue *)0x0)) {
    iVar3 = call_binTM(param_1,param_2,param_3,unaff_ESI,(TMS)param_4);
    if (iVar3 == 0) {
      luaG_aritherror(param_1,param_2,param_3);
    }
  }
  else {
    local_1c = (plVar1->value).n;
    fVar4 = (float10)local_1c;
    local_14._8_8_ = (plVar2->value).n;
    fVar5 = (float10)(double)local_14._8_8_;
    if (param_4 == (lua_TValue *)0x5) {
      fVar4 = fVar5 + fVar4;
    }
    else if (param_4 == (lua_TValue *)0x6) {
      fVar4 = fVar4 - fVar5;
    }
    else if (param_4 == (lua_TValue *)0x7) {
      fVar4 = fVar5 * fVar4;
    }
    else if (param_4 == (lua_TValue *)0x8) {
      fVar4 = fVar4 / fVar5;
    }
    else if (param_4 == (lua_TValue *)0x9) {
      fVar5 = (float10)floor((double)(fVar4 / fVar5));
      fVar4 = (float10)local_1c - fVar5 * (float10)(double)local_14._8_8_;
    }
    else if (param_4 == (lua_TValue *)0xa) {
      fVar4 = (float10)__CIpow();
    }
    else {
      if (param_4 != (lua_TValue *)0xb) {
        return;
      }
      fVar4 = -fVar4;
    }
    (unaff_ESI->value).n = (double)fVar4;
    unaff_ESI->tt = 3;
  }
  return;
}
