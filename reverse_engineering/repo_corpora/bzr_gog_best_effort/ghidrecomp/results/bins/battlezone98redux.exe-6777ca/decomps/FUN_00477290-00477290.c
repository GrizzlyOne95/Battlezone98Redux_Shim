
undefined4 * __thiscall FUN_00477290(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  float10 fVar3;
  
  param_1[1] = param_2;
  param_1[5] = param_3;
  fVar3 = (float10)FUN_0062df00(param_2,param_3);
  uVar1 = FUN_00477230((float)fVar3);
  *param_1 = uVar1;
  fVar3 = (float10)FUN_0062dec0(param_2);
  param_1[2] = (float)fVar3;
  fVar3 = (float10)FUN_0062dee0(param_2,param_3);
  param_1[3] = (float)fVar3;
  uVar1 = FUN_0062df20(param_1[2],param_1[3]);
  param_1[4] = uVar1;
  iVar2 = FUN_0062df80(param_3);
  if (iVar2 == 0) {
    param_1[6] = 0;
    param_1[7] = 0;
    param_1[8] = 4;
  }
  else {
    iVar2 = FUN_0045c4f0(param_3);
    fVar3 = (float10)FUN_0062dec0(param_3);
    param_1[6] = (float)fVar3;
    fVar3 = (float10)FUN_0062dee0(param_3,param_2);
    param_1[7] = (float)fVar3;
    if ((*(uint *)(iVar2 + 0x114) & 2) == 0) {
      uVar1 = FUN_0062df20(param_1[6],param_1[7]);
      param_1[8] = uVar1;
    }
    else {
      param_1[8] = 4;
    }
  }
  return param_1;
}

