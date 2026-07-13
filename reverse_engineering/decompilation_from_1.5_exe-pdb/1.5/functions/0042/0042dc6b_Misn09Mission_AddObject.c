/*
 * Entry: 0042dc6b
 * Name: Misn09Mission::AddObject
 * Namespace: Misn09Mission
 * Signature: void AddObject(Misn09Mission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn09Mission::AddObject(Misn09Mission *this,int param_1)

{
  bool bVar1;
  int *piVar2;
  
  if (((this->field18_0xec)._s_0.cca1 == 0) && (bVar1 = IsOdf(param_1,"svturr"), bVar1)) {
    (this->field18_0xec)._s_0.cca1 = param_1;
  }
  else {
    piVar2 = &(this->field18_0xec)._s_0.cca2;
    if (((((((((*piVar2 == 0) && (bVar1 = IsOdf(param_1,"svturr"), bVar1)) ||
             ((piVar2 = &(this->field18_0xec)._s_0.cca3, *piVar2 == 0 &&
              (bVar1 = IsOdf(param_1,"svturr"), bVar1)))) ||
            ((piVar2 = &(this->field18_0xec)._s_0.cca4, *piVar2 == 0 &&
             (bVar1 = IsOdf(param_1,"svturr"), bVar1)))) ||
           ((piVar2 = &(this->field18_0xec)._s_0.cca5, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"svfigh"), bVar1)))) ||
          ((((piVar2 = &(this->field18_0xec)._s_0.cca6, *piVar2 == 0 &&
             (bVar1 = IsOdf(param_1,"svfigh"), bVar1)) ||
            ((piVar2 = &(this->field18_0xec)._s_0.cca7, *piVar2 == 0 &&
             (bVar1 = IsOdf(param_1,"svfigh"), bVar1)))) ||
           ((piVar2 = &(this->field18_0xec)._s_0.cca8, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"svfigh"), bVar1)))))) ||
         ((piVar2 = &(this->field18_0xec)._s_0.cca9, *piVar2 == 0 &&
          (bVar1 = IsOdf(param_1,"svtank"), bVar1)))) ||
        ((((piVar2 = &(this->field18_0xec)._s_0.cca0, *piVar2 == 0 &&
           (bVar1 = IsOdf(param_1,"svtank"), bVar1)) ||
          ((piVar2 = &(this->field18_0xec)._s_0.scav1, *piVar2 == 0 &&
           (bVar1 = IsOdf(param_1,"svscav"), bVar1)))) ||
         (((piVar2 = &(this->field18_0xec)._s_0.scav2, *piVar2 == 0 &&
           (bVar1 = IsOdf(param_1,"svscav"), bVar1)) ||
          ((piVar2 = &(this->field18_0xec)._s_0.scav3, *piVar2 == 0 &&
           (bVar1 = IsOdf(param_1,"svscav"), bVar1)))))))) ||
       (((piVar2 = &(this->field18_0xec)._s_0.nsdfgech1, *piVar2 == 0 &&
         (bVar1 = IsOdf(param_1,"avwalk"), bVar1)) ||
        ((piVar2 = &(this->field18_0xec)._s_0.ccatug, *piVar2 == 0 &&
         (bVar1 = IsOdf(param_1,"svhaul"), bVar1)))))) {
      *piVar2 = param_1;
    }
    else {
      piVar2 = &(this->field18_0xec)._s_0.avsilo;
      if ((*piVar2 == 0) && (bVar1 = IsOdf(param_1,"absilo"), bVar1)) {
        *piVar2 = param_1;
      }
    }
  }
  return;
}
