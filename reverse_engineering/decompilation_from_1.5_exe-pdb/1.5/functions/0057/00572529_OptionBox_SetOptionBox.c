/*
 * Entry: 00572529
 * Name: OptionBox::SetOptionBox
 * Namespace: OptionBox
 * Signature: int SetOptionBox(OptionBox * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall OptionBox::SetOptionBox(OptionBox *this,int param_1)

{
  int iVar1;
  
  if (((this->nItemCount == 0) || (this->nItemCount < param_1)) || (0x32 < param_1)) {
    iVar1 = -1;
  }
  else {
    this->nOptionMode = param_1;
    TextLabel::SetLabelText(this->dataBox,this->itemList[param_1].cOptionName);
    TextLabel::DrawLabelText(this->dataBox,(char *)0x0,0);
    iVar1 = this->itemList[param_1].nReturnNum;
  }
  return iVar1;
}
