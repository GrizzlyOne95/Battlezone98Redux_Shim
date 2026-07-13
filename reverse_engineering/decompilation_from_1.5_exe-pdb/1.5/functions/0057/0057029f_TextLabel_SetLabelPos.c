/*
 * Entry: 0057029f
 * Name: TextLabel::SetLabelPos
 * Namespace: TextLabel
 * Signature: int SetLabelPos(TextLabel * this, int param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall
TextLabel::SetLabelPos(TextLabel *this,int param_1,int param_2,int param_3,int param_4)

{
  long *plVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = (this->labelRect).left;
  plVar1 = &(this->labelRect).top;
  iVar3 = *plVar1;
  (this->labelRect).left = param_1;
  *plVar1 = param_2;
  if (param_3 == 0) {
    (this->labelRect).right = ((this->labelRect).right - iVar2) + param_1;
  }
  else {
    (this->labelRect).right = param_1 + param_3;
  }
  if (param_4 == 0) {
    (this->labelRect).bottom = ((this->labelRect).bottom - iVar3) + param_2;
  }
  else {
    (this->labelRect).bottom = param_2 + param_4;
  }
  return 1;
}
