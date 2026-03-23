
undefined4 * __thiscall FUN_0049eb60(undefined4 *param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  float10 fVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849598;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004e6bf0(param_2,param_3,0x42c80000);
  local_8 = 0;
  *param_1 = UnBuild::vftable;
  param_1[0x57] = 0;
  if (param_3 != 0) {
    iVar2 = FUN_00462400(uVar1);
    fVar3 = (float10)FUN_00462470(*(undefined4 *)(iVar2 + 0xc));
    fVar3 = (float10)FUN_0044fb20((float)fVar3);
    param_1[0x53] = (float)fVar3 + 5.0 + 10.0;
    param_1[0x53] = (float)param_1[0x53] * (float)param_1[0x53];
  }
  ExceptionList = local_10;
  return param_1;
}

