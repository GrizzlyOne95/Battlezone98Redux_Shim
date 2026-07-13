/*
 * Entry: 00571fdf
 * Name: SetNetworkFont
 * Namespace: Global
 * Signature: void SetNetworkFont(HWND__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetNetworkFont(HWND__ *param_1)

{
  char *pcVar1;
  int iVar2;
  HDC hdc;
  
  iVar2 = IsJapanese();
  if (((iVar2 != 0) || (iVar2 = GetScreenDPI(), iVar2 != 0x60)) && (param_1 != (HWND__ *)0x0)) {
    GetLangIni();
    if (netFont == (HFONT__ *)0x0) {
      hdc = GetDC((HWND)param_1);
      nDesiredHeight = defaultFontSize1;
      iVar2 = 0;
      do {
        pcVar1 = defaultFont + iVar2;
        desiredFont[iVar2] = *pcVar1;
        iVar2 = iVar2 + 1;
      } while (*pcVar1 != '\0');
      EnumFontsA(hdc,desiredFont,EnumButtonFontsProc,2);
      netFont = hButtonFont;
      hButtonFont = (HFONT__ *)0x0;
      ReleaseDC((HWND)param_1,hdc);
    }
    SendMessageA((HWND)param_1,0x30,(WPARAM)netFont,1);
  }
  return;
}
