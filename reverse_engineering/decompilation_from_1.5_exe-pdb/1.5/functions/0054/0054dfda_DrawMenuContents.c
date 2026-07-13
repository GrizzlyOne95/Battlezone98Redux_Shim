/*
 * Entry: 0054dfda
 * Name: DrawMenuContents
 * Namespace: Global
 * Signature: void DrawMenuContents(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DrawMenuContents(void)

{
  tagRECT (*patVar1) [2];
  MENU_ITEM_LOC MVar2;
  tagRECT *ptVar3;
  _menu *p_Var4;
  HGDIOBJ pvVar5;
  int iVar6;
  _menu_item *p_Var7;
  int local_8;
  
  p_Var4 = mInfo.curMenu;
  Graphic_Buffer_Clear(&mInfo.textGB,0xff);
  pvVar5 = GetStockObject(2);
  SelectObject((HDC)mInfo.dc,pvVar5);
  pvVar5 = SelectObject((HDC)mInfo.dc,mInfo.hBitmap);
  RealizePalette((HDC)mInfo.dc);
  SetTextColor((HDC)mInfo.dc,0x2ffffff);
  SetBkColor((HDC)mInfo.dc,0x20000f0);
  SetBkMode((HDC)mInfo.dc,1);
  DrawCheckNum((mInfo.curMenu)->checkNum);
  local_8 = 0;
  p_Var7 = p_Var4->items;
  if (0 < p_Var4->numItems) {
    do {
      MVar2 = p_Var7->itemLoc;
      patVar1 = menuItemLocs + MVar2;
      (p_Var7->itemRect).left = (*patVar1)[0].left;
      (p_Var7->itemRect).top = (*patVar1)[0].top;
      (p_Var7->itemRect).right = (*patVar1)[0].right;
      (p_Var7->itemRect).bottom = (*patVar1)[0].bottom;
      ptVar3 = menuItemLocs[MVar2];
      (p_Var7->choiceRect).left = ptVar3[1].left;
      (p_Var7->choiceRect).top = ptVar3[1].top;
      (p_Var7->choiceRect).right = ptVar3[1].right;
      (p_Var7->choiceRect).bottom = ptVar3[1].bottom;
      DrawMenuObject(p_Var7,(uint)(local_8 == (mInfo.curMenu)->curItem));
      local_8 = local_8 + 1;
      p_Var7 = p_Var7 + 1;
    } while (local_8 < p_Var4->numItems);
  }
  GdiFlush();
  iVar6 = (*Device.VideoMode.LockBuffer)(&Device);
  if (iVar6 != 0) {
    Graphic_Copy_Bitmap(&Device.Viewport,&mInfo.bgGB,mInfo.menuLoc.left,mInfo.menuLoc.top,
                        SOLID_PIXELS);
    Graphic_Copy_Bitmap(&Device.Viewport,&mInfo.textGB,mInfo.menuLoc.left,mInfo.menuLoc.top,
                        TRANSPARENT_PIXELS);
    (*Device.VideoMode.UnlockBuffer)(&Device);
  }
  SelectObject((HDC)mInfo.dc,pvVar5);
  (*Device.Refresh.Blit)(&Device);
  return;
}
