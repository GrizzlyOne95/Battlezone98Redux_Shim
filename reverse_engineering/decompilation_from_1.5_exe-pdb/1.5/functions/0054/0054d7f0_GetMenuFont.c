/*
 * Entry: 0054d7f0
 * Name: GetMenuFont
 * Namespace: Global
 * Signature: HFONT__ * GetMenuFont(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HFONT__ * __cdecl GetMenuFont(long param_1)

{
  uint uVar1;
  int iVar2;
  HFONT__ *pHVar3;
  
  uVar1 = param_1 & 0x3ff;
  if (uVar1 < 0x21) {
    if (uVar1 == 0x20) {
      return mInfo.checkboxFont;
    }
    if (uVar1 == 1) {
      return mInfo.titleFont;
    }
    if ((uVar1 == 2) || (uVar1 == 4)) {
      return mInfo.yesNoFont;
    }
    if (uVar1 == 8) goto LAB_0054d847;
    iVar2 = uVar1 - 0x10;
  }
  else {
    if (uVar1 == 0x40) goto LAB_0054d847;
    if ((uVar1 == 0x80) || (uVar1 == 0x100)) {
      return mInfo.sliderFont;
    }
    iVar2 = uVar1 - 0x200;
  }
  if (iVar2 != 0) {
    return (HFONT__ *)0x0;
  }
LAB_0054d847:
  pHVar3 = mInfo.itemFontSmall;
  if ((param_1 & 0x400U) == 0) {
    pHVar3 = mInfo.itemFont;
  }
  return pHVar3;
}
