
undefined4 FUN_0043fe20(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  
  iVar1 = FUN_0067c830(param_2);
  if (iVar1 == 0) {
    param_1[0x1e] = 6;
    uVar2 = 0;
  }
  else {
    uVar3 = FUN_00437330();
    *param_1 = (int)uVar3;
    uVar4 = FUN_00437330();
    param_1[1] = (int)((ulonglong)uVar4 >> 0x20);
    param_1[0x1f] = PTR__Val_type<>_008e7674;
    param_1[0x20] = PTR_FUN_008e7678;
    param_1[0x21] = PTR_FUN_008e767c;
    param_1[0x22] = PTR_FUN_008e7680;
    param_1[0x23] = PTR_FUN_008e7684;
    uVar3 = FUN_00437330(uVar4,uVar3);
    *(undefined8 *)(param_1 + 8) = uVar3;
    FUN_004375d0(param_1);
    FUN_004375f0(param_1,1);
    iVar1 = FUN_0043ff20(param_1,1);
    if (iVar1 == 0) {
      if (param_1[0x1e] == 0) {
        param_1[0x1e] = 5;
      }
      uVar2 = 0;
    }
    else {
      FUN_0067c820();
      FUN_0067c940();
      uVar2 = 1;
    }
  }
  return uVar2;
}

