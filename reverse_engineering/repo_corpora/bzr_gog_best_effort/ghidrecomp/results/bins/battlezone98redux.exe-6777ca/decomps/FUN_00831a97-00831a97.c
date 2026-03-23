
void FUN_00831a97(undefined4 param_1,double *param_2,undefined4 param_3,undefined4 param_4,
                 int param_5)

{
  double *pdVar1;
  double *pdVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  undefined1 local_24 [16];
  undefined1 local_14 [16];
  
  pdVar1 = (double *)FUN_0083332e(param_3,local_14);
  if ((pdVar1 == (double *)0x0) ||
     (pdVar2 = (double *)FUN_0083332e(param_4,local_24), pdVar2 == (double *)0x0)) {
    iVar3 = FUN_00831d18(param_1,param_3,param_4,param_2,param_5);
    if (iVar3 == 0) {
      FUN_0082dde7(param_1,param_3,param_4);
    }
    return;
  }
  dVar8 = *pdVar2;
  dVar7 = *pdVar1;
  if (param_5 == 5) {
    dVar8 = dVar8 + dVar7;
LAB_00831ba9:
    *param_2 = dVar8;
  }
  else {
    if (param_5 == 6) {
      dVar7 = dVar7 - dVar8;
    }
    else {
      if (param_5 == 7) {
        dVar8 = dVar8 * dVar7;
        goto LAB_00831ba9;
      }
      if (param_5 == 8) {
        dVar7 = dVar7 / dVar8;
      }
      else if (param_5 == 9) {
        dVar5 = dVar7 / dVar8;
        dVar6 = (double)((ulonglong)dVar5 & 0x8000000000000000);
        dVar4 = (double)(-(ulonglong)
                          ((double)((ulonglong)dVar5 ^ (ulonglong)dVar6) < 4503599627370496.0) &
                         0x4330000000000000 | (ulonglong)dVar6);
        dVar4 = (dVar5 + dVar4) - dVar4;
        dVar7 = dVar7 - (dVar4 - (double)(-(ulonglong)(dVar6 < dVar4 - dVar5) & 0x3ff0000000000000))
                        * dVar8;
      }
      else {
        if (param_5 == 10) {
          __libm_sse2_pow();
          *param_2 = dVar7;
          goto LAB_00831bb0;
        }
        if (param_5 != 0xb) {
          return;
        }
        dVar7 = -dVar7;
      }
    }
    *param_2 = dVar7;
  }
LAB_00831bb0:
  *(undefined4 *)(param_2 + 1) = 3;
  return;
}

