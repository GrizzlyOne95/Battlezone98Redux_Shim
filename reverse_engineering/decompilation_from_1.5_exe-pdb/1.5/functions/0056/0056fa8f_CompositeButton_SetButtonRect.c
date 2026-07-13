/*
 * Entry: 0056fa8f
 * Name: CompositeButton::SetButtonRect
 * Namespace: CompositeButton
 * Signature: void SetButtonRect(CompositeButton * this, int param_1, int param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
CompositeButton::SetButtonRect
          (CompositeButton *this,int param_1,int param_2,int param_3,int param_4,int param_5)

{
  long *plVar1;
  
  if (param_1 == 0) {
    (this->buttonRect).left = (this->buttonRect).left + param_2;
    plVar1 = &(this->buttonRect).top;
    *plVar1 = *plVar1 + param_3;
    plVar1 = &(this->buttonRect).right;
    *plVar1 = *plVar1 + param_4;
    plVar1 = &(this->buttonRect).bottom;
    *plVar1 = *plVar1 + param_5;
  }
  else {
    (this->buttonRect).left = param_2;
    (this->buttonRect).top = param_3;
    (this->buttonRect).right = param_4;
    (this->buttonRect).bottom = param_5;
  }
  return;
}
