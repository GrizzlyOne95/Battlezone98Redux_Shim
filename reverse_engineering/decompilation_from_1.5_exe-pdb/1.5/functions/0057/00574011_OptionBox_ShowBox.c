/*
 * Entry: 00574011
 * Name: OptionBox::ShowBox
 * Namespace: OptionBox
 * Signature: int ShowBox(OptionBox * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall OptionBox::ShowBox(OptionBox *this,int param_1)

{
  int iVar1;
  
  if (this->nBoxVisible == 0) {
    iVar1 = 1;
    this->nBoxVisible = 1;
    this->dataBox->nTextVisible = 1;
    if (param_1 != 0) {
      UpdateOptionBox(this);
    }
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}
