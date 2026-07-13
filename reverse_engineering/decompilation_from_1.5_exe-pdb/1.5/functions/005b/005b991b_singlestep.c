/*
 * Entry: 005b991b
 * Name: singlestep
 * Namespace: Global
 * Signature: int singlestep(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl singlestep(lua_State *param_1)

{
  uchar uVar1;
  global_State *pgVar2;
  uint uVar3;
  lua_State *in_EAX;
  GCObject **ppGVar4;
  int iVar5;
  lua_State *unaff_EBP;
  lua_State *unaff_EDI;
  
  pgVar2 = in_EAX->l_G;
  uVar1 = pgVar2->gcstate;
  if (uVar1 == '\0') {
    markroot(unaff_EDI);
  }
  else if (uVar1 == '\x01') {
    if (pgVar2->gray != (GCObject *)0x0) {
      iVar5 = propagatemark((global_State *)param_1);
      return iVar5;
    }
    atomic(unaff_EDI);
  }
  else {
    if (uVar1 == '\x02') {
      iVar5 = pgVar2->sweepstrgc;
      ppGVar4 = (pgVar2->strt).hash;
      uVar3 = pgVar2->totalbytes;
      pgVar2->sweepstrgc = iVar5 + 1;
      sweeplist(in_EAX,ppGVar4 + iVar5,0xfffffffd);
      if ((pgVar2->strt).size <= pgVar2->sweepstrgc) {
        pgVar2->gcstate = '\x03';
      }
      pgVar2->estimate = pgVar2->estimate + (pgVar2->totalbytes - uVar3);
      return 10;
    }
    if (uVar1 == '\x03') {
      uVar3 = pgVar2->totalbytes;
      ppGVar4 = sweeplist(in_EAX,pgVar2->sweepgc,0x28);
      pgVar2->sweepgc = ppGVar4;
      if (*ppGVar4 == (GCObject *)0x0) {
        checkSizes(unaff_EBP);
        pgVar2->gcstate = '\x04';
      }
      pgVar2->estimate = pgVar2->estimate + (pgVar2->totalbytes - uVar3);
      return 400;
    }
    if (uVar1 == '\x04') {
      if (pgVar2->tmudata != (GCObject *)0x0) {
        GCTM(unaff_EDI);
        if (100 < pgVar2->estimate) {
          pgVar2->estimate = pgVar2->estimate - 100;
        }
        return 100;
      }
      pgVar2->gcstate = '\0';
      pgVar2->gcdept = 0;
    }
  }
  return 0;
}
