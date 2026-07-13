/*
 * Entry: 0042f70d
 * Name: Misn10Mission::AddObject
 * Namespace: Misn10Mission
 * Signature: void AddObject(Misn10Mission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn10Mission::AddObject(Misn10Mission *this,int param_1)

{
  bool bVar1;
  int *piVar2;
  
  if (((this->field18_0xbc)._s_0.ccatug == 0) && (bVar1 = IsOdf(param_1,"svhaul"), bVar1)) {
    (this->field18_0xbc)._s_0.ccatug = param_1;
  }
  else {
    piVar2 = &(this->field18_0xbc)._s_0.ccaartil1;
    if (((((((*piVar2 == 0) && (bVar1 = IsOdf(param_1,"svartl"), bVar1)) ||
           ((piVar2 = &(this->field18_0xbc)._s_0.ccaartil2, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"svartl"), bVar1)))) ||
          ((piVar2 = &(this->field18_0xbc)._s_0.ccaartil3, *piVar2 == 0 &&
           (bVar1 = IsOdf(param_1,"svartl"), bVar1)))) ||
         (((piVar2 = &(this->field18_0xbc)._s_0.ccaturret1, *piVar2 == 0 &&
           (bVar1 = IsOdf(param_1,"svturr"), bVar1)) ||
          ((((piVar2 = &(this->field18_0xbc)._s_0.ccaturret2, *piVar2 == 0 &&
             (bVar1 = IsOdf(param_1,"svturr"), bVar1)) ||
            ((piVar2 = &(this->field18_0xbc)._s_0.ccaturret3, *piVar2 == 0 &&
             (bVar1 = IsOdf(param_1,"svturr"), bVar1)))) ||
           ((piVar2 = &(this->field18_0xbc)._s_0.ccafighter1, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"svfigh"), bVar1)))))))) ||
        ((piVar2 = &(this->field18_0xbc)._s_0.ccafighter2, *piVar2 == 0 &&
         (bVar1 = IsOdf(param_1,"svfigh"), bVar1)))) ||
       (((piVar2 = &(this->field18_0xbc)._s_0.ccatank1, *piVar2 == 0 &&
         (bVar1 = IsOdf(param_1,"svltnk"), bVar1)) ||
        ((piVar2 = &(this->field18_0xbc)._s_0.ccatank2, *piVar2 == 0 &&
         (bVar1 = IsOdf(param_1,"svltnk"), bVar1)))))) {
      *piVar2 = param_1;
    }
    else {
      piVar2 = &(this->field18_0xbc)._s_0.ccamuf;
      if ((*piVar2 == 0) && (bVar1 = IsOdf(param_1,"svmuf"), bVar1)) {
        *piVar2 = param_1;
      }
    }
  }
  return;
}
