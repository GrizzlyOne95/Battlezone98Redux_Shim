
undefined4 FUN_0083bffe(undefined4 param_1,int param_2,undefined4 param_3)

{
  double dVar1;
  int iVar2;
  undefined4 uVar3;
  int extraout_ECX;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  
  iVar2 = FUN_0083c468(param_2);
  if ((iVar2 == 0) || (iVar2 = FUN_0083c468(param_3), iVar2 == 0)) goto switchD_0083c043_caseD_14;
  dVar7 = *(double *)(param_2 + 8);
  dVar1 = *(double *)(extraout_ECX + 8);
  switch(param_1) {
  case 0xc:
    dVar7 = dVar1 + dVar7;
    break;
  case 0xd:
    dVar7 = dVar7 - dVar1;
    break;
  case 0xe:
    dVar7 = dVar1 * dVar7;
    break;
  case 0xf:
    if (dVar1 != 0.0) {
      dVar7 = dVar7 / dVar1;
      break;
    }
    goto switchD_0083c043_caseD_14;
  case 0x10:
    if (dVar1 != 0.0) {
      dVar5 = dVar7 / dVar1;
      dVar6 = (double)((ulonglong)dVar5 & 0x8000000000000000);
      dVar4 = (double)(-(ulonglong)
                        ((double)((ulonglong)dVar5 ^ (ulonglong)dVar6) < 4503599627370496.0) &
                       0x4330000000000000 | (ulonglong)dVar6);
      dVar4 = (dVar5 + dVar4) - dVar4;
      dVar7 = dVar7 - (dVar4 - (double)(-(ulonglong)(dVar6 < dVar4 - dVar5) & 0x3ff0000000000000)) *
                      dVar1;
      break;
    }
    goto switchD_0083c043_caseD_14;
  case 0x11:
    __libm_sse2_pow();
    break;
  case 0x12:
    dVar7 = -dVar7;
    break;
  default:
    dVar7 = 0.0;
    break;
  case 0x14:
    goto switchD_0083c043_caseD_14;
  }
  if (NAN(dVar7)) {
switchD_0083c043_caseD_14:
    uVar3 = 0;
  }
  else {
    *(double *)(param_2 + 8) = dVar7;
    uVar3 = 1;
  }
  return uVar3;
}

