/*
 * Entry: 00572575
 * Name: OptionBox::SetCurrentValue
 * Namespace: OptionBox
 * Signature: int SetCurrentValue(OptionBox * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall OptionBox::SetCurrentValue(OptionBox *this,int param_1)

{
  int iVar1;
  int *piVar2;
  
  if (this->nItemCount == 0) {
    iVar1 = -1;
  }
  else {
    iVar1 = 0;
    piVar2 = &this->itemList[0].nReturnNum;
    do {
      if (this->nItemCount <= iVar1) break;
      if (*piVar2 == param_1) {
        this->nOptionMode = iVar1;
        break;
      }
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 0x41;
    } while (iVar1 < 0x32);
    TextLabel::SetLabelText(this->dataBox,this->itemList[this->nOptionMode].cOptionName);
    TextLabel::DrawLabelText(this->dataBox,(char *)0x0,0);
    iVar1 = this->itemList[this->nOptionMode].nReturnNum;
  }
  return iVar1;
}
