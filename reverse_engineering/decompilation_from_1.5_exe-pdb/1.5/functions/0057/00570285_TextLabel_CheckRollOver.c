/*
 * Entry: 00570285
 * Name: TextLabel::CheckRollOver
 * Namespace: TextLabel
 * Signature: int CheckRollOver(TextLabel * this, int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall TextLabel::CheckRollOver(TextLabel *this,int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = check_roll_over(&this->labelRect,param_1,param_2);
  return iVar1;
}
