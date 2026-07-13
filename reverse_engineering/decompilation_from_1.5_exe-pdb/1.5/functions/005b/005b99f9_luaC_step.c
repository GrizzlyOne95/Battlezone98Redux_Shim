/*
 * Entry: 005b99f9
 * Name: luaC_step
 * Namespace: Global
 * Signature: void luaC_step(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaC_step(lua_State *param_1)

{
  global_State *pgVar1;
  int iVar2;
  uint uVar3;
  lua_State *unaff_EDI;
  int iVar4;
  
  pgVar1 = param_1->l_G;
  iVar4 = pgVar1->gcstepmul * 10;
  if (iVar4 == 0) {
    iVar4 = 0x7ffffffe;
  }
  pgVar1->gcdept = pgVar1->gcdept + (pgVar1->totalbytes - pgVar1->GCthreshold);
  do {
    iVar2 = singlestep(unaff_EDI);
    iVar4 = iVar4 - iVar2;
    if (pgVar1->gcstate == '\0') goto LAB_005b9a54;
  } while (0 < iVar4);
  if (pgVar1->gcstate == '\0') {
LAB_005b9a54:
    uVar3 = (pgVar1->estimate / 100) * pgVar1->gcpause;
  }
  else if (pgVar1->gcdept < 0x400) {
    uVar3 = pgVar1->totalbytes + 0x400;
  }
  else {
    pgVar1->gcdept = pgVar1->gcdept - 0x400;
    uVar3 = pgVar1->totalbytes;
  }
  pgVar1->GCthreshold = uVar3;
  return;
}
