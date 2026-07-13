/*
 * Entry: 00445f8c
 * Name: Misns7Mission::AddObject
 * Namespace: Misns7Mission
 * Signature: void AddObject(Misns7Mission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns7Mission::AddObject(Misns7Mission *this,int param_1)

{
  bool bVar1;
  int *piVar2;
  
  if (((this->field18_0x130)._s_0.avscav1 == 0) && (bVar1 = IsOdf(param_1,"bvscav"), bVar1)) {
    (this->field18_0x130)._s_0.avscav1 = param_1;
  }
  else {
    piVar2 = &(this->field18_0x130)._s_0.avscav2;
    if ((((((*piVar2 == 0) && (bVar1 = IsOdf(param_1,"bvscav"), bVar1)) ||
          ((piVar2 = &(this->field18_0x130)._s_0.avfight1, *piVar2 == 0 &&
           (bVar1 = IsOdf(param_1,"bvraz"), bVar1)))) ||
         ((piVar2 = &(this->field18_0x130)._s_0.avfight2, *piVar2 == 0 &&
          (bVar1 = IsOdf(param_1,"bvraz"), bVar1)))) ||
        (((((piVar2 = &(this->field18_0x130)._s_0.avtank1, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"bvtank"), bVar1)) ||
           ((((piVar2 = &(this->field18_0x130)._s_0.avtank2, *piVar2 == 0 &&
              (bVar1 = IsOdf(param_1,"bvtank"), bVar1)) ||
             ((piVar2 = &(this->field18_0x130)._s_0.avltnk1, *piVar2 == 0 &&
              (bVar1 = IsOdf(param_1,"bvltnk"), bVar1)))) ||
            ((piVar2 = &(this->field18_0x130)._s_0.avltnk2, *piVar2 == 0 &&
             (bVar1 = IsOdf(param_1,"bvltnk"), bVar1)))))) ||
          ((piVar2 = &(this->field18_0x130)._s_0.avgech, *piVar2 == 0 &&
           (bVar1 = IsOdf(param_1,"bvwalk"), bVar1)))) ||
         ((((piVar2 = &(this->field18_0x130)._s_0.avturr1, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"bvturr"), bVar1)) ||
           ((piVar2 = &(this->field18_0x130)._s_0.avturr2, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"bvturr"), bVar1)))) ||
          (((piVar2 = &(this->field18_0x130)._s_0.main_tower, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"abtowe"), bVar1)) ||
           ((piVar2 = &(this->field18_0x130)._s_0.avtower1, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"abtowe"), bVar1)))))))))) ||
       (((((piVar2 = &(this->field18_0x130)._s_0.avtower2, *piVar2 == 0 &&
           (bVar1 = IsOdf(param_1,"abtowe"), bVar1)) ||
          ((piVar2 = &(this->field18_0x130)._s_0.main_power, *piVar2 == 0 &&
           (bVar1 = IsOdf(param_1,"abwpow"), bVar1)))) ||
         ((piVar2 = &(this->field18_0x130)._s_0.avpower1, *piVar2 == 0 &&
          (bVar1 = IsOdf(param_1,"abwpow"), bVar1)))) ||
        (((piVar2 = &(this->field18_0x130)._s_0.avpower2, *piVar2 == 0 &&
          (bVar1 = IsOdf(param_1,"abwpow"), bVar1)) ||
         (((bVar1 = IsAlive(&(this->field18_0x130)._s_0.svmuf), bVar1 &&
           (piVar2 = &(this->field18_0x130)._s_0.newmuf, *piVar2 == 0)) &&
          (bVar1 = IsOdf(param_1,"svmuf"), bVar1)))))))) {
      *piVar2 = param_1;
    }
    else {
      piVar2 = &(this->field18_0x130)._s_0.avmuf;
      bVar1 = IsAlive(piVar2);
      if ((!bVar1) && (bVar1 = IsOdf(param_1,"bvmuf"), bVar1)) {
        *piVar2 = param_1;
      }
    }
  }
  return;
}
