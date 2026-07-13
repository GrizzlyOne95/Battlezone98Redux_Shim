/*
 * Entry: 005725e0
 * Name: OptionBox::ToggleOptionBox
 * Namespace: OptionBox
 * Signature: int ToggleOptionBox(OptionBox * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall OptionBox::ToggleOptionBox(OptionBox *this)

{
  if (this->nItemCount == 0) {
    return -1;
  }
  this->nOptionMode = this->nOptionMode + 1;
  if (this->nOptionMode == this->nItemCount) {
    this->nOptionMode = 0;
  }
  TextLabel::SetLabelText(this->dataBox,this->itemList[this->nOptionMode].cOptionName);
  TextLabel::DrawLabelText(this->dataBox,(char *)0x0,0);
  return this->itemList[this->nOptionMode].nReturnNum;
}
