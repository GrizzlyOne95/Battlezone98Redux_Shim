/*
 * Entry: 00571b60
 * Name: TextLabel::SetTextFont
 * Namespace: TextLabel
 * Signature: int SetTextFont(TextLabel * this, char * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall TextLabel::SetTextFont(TextLabel *this,char *param_1,int param_2)

{
  char cVar1;
  HDC hdc;
  int iVar2;
  
  if (this->hTextFont != (HFONT__ *)0x0) {
    DeleteObject(this->hTextFont);
  }
  hdc = GetDC((HWND)this->hParentHwnd);
  nDesiredHeight = param_2;
  iVar2 = (int)desiredFont - (int)param_1;
  do {
    cVar1 = *param_1;
    param_1[iVar2] = cVar1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  EnumFontsA(hdc,defaultFont,EnumButtonFontsProc,2);
  this->hTextFont = hButtonFont;
  ReleaseDC((HWND)this->hParentHwnd,hdc);
  return 1;
}
