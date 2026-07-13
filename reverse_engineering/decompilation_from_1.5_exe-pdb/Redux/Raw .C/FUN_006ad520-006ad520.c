
undefined4 __thiscall FUN_006ad520(int param_1,undefined4 *param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int *piVar5;
  undefined1 local_18 [4];
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850190;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  piVar5 = (int *)(param_1 + 0x18);
  LOCK();
  iVar1 = *piVar5;
  *piVar5 = *piVar5;
  UNLOCK();
  local_14 = param_1;
  if (iVar1 == 0) {
    FUN_006ad5e0();
    puVar3 = (undefined4 *)FUN_004fbb60();
    uVar4 = puVar3[1];
    *param_2 = *puVar3;
    param_2[1] = uVar4;
    uVar4 = 0;
  }
  else {
    FUN_006ad400(uVar2);
    local_8 = 0;
    FUN_006c9060(local_14,local_18);
    local_8._0_1_ = 1;
    uVar4 = FUN_006ad980(0,param_2);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_006c90e0();
    local_8 = 0xffffffff;
    FUN_006ad420();
  }
  ExceptionList = local_10;
  return uVar4;
}

