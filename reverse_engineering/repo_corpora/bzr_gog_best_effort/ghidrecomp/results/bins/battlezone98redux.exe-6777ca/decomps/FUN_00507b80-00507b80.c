
undefined4 FUN_00507b80(undefined4 param_1)

{
  float *pfVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  
  pfVar1 = (float *)FUN_004ff7a0(param_1,1);
  if (pfVar1 != (float *)0x0) {
    uVar2 = FUN_0082ba59(param_1,2,0);
    iVar3 = FUN_00446460(uVar2,0x811c9dc5);
    if (iVar3 == -0x3f3b10c) {
      fVar4 = (float10)FUN_0082ba89(param_1,3);
      pfVar1[1] = (float)fVar4;
    }
    else if (iVar3 == -0x2f3af79) {
      fVar4 = (float10)FUN_0082ba89(param_1,3);
      *pfVar1 = (float)fVar4;
    }
    else if (iVar3 == -0xf3ac53) {
      fVar4 = (float10)FUN_0082ba89(param_1,3);
      pfVar1[2] = (float)fVar4;
    }
  }
  return 0;
}

