/*
 * Entry: 005717d4
 * Name: OptionBox::UpdateOptionBox
 * Namespace: OptionBox
 * Signature: int UpdateOptionBox(OptionBox * this, HDC__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall OptionBox::UpdateOptionBox(OptionBox *this,HDC__ *param_1)

{
  int iVar1;
  
  if (this->nBoxVisible == 0) {
    iVar1 = 0;
  }
  else if (this->nItemCount == 0) {
    iVar1 = -1;
  }
  else {
    TextLabel::SetLabelText(this->dataBox,this->itemList[this->nOptionMode].cOptionName);
    TextLabel::DrawLabelText(this->dataBox,param_1,(char *)0x0,0);
    iVar1 = this->itemList[this->nOptionMode].nReturnNum;
  }
  return iVar1;
}
