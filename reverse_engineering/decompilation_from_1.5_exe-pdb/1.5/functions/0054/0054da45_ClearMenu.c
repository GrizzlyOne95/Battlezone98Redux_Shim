/*
 * Entry: 0054da45
 * Name: ClearMenu
 * Namespace: Global
 * Signature: void ClearMenu(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClearMenu(void)

{
  long lVar1;
  HGDIOBJ pvVar2;
  
  lVar1 = mInfo.returnVal;
  CloseMenu(mInfo.curMenu);
  Graphic_Buffer_Close(&mInfo.cmGB);
  EnableForceFeedback();
  if (mInfo.dc != (HDC__ *)0x0) {
    pvVar2 = GetStockObject(0xd);
    SelectObject((HDC)mInfo.dc,pvVar2);
    pvVar2 = GetStockObject(5);
    SelectObject((HDC)mInfo.dc,pvVar2);
  }
  if (mInfo.checkmark != (TEXTURE *)0x0) {
    UnlockRDItem("x1.map",0,0);
  }
  if (mInfo.titleFont != (HFONT__ *)0x0) {
    DeleteObject(mInfo.titleFont);
  }
  if (mInfo.yesNoFont != (HFONT__ *)0x0) {
    DeleteObject(mInfo.yesNoFont);
  }
  if (mInfo.itemFont != (HFONT__ *)0x0) {
    DeleteObject(mInfo.itemFont);
  }
  if (mInfo.itemFontSmall != (HFONT__ *)0x0) {
    DeleteObject(mInfo.itemFontSmall);
  }
  if (mInfo.checkboxFont != (HFONT__ *)0x0) {
    DeleteObject(mInfo.checkboxFont);
  }
  if (mInfo.sliderFont != (HFONT__ *)0x0) {
    DeleteObject(mInfo.sliderFont);
  }
  memset(&mInfo,0,0x104);
  mInfo.returnVal = lVar1;
  LockMouse();
  return;
}
