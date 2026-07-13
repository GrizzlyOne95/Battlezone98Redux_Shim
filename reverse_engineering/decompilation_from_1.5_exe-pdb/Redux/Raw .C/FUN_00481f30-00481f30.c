
undefined4 * __thiscall FUN_00481f30(undefined4 *param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  void *pvVar2;
  int iVar3;
  undefined4 local_20;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847a04;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_005a79f0(param_2,param_3);
  local_8 = 0;
  *param_1 = CameraPod::vftable;
  param_1[6] = CameraPod::vftable;
  if (0.0 < *(float *)(param_3 + 0x174)) {
    pvVar2 = operator_new(0x14);
    local_8._0_1_ = 1;
    if (pvVar2 == (void *)0x0) {
      local_20 = 0;
    }
    else {
      local_20 = FUN_005c18e0(param_1);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    param_1[0x66] = local_20;
    *(undefined4 *)param_1[0x66] = *(undefined4 *)(param_3 + 0x174);
    *(undefined4 *)(param_1[0x66] + 4) = *(undefined4 *)(param_3 + 0x178);
  }
  iVar3 = FUN_0062e250(param_2,0x28,uVar1);
  if (iVar3 == 0) {
    iVar3 = FUN_0062ccc0(param_2,"fun3d\\CameraPod.cpp");
    builtin_strncpy((char *)(iVar3 + 8),"eyep",4);
    builtin_strncpy((char *)(iVar3 + 0xc),"oint",4);
    *(double *)(iVar3 + 0x50) =
         (double)*(float *)(param_1[0x3c] + 0xc) + (double)*(float *)(param_1[0x3c] + 0x14) * 0.8;
    *(undefined4 *)(iVar3 + 0x84) = 0x28;
  }
  ExceptionList = local_10;
  return param_1;
}

