/*
 * Entry: 0041e703
 * Name: Misn03Mission::AddObject
 * Namespace: Misn03Mission
 * Signature: void AddObject(Misn03Mission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn03Mission::AddObject(Misn03Mission *this,int param_1)

{
  bool bVar1;
  int *piVar2;
  
  if (((this->field18_0xdc)._s_0.avturret1 == 0) && (bVar1 = IsOdf(param_1,"avturr"), bVar1)) {
    (this->field18_0xdc)._s_0.avturret1 = param_1;
  }
  else {
    piVar2 = &(this->field18_0xdc)._s_0.avturret2;
    if ((((((*piVar2 == 0) && (bVar1 = IsOdf(param_1,"avturr"), bVar1)) ||
          ((piVar2 = &(this->field18_0xdc)._s_0.avturret3, *piVar2 == 0 &&
           (bVar1 = IsOdf(param_1,"avturr"), bVar1)))) ||
         ((piVar2 = &(this->field18_0xdc)._s_0.avturret4, *piVar2 == 0 &&
          (bVar1 = IsOdf(param_1,"avturr"), bVar1)))) ||
        (((piVar2 = &(this->field18_0xdc)._s_0.avturret5, *piVar2 == 0 &&
          (bVar1 = IsOdf(param_1,"avturr"), bVar1)) ||
         ((((piVar2 = &(this->field18_0xdc)._s_0.avturret6, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"avturr"), bVar1)) ||
           ((piVar2 = &(this->field18_0xdc)._s_0.avturret7, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"avturr"), bVar1)))) ||
          ((piVar2 = &(this->field18_0xdc)._s_0.avturret8, *piVar2 == 0 &&
           (bVar1 = IsOdf(param_1,"avturr"), bVar1)))))))) ||
       (((piVar2 = &(this->field18_0xdc)._s_0.scav3, *piVar2 == 0 &&
         (bVar1 = IsOdf(param_1,"avscav"), bVar1)) ||
        (((piVar2 = &(this->field18_0xdc)._s_0.avturret9, *piVar2 == 0 &&
          (bVar1 = IsOdf(param_1,"avturr"), bVar1)) ||
         ((piVar2 = &(this->field18_0xdc)._s_0.avturret10, *piVar2 == 0 &&
          (bVar1 = IsOdf(param_1,"avturr"), bVar1)))))))) {
      *piVar2 = param_1;
    }
    else {
      piVar2 = &(this->field18_0xdc)._s_0.scav4;
      if (((*piVar2 == 0) && (bVar1 = IsOdf(param_1,"avscav"), bVar1)) ||
         ((piVar2 = &(this->field18_0xdc)._s_0.scav5, *piVar2 == 0 &&
          (bVar1 = IsOdf(param_1,"avscav"), bVar1)))) {
        *piVar2 = param_1;
      }
      else {
        piVar2 = &(this->field18_0xdc)._s_0.scav6;
        if ((*piVar2 == 0) && (bVar1 = IsOdf(param_1,"avscav"), bVar1)) {
          *piVar2 = param_1;
        }
      }
    }
  }
  return;
}
