/*
 * Entry: 00573f95
 * Name: OptionBox::OptionBox
 * Namespace: OptionBox
 * Signature: OptionBox * OptionBox(OptionBox * this, HWND__ * param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OptionBox * __thiscall
OptionBox::OptionBox
          (OptionBox *this,HWND__ *param_1,int param_2,int param_3,int param_4,int param_5,
          int param_6)

{
  TextLabel *pTVar1;
  
  this->nOptionMode = 0;
  this->hParentHwnd = param_1;
  this->nItemCount = param_2;
  nDesiredHeight = defaultFontSize1;
  this->nBoxVisible = 1;
  pTVar1 = operator_new(0x128);
  if (pTVar1 == (TextLabel *)0x0) {
    pTVar1 = (TextLabel *)0x0;
  }
  else {
    pTVar1 = TextLabel::TextLabel(pTVar1,param_1,"NULL",param_3,param_4,param_5,param_6,0);
  }
  this->dataBox = pTVar1;
  (this->optionRect).left = param_3;
  (this->optionRect).top = param_4;
  (this->optionRect).bottom = param_4 + param_6;
  (this->optionRect).right = param_3 + param_5;
  return this;
}
