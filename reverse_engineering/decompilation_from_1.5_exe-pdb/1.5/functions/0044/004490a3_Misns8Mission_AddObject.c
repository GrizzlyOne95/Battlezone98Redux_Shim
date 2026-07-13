/*
 * Entry: 004490a3
 * Name: Misns8Mission::AddObject
 * Namespace: Misns8Mission
 * Signature: void AddObject(Misns8Mission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns8Mission::AddObject(Misns8Mission *this,int param_1)

{
  bool bVar1;
  int *piVar2;
  
  if (((this->field18_0x130)._s_0.avturret1 == 0) && (bVar1 = IsOdf(param_1,"bvtur8"), bVar1)) {
    (this->field18_0x130)._s_0.avturret1 = param_1;
  }
  else {
    piVar2 = &(this->field18_0x130)._s_0.avturret2;
    if (((((((((*piVar2 == 0) && (bVar1 = IsOdf(param_1,"bvtur8"), bVar1)) ||
             ((piVar2 = &(this->field18_0x130)._s_0.avfighter1, *piVar2 == 0 &&
              (bVar1 = IsOdf(param_1,"bvra8"), bVar1)))) ||
            ((piVar2 = &(this->field18_0x130)._s_0.avfighter2, *piVar2 == 0 &&
             (bVar1 = IsOdf(param_1,"bvra8"), bVar1)))) ||
           ((piVar2 = &(this->field18_0x130)._s_0.avrig1, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"avcns8"), bVar1)))) ||
          (((((piVar2 = &(this->field18_0x130)._s_0.avrig2, *piVar2 == 0 &&
              (bVar1 = IsOdf(param_1,"avcns8"), bVar1)) ||
             ((piVar2 = &(this->field18_0x130)._s_0.avtank1, *piVar2 == 0 &&
              (bVar1 = IsOdf(param_1,"bvtavk"), bVar1)))) ||
            ((piVar2 = &(this->field18_0x130)._s_0.avtank2, *piVar2 == 0 &&
             (bVar1 = IsOdf(param_1,"bvtavk"), bVar1)))) ||
           ((piVar2 = &(this->field18_0x130)._s_0.avtank3, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"bvtavk"), bVar1)))))) ||
         ((((piVar2 = &(this->field18_0x130)._s_0.avtower1, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"abtowe"), bVar1)) ||
           ((piVar2 = &(this->field18_0x130)._s_0.avtower2, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"abtowe"), bVar1)))) ||
          (((piVar2 = &(this->field18_0x130)._s_0.avpower1, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"abwpow"), bVar1)) ||
           ((piVar2 = &(this->field18_0x130)._s_0.avpower2, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"abwpow"), bVar1)))))))) ||
        (((((piVar2 = &(this->field18_0x130)._s_0.avtower3, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"abtowe"), bVar1)) ||
           ((piVar2 = &(this->field18_0x130)._s_0.avtower4, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"abtowe"), bVar1)))) ||
          ((piVar2 = &(this->field18_0x130)._s_0.avpower3, *piVar2 == 0 &&
           (bVar1 = IsOdf(param_1,"abwpow"), bVar1)))) ||
         ((piVar2 = &(this->field18_0x130)._s_0.avpower4, *piVar2 == 0 &&
          (bVar1 = IsOdf(param_1,"abwpow"), bVar1)))))) ||
       ((((((piVar2 = &(this->field18_0x130)._s_0.avsilo1, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"absilo"), bVar1)) ||
           ((piVar2 = &(this->field18_0x130)._s_0.avsilo2, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"absilo"), bVar1)))) ||
          (((piVar2 = &(this->field18_0x130)._s_0.screwtower, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"abtowe"), bVar1)) ||
           (((piVar2 = &(this->field18_0x130)._s_0.screwpower, *piVar2 == 0 &&
             (bVar1 = IsOdf(param_1,"abwpow"), bVar1)) ||
            ((((piVar2 = &(this->field18_0x130)._s_0.svpower1, *piVar2 == 0 &&
               (bVar1 = IsOdf(param_1,"sbwpow"), bVar1)) ||
              ((piVar2 = &(this->field18_0x130)._s_0.svpower2, *piVar2 == 0 &&
               (bVar1 = IsOdf(param_1,"sbwpow"), bVar1)))) ||
             ((piVar2 = &(this->field18_0x130)._s_0.avturret3, *piVar2 == 0 &&
              (bVar1 = IsOdf(param_1,"bvtur8"), bVar1)))))))))) ||
         ((((piVar2 = &(this->field18_0x130)._s_0.avturret4, *piVar2 == 0 &&
            (bVar1 = IsOdf(param_1,"bvtur8"), bVar1)) ||
           ((((((piVar2 = &(this->field18_0x130)._s_0.avbomb1, *piVar2 == 0 &&
                (bVar1 = IsOdf(param_1,"bvhraz"), bVar1)) ||
               ((piVar2 = &(this->field18_0x130)._s_0.avapc1, *piVar2 == 0 &&
                (bVar1 = IsOdf(param_1,"bvapc"), bVar1)))) ||
              ((piVar2 = &(this->field18_0x130)._s_0.sav1, *piVar2 == 0 &&
               (bVar1 = IsOdf(param_1,"savtnk"), bVar1)))) ||
             ((piVar2 = &(this->field18_0x130)._s_0.sav2, *piVar2 == 0 &&
              (bVar1 = IsOdf(param_1,"savtnk"), bVar1)))) ||
            (((piVar2 = &(this->field18_0x130)._s_0.sav3, *piVar2 == 0 &&
              (bVar1 = IsOdf(param_1,"savtnk"), bVar1)) ||
             ((piVar2 = &(this->field18_0x130)._s_0.sav4, *piVar2 == 0 &&
              (bVar1 = IsOdf(param_1,"savtnk"), bVar1)))))))) ||
          ((piVar2 = &(this->field18_0x130)._s_0.sav5, *piVar2 == 0 &&
           (bVar1 = IsOdf(param_1,"savtnk"), bVar1)))))) ||
        ((piVar2 = &(this->field18_0x130)._s_0.sav6, *piVar2 == 0 &&
         (bVar1 = IsOdf(param_1,"savtnk"), bVar1)))))) {
      *piVar2 = param_1;
    }
    else {
      piVar2 = &(this->field18_0x130)._s_0.avwalker;
      if ((*piVar2 == 0) && (bVar1 = IsOdf(param_1,"bvwalk"), bVar1)) {
        *piVar2 = param_1;
      }
    }
  }
  return;
}
