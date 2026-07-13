/*
 * Entry: 0056f633
 * Name: ShellBitmap::ShellBitmap
 * Namespace: ShellBitmap
 * Signature: ShellBitmap * ShellBitmap(ShellBitmap * this, char * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ShellBitmap * __thiscall
ShellBitmap::ShellBitmap(ShellBitmap *this,char *param_1,int param_2,int param_3)

{
  void **ppvVar1;
  tagBITMAPINFO **pptVar2;
  tagBITMAPINFO *ptVar3;
  HPALETTE pHVar4;
  int iVar5;
  void **unaff_EDI;
  char *pcVar6;
  tagRGBQUAD local_80c;
  BYTE aBStack_808 [1018];
  undefined1 local_40e;
  LOGPALETTE local_40c;
  BYTE aBStack_404 [1020];
  HDC local_8;
  
  local_40c.palVersion = 0x300;
  local_40c.palNumEntries = 0x100;
  memset(local_40c.palPalEntry,0,0x400);
  local_8 = GetDC((HWND)shell_hwnd);
  ppvVar1 = &this->bmBits;
  this->pBitmapPal = (HPALETTE__ *)0x0;
  *ppvVar1 = (void *)0x0;
  pptVar2 = &this->bmInfo;
  *pptVar2 = (tagBITMAPINFO *)0x0;
  iVar5 = 1;
  this->nScanLine = 3;
  local_40c.palPalEntry[0].peFlags = '\0';
  do {
    local_40c.palPalEntry[iVar5].peFlags = '\0';
    iVar5 = iVar5 + 1;
  } while (iVar5 < 0x100);
  forceBitmap24 = 1;
  iVar5 = Read_Shell_Bitmap(param_1,&local_80c,pptVar2,ppvVar1);
  if (iVar5 == 0) {
    pcVar6 = "BattleZone (ShellBitmap Class) Bitmap Read Error!\n";
    Trace("BattleZone (ShellBitmap Class) Bitmap Read Error!\n");
    Default_Shell_Bitmap((tagRGBQUAD *)ppvVar1,(tagBITMAPINFO **)pcVar6,unaff_EDI);
  }
  local_40c.palPalEntry[0].peRed = local_80c.rgbRed;
  local_40c.palPalEntry[0].peGreen = local_80c.rgbGreen;
  local_40c.palPalEntry[0].peBlue = local_80c.rgbBlue;
  aBStack_404[0x3f8] = local_40e;
  aBStack_404[0x3f9] = aBStack_808[0x3f9];
  aBStack_404[0x3fa] = aBStack_808[0x3f8];
  local_40c.palPalEntry[0].peFlags = '\x04';
  aBStack_404[0x3fb] = 4;
  iVar5 = 0;
  do {
    aBStack_404[iVar5] = aBStack_808[iVar5 + 2];
    aBStack_404[iVar5 + 1] = aBStack_808[iVar5 + 1];
    aBStack_404[iVar5 + 2] = aBStack_808[iVar5];
    aBStack_404[iVar5 + 3] = '\x04';
    iVar5 = iVar5 + 4;
  } while (iVar5 < 0x3f8);
  pHVar4 = CreatePalette(&local_40c);
  this->pBitmapPal = (HPALETTE__ *)pHVar4;
  if (pHVar4 == (HPALETTE)0x0) {
    DEBUG_systemError("BattleZone (ShellBitmap) Create Palette Error!");
  }
  ptVar3 = *pptVar2;
  (this->bmRect).left = param_2;
  (this->bmRect).top = param_3;
  (this->bmRect).right = (ptVar3->bmiHeader).biWidth + param_2;
  (this->bmRect).bottom = (ptVar3->bmiHeader).biHeight + param_3;
  ReleaseDC((HWND)shell_hwnd,local_8);
  return this;
}
