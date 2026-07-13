/*
 * Entry: 0056fd44
 * Name: LabelButton::CheckRollOver
 * Namespace: LabelButton
 * Signature: int CheckRollOver(LabelButton * this, int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall LabelButton::CheckRollOver(LabelButton *this,int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = check_roll_over(&this->buttonRect,param_1,param_2);
  return iVar1;
}
