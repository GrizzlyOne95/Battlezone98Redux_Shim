/*
 * Entry: 0048120d
 * Name: LinkCopy
 * Namespace: Global
 * Signature: void LinkCopy(_gas_object * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl LinkCopy(_gas_object *param_1)

{
  byte bVar1;
  _gas_object *p_Var2;
  int iVar3;
  int iVar4;
  GAS_CTRL *pGVar5;
  int iVar6;
  GAS_CTRL *pGVar7;
  CopyInfo *pCVar8;
  bool bVar9;
  
  iVar4 = freeCopy;
  for (p_Var2 = firstSound; p_Var2 != (_gas_object *)0x0; p_Var2 = p_Var2->next) {
    if (p_Var2 != param_1) {
      pGVar7 = &param_1->gc;
      pGVar5 = &p_Var2->gc;
      do {
        bVar1 = pGVar5->name[0];
        bVar9 = bVar1 < (byte)pGVar7->name[0];
        if (bVar1 != pGVar7->name[0]) {
LAB_00481249:
          iVar6 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
          goto LAB_0048124d;
        }
        if (bVar1 == 0) break;
        bVar1 = pGVar5->name[1];
        bVar9 = bVar1 < (byte)pGVar7->name[1];
        if (bVar1 != pGVar7->name[1]) goto LAB_00481249;
        pGVar5 = (GAS_CTRL *)(pGVar5->name + 2);
        pGVar7 = (GAS_CTRL *)(pGVar7->name + 2);
      } while (bVar1 != 0);
      iVar6 = 0;
LAB_0048124d:
      if (iVar6 == 0) break;
    }
  }
  param_1->count = freeCopy;
  if (iVar4 == -1) {
    Trace("LinkCopy out of copies\n");
  }
  else {
    freeCopy = copies[iVar4].next;
    freeCopies = freeCopies + -1;
    if (freeCopies < minFreeCopies) {
      minFreeCopies = freeCopies;
    }
    copies[iVar4].count = 0;
    copies[iVar4].go = param_1;
    if (p_Var2 == (_gas_object *)0x0) {
      copies[iVar4].prev = -1;
      copies[iVar4].next = -1;
    }
    else {
      iVar6 = p_Var2->count;
      iVar3 = copies[iVar6].next;
      if (iVar3 == -1) {
        pCVar8 = (CopyInfo *)0x0;
      }
      else {
        pCVar8 = copies + iVar3;
      }
      copies[iVar4].next = iVar3;
      copies[iVar4].prev = p_Var2->count;
      copies[iVar6].next = param_1->count;
      if (pCVar8 != (CopyInfo *)0x0) {
        pCVar8->prev = param_1->count;
      }
    }
  }
  return;
}
