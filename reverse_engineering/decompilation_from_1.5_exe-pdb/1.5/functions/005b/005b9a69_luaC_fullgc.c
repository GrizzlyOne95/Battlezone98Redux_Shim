/*
 * Entry: 005b9a69
 * Name: luaC_fullgc
 * Namespace: Global
 * Signature: void luaC_fullgc(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaC_fullgc(lua_State *param_1)

{
  global_State *pgVar1;
  lua_State *unaff_EDI;
  
  pgVar1 = param_1->l_G;
  if (pgVar1->gcstate < 2) {
    pgVar1->sweepstrgc = 0;
    pgVar1->sweepgc = &pgVar1->rootgc;
    pgVar1->gray = (GCObject *)0x0;
    pgVar1->grayagain = (GCObject *)0x0;
    pgVar1->weak = (GCObject *)0x0;
    pgVar1->gcstate = '\x02';
  }
  while (pgVar1->gcstate != '\x04') {
    singlestep(unaff_EDI);
  }
  markroot(unaff_EDI);
  while (pgVar1->gcstate != '\0') {
    singlestep(unaff_EDI);
  }
  pgVar1->GCthreshold = (pgVar1->estimate / 100) * pgVar1->gcpause;
  return;
}
