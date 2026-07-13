/*
 * Entry: 00571bcc
 * Name: TextLabel::DrawLabelText
 * Namespace: TextLabel
 * Signature: int DrawLabelText(TextLabel * this, char * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall TextLabel::DrawLabelText(TextLabel *this,char *param_1,int param_2)

{
  HDC hDC;
  int iVar1;
  
  hDC = GetDC((HWND)this->hParentHwnd);
  iVar1 = DrawLabelText(this,(HDC__ *)hDC,param_1,param_2);
  ReleaseDC((HWND)this->hParentHwnd,hDC);
  return iVar1;
}
