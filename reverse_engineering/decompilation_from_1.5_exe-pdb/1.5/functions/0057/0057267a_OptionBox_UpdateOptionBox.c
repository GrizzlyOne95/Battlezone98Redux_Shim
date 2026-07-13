/*
 * Entry: 0057267a
 * Name: OptionBox::UpdateOptionBox
 * Namespace: OptionBox
 * Signature: int UpdateOptionBox(OptionBox * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall OptionBox::UpdateOptionBox(OptionBox *this)

{
  if (this->nBoxVisible == 0) {
    return 0;
  }
  if (this->nItemCount == 0) {
    return -1;
  }
  TextLabel::SetLabelText(this->dataBox,this->itemList[this->nOptionMode].cOptionName);
  TextLabel::DrawLabelText(this->dataBox,(char *)0x0,0);
  return this->itemList[this->nOptionMode].nReturnNum;
}
