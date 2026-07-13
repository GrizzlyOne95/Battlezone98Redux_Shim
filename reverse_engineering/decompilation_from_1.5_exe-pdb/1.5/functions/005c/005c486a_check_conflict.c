/*
 * Entry: 005c486a
 * Name: check_conflict
 * Namespace: Global
 * Signature: void check_conflict(LexState * param_1, LHS_assign * param_2, expdesc * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl check_conflict(LexState *param_1,LHS_assign *param_2,expdesc *param_3)

{
  FuncState *pFVar1;
  int iVar2;
  bool bVar3;
  int *in_EAX;
  int in_ECX;
  int in_EDX;
  
  pFVar1 = *(FuncState **)(in_ECX + 0x30);
  iVar2 = pFVar1->freereg;
  bVar3 = false;
  if (in_EAX != (int *)0x0) {
    do {
      if (in_EAX[2] == 9) {
        if (in_EAX[4] == *(int *)(in_EDX + 8)) {
          bVar3 = true;
          in_EAX[4] = iVar2;
        }
        if (in_EAX[5] == *(int *)(in_EDX + 8)) {
          bVar3 = true;
          in_EAX[5] = iVar2;
        }
      }
      in_EAX = (int *)*in_EAX;
    } while (in_EAX != (int *)0x0);
    if (bVar3) {
      luaK_codeABC(pFVar1,OP_MOVE,pFVar1->freereg,*(int *)(in_EDX + 8),0);
      luaK_reserveregs(pFVar1,1);
    }
  }
  return;
}
