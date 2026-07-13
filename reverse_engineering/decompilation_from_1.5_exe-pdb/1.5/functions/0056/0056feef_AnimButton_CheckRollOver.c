/*
 * Entry: 0056feef
 * Name: AnimButton::CheckRollOver
 * Namespace: AnimButton
 * Signature: int CheckRollOver(AnimButton * this, int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall AnimButton::CheckRollOver(AnimButton *this,int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = check_roll_over(&this->buttonRect,param_1,param_2);
  return iVar1;
}
