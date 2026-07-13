/*
 * Entry: 0043b0f9
 * Name: Misn17Mission::AddObject
 * Namespace: Misn17Mission
 * Signature: void AddObject(Misn17Mission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn17Mission::AddObject(Misn17Mission *this,int param_1)

{
  bool bVar1;
  int *piVar2;
  
  if (((this->field18_0x110)._s_0.art1 == 0) && (bVar1 = IsOdf(param_1,"avartl"), bVar1)) {
    (this->field18_0x110)._s_0.art1 = param_1;
  }
  else {
    piVar2 = &(this->field18_0x110)._s_0.art2;
    if ((((*piVar2 == 0) && (bVar1 = IsOdf(param_1,"avartl"), bVar1)) ||
        ((piVar2 = &(this->field18_0x110)._s_0.art3, *piVar2 == 0 &&
         (bVar1 = IsOdf(param_1,"avartl"), bVar1)))) ||
       ((piVar2 = &(this->field18_0x110)._s_0.art4, *piVar2 == 0 &&
        (bVar1 = IsOdf(param_1,"avartl"), bVar1)))) {
      *piVar2 = param_1;
    }
    else {
      piVar2 = &(this->field18_0x110)._s_0.art5;
      if ((*piVar2 == 0) && (bVar1 = IsOdf(param_1,"avartl"), bVar1)) {
        *piVar2 = param_1;
      }
    }
  }
  return;
}
