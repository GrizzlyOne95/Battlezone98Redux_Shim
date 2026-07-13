/*
 * Entry: 005b69d5
 * Name: lua_gc
 * Namespace: Global
 * Signature: int lua_gc(lua_State * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_gc(lua_State *param_1,int param_2,int param_3)

{
  global_State *pgVar1;
  uint uVar2;
  uint uVar3;
  
  pgVar1 = param_1->l_G;
  uVar3 = 0;
  switch(param_2) {
  case 0:
    pgVar1->GCthreshold = 0xfffffffd;
    break;
  case 1:
    pgVar1->GCthreshold = pgVar1->totalbytes;
    break;
  case 2:
    luaC_fullgc(param_1);
    break;
  case 3:
    uVar3 = pgVar1->totalbytes >> 10;
    break;
  case 4:
    uVar3 = pgVar1->totalbytes & 0x3ff;
    break;
  case 5:
    uVar2 = pgVar1->totalbytes;
    if (uVar2 < (uint)(param_3 * 0x400)) {
      pgVar1->GCthreshold = 0;
    }
    else {
      pgVar1->GCthreshold = uVar2 + param_3 * -0x400;
    }
    if (pgVar1->GCthreshold <= uVar2) {
      do {
        luaC_step(param_1);
        if (pgVar1->gcstate == '\0') {
          return 1;
        }
      } while (pgVar1->GCthreshold <= pgVar1->totalbytes);
    }
    break;
  case 6:
    uVar3 = pgVar1->gcpause;
    pgVar1->gcpause = param_3;
    break;
  case 7:
    uVar3 = pgVar1->gcstepmul;
    pgVar1->gcstepmul = param_3;
    break;
  default:
    uVar3 = 0xffffffff;
  }
  return uVar3;
}
