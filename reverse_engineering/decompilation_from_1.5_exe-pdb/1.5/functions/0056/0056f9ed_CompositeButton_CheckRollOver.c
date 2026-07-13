/*
 * Entry: 0056f9ed
 * Name: CompositeButton::CheckRollOver
 * Namespace: CompositeButton
 * Signature: int CheckRollOver(CompositeButton * this, int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall CompositeButton::CheckRollOver(CompositeButton *this,int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = check_roll_over(&this->buttonRect,param_1,param_2);
  return iVar1;
}
