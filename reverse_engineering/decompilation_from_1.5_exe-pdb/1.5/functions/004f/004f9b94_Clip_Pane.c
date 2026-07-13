/*
 * Entry: 004f9b94
 * Name: Clip_Pane
 * Namespace: Global
 * Signature: long Clip_Pane(PANE * param_1, PANE * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Clip_Pane(PANE *param_1,PANE *param_2)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  uint uVar4;
  
  iVar1 = param_2->x0;
  uVar2 = ((((param_1->y0 - param_2->y1) - 1U >> 1 & 0x40000000 |
            param_1->y0 - param_2->y0 & 0x80000003U) >> 1 |
           (param_1->x0 - param_2->x1) - 1U & 0x80000001) >> 1 | param_1->x0 - iVar1 & 0x80000000U)
          ^ 0x50000000;
  uVar4 = ((((param_1->y1 - param_2->y1) - 1U >> 1 & 0x40000000 |
            param_1->y1 - param_2->y0 & 0x80000003U) >> 1 |
           (param_1->x1 - param_2->x1) - 1U & 0x80000001) >> 1 | param_1->x1 - iVar1 & 0x80000000U)
          ^ 0x50000000;
  if ((uVar2 & uVar4) == 0) {
    if (uVar4 == 0 && uVar2 == 0) {
      lVar3 = 0;
    }
    else {
      if ((uVar2 & 0x80000000) != 0) {
        param_1->x0 = iVar1;
      }
      if ((uVar2 & 0x20000000) != 0) {
        param_1->y0 = param_2->y0;
      }
      if ((uVar4 & 0x40000000) != 0) {
        param_1->x1 = param_2->x1;
      }
      if ((uVar4 & 0x10000000) != 0) {
        param_1->y1 = param_2->y1;
      }
      lVar3 = 1;
    }
  }
  else {
    lVar3 = -1;
  }
  return lVar3;
}
