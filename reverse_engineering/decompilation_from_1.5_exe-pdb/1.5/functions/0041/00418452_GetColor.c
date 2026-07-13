/*
 * Entry: 00418452
 * Name: GetColor
 * Namespace: Global
 * Signature: long GetColor(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl GetColor(char *param_1)

{
  uint uVar1;
  
  uVar1 = Hash(param_1,0x811c9dc5);
  if (uVar1 < 0x40f480dd) {
    if (uVar1 == 0x40f480dc) {
      return DisplayInterface::colorRed;
    }
    if (uVar1 == 0x11decbc) {
      return DisplayInterface::colorGreen;
    }
    if (uVar1 == 0x5bf6449) {
      return DisplayInterface::colorYellow;
    }
    if (uVar1 == 0x23dbfbcf) {
      return DisplayInterface::colorDkRed;
    }
    if (uVar1 == 0x3450d0d4) {
      return DisplayInterface::colorDkBlue;
    }
    if (uVar1 == 0x3657edc3) {
      return DisplayInterface::colorDkGrey;
    }
  }
  else {
    if (uVar1 == 0x568f4ba4) {
      return DisplayInterface::colorBlack;
    }
    if (uVar1 == 0x5960cc5b) {
      return DisplayInterface::colorDkGreen;
    }
    if (uVar1 == 0x7de4f740) {
      return DisplayInterface::colorDkYellow;
    }
    if (uVar1 == 0x82fbf5cd) {
      return DisplayInterface::colorBlue;
    }
    if (uVar1 == 0xb29019a6) {
      return DisplayInterface::colorGrey;
    }
  }
  return DisplayInterface::colorWhite;
}
