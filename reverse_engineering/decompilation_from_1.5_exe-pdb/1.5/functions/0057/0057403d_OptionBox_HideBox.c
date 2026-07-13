/*
 * Entry: 0057403d
 * Name: OptionBox::HideBox
 * Namespace: OptionBox
 * Signature: int HideBox(OptionBox * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall OptionBox::HideBox(OptionBox *this,int param_1)

{
  int iVar1;
  
  if (this->nBoxVisible == 0) {
    iVar1 = 0;
  }
  else {
    this->dataBox->nTextVisible = 0;
    if (param_1 != 0) {
      UpdateOptionBox(this);
    }
    this->nBoxVisible = 0;
    iVar1 = 1;
  }
  return iVar1;
}
