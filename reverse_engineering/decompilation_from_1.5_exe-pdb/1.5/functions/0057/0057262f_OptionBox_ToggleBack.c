/*
 * Entry: 0057262f
 * Name: OptionBox::ToggleBack
 * Namespace: OptionBox
 * Signature: int ToggleBack(OptionBox * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall OptionBox::ToggleBack(OptionBox *this)

{
  int *piVar1;
  
  if (this->nItemCount == 0) {
    return -1;
  }
  piVar1 = &this->nOptionMode;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 < 0) {
    this->nOptionMode = this->nItemCount;
  }
  TextLabel::SetLabelText(this->dataBox,this->itemList[this->nOptionMode].cOptionName);
  TextLabel::DrawLabelText(this->dataBox,(char *)0x0,0);
  return this->itemList[this->nOptionMode].nReturnNum;
}
