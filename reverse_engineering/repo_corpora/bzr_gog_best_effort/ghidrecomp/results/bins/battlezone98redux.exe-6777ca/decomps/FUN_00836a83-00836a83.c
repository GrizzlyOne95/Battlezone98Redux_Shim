
undefined4 FUN_00836a83(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  
  iVar1 = rand();
  dVar4 = (double)(iVar1 % 0x7fff) * 3.051850947599719e-05;
  iVar1 = FUN_0082c8f6(param_1);
  if (iVar1 != 0) {
    if (iVar1 != 1) {
      if (iVar1 == 2) {
        iVar1 = FUN_0082ba1c(param_1,1);
        iVar3 = FUN_0082ba1c(param_1,2);
        if (iVar3 < iVar1) {
          FUN_0082b8e4(param_1,2,"interval is empty");
        }
        dVar4 = (double)((iVar3 - iVar1) + 1) * dVar4;
        dVar6 = (double)((ulonglong)dVar4 & 0x8000000000000000);
        dVar5 = (double)(-(ulonglong)
                          ((double)((ulonglong)dVar4 ^ (ulonglong)dVar6) < 4503599627370496.0) &
                         0x4330000000000000 | (ulonglong)dVar6);
        dVar5 = (dVar4 + dVar5) - dVar5;
        FUN_0082cd58(param_1,(dVar5 - (double)(-(ulonglong)(dVar6 < dVar5 - dVar4) &
                                              0x3ff0000000000000)) + (double)iVar1);
        return 1;
      }
      uVar2 = FUN_0082bc39(param_1,"wrong number of arguments");
      return uVar2;
    }
    iVar1 = FUN_0082ba1c(param_1,1);
    if (iVar1 < 1) {
      FUN_0082b8e4(param_1,1,"interval is empty");
    }
    dVar4 = (double)iVar1 * dVar4;
    dVar6 = (double)((ulonglong)dVar4 & 0x8000000000000000);
    dVar5 = (double)(-(ulonglong)
                      ((double)((ulonglong)dVar4 ^ (ulonglong)dVar6) < 4503599627370496.0) &
                     0x4330000000000000 | (ulonglong)dVar6);
    dVar5 = (dVar4 + dVar5) - dVar5;
    dVar4 = (dVar5 - (double)(-(ulonglong)(dVar6 < dVar5 - dVar4) & 0x3ff0000000000000)) + 1.0;
  }
  FUN_0082cd58(param_1,dVar4);
  return 1;
}

