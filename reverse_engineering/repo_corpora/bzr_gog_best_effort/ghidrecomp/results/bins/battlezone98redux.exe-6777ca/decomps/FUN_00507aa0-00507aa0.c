
undefined4 FUN_00507aa0(undefined4 param_1)

{
  float *pfVar1;
  undefined4 uVar2;
  int iVar3;
  
  pfVar1 = (float *)FUN_004ff7a0(param_1,1);
  if (pfVar1 == (float *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0082ba59(param_1,2,0);
    iVar3 = FUN_00446460(uVar2,0x811c9dc5);
    if (iVar3 == -0x3f3b10c) {
      FUN_0082cd58(param_1,(double)pfVar1[1]);
      uVar2 = 1;
    }
    else if (iVar3 == -0x2f3af79) {
      FUN_0082cd58(param_1,(double)*pfVar1);
      uVar2 = 1;
    }
    else if (iVar3 == -0xf3ac53) {
      FUN_0082cd58(param_1,(double)pfVar1[2]);
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

