/*
 * Entry: 00570320
 * Name: TextLabel::DrawLabelText
 * Namespace: TextLabel
 * Signature: int DrawLabelText(TextLabel * this, HDC__ * param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall TextLabel::DrawLabelText(TextLabel *this,HDC__ *param_1,char *param_2,int param_3)

{
  HGDIOBJ pvVar1;
  HDC hdc;
  HGDIOBJ h;
  
  if (param_3 == 0) {
    if (hCurrentBackground == (HBITMAP__ *)0x0) {
      return 0;
    }
    hdc = CreateCompatibleDC((HDC)param_1);
    pvVar1 = SelectObject(hdc,hCurrentBackground);
    DrawTransparentBitmap
              (param_1,this->hTextBack,(this->labelRect).left,(this->labelRect).top,0,(HDC__ *)hdc);
    h = SelectObject((HDC)param_1,this->hTextFont);
    SetBkMode((HDC)param_1,1);
    SetTextColor((HDC)param_1,this->textColor);
    if (this->nTextVisible != 0) {
      if (param_2 == (char *)0x0) {
        param_2 = this->textData;
      }
      DrawTextExA((HDC)param_1,param_2,-1,(LPRECT)&this->labelRect,this->nFormatType,
                  (LPDRAWTEXTPARAMS)0x0);
    }
    SelectObject(hdc,pvVar1);
    DeleteObject(hdc);
    if (h != (HGDIOBJ)0x0) {
      SelectObject((HDC)param_1,h);
    }
  }
  else {
    DrawTransparentBitmap
              (param_1,this->hTextBack,(this->labelRect).left,(this->labelRect).top,0,(HDC__ *)0x0);
    pvVar1 = SelectObject((HDC)param_1,this->hTextFont);
    SetBkMode((HDC)param_1,1);
    SetTextColor((HDC)param_1,this->textColor);
    if (this->nTextVisible != 0) {
      if (param_2 == (char *)0x0) {
        param_2 = this->textData;
      }
      DrawTextExA((HDC)param_1,param_2,-1,(LPRECT)&this->labelRect,this->nFormatType,
                  (LPDRAWTEXTPARAMS)0x0);
    }
    if (pvVar1 != (HGDIOBJ)0x0) {
      SelectObject((HDC)param_1,pvVar1);
    }
  }
  hButtonFont = (HFONT__ *)0x0;
  return 1;
}
