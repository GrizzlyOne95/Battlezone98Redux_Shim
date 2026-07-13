/*
 * Entry: 004c3a30
 * Name: AdjustPositions
 * Namespace: Global
 * Signature: void AdjustPositions(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AdjustPositions(void)

{
  tagRECT *ptVar1;
  tagPOINT *ptVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  long *plVar6;
  uint uVar7;
  int local_8;
  
  if (firstTime) {
    firstTime = false;
    iVar3 = IsJapanese();
    if (iVar3 != 0) {
      iVar4 = GetINIInt("Config","MenuGap",2,"lang.ini");
      local_8 = 0xf;
      uVar7 = 0;
      plVar6 = &MODE_BUTTON_RECT[0].top;
      iVar3 = iVar4 + 9;
      do {
        if (9 < uVar7) {
          local_8 = local_8 + 5;
        }
        ((tagRECT *)(plVar6 + -1))->left = 10;
        iVar5 = local_8 + iVar3;
        *plVar6 = iVar5;
        plVar6[2] = iVar5 + 8;
        MODE_BUTTON_POS[uVar7].x = 0x25;
        MODE_BUTTON_POS[uVar7].y = (iVar5 + iVar5 + 8) / 2;
        plVar6[1] = 0x9c;
        ptVar2 = CANCEL_BUTTON_POS;
        ptVar1 = CANCEL_BUTTON_RECT;
        uVar7 = uVar7 + 1;
        iVar3 = iVar3 + iVar4 + 9;
        plVar6 = plVar6 + 4;
      } while (uVar7 < 0xd);
      plVar6 = &CANCEL_BUTTON_RECT->top;
      CANCEL_BUTTON_RECT->left = MODE_BUTTON_RECT[0xc].left;
      *plVar6 = MODE_BUTTON_RECT[0xc].top;
      ptVar1->right = MODE_BUTTON_RECT[0xc].right;
      ptVar1->bottom = MODE_BUTTON_RECT[0xc].bottom;
      ptVar2->x = MODE_BUTTON_POS[0xc].x;
      ptVar2->y = MODE_BUTTON_POS[0xc].y;
      CONTROL_PANEL_RECT.bottom = ptVar1->bottom;
    }
  }
  return;
}
