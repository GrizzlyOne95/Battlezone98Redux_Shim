
void FUN_006a0e20(int param_1)

{
  float fVar1;
  undefined1 uVar2;
  uint uVar3;
  int *piVar4;
  void *pvVar5;
  float *pfVar6;
  undefined4 uVar7;
  int local_34;
  int local_2c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fa6c;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  piVar4 = (int *)FUN_004200d0();
  local_2c = *piVar4;
  if (local_2c == 0) {
    pvVar5 = operator_new(0x70);
    local_8 = 0;
    if (pvVar5 == (void *)0x0) {
      local_34 = 0;
    }
    else {
      local_34 = FUN_006a0fa0();
    }
    local_8 = 0xffffffff;
    local_2c = local_34;
    piVar4 = (int *)FUN_004200d0();
    *piVar4 = local_34;
  }
  pfVar6 = (float *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))(uVar3);
  fVar1 = pfVar6[2];
  uVar7 = FUN_006a08c0((double)*pfVar6);
  *(undefined4 *)(local_2c + 0x18) = uVar7;
  uVar7 = FUN_006a0920((double)fVar1);
  *(undefined4 *)(local_2c + 0x1c) = uVar7;
  FUN_0046fbd0();
  uVar7 = FUN_0083f040();
  *(undefined4 *)(local_2c + 0x10) = uVar7;
  uVar2 = FUN_004625b0();
  *(undefined1 *)(local_2c + 0x15) = uVar2;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

