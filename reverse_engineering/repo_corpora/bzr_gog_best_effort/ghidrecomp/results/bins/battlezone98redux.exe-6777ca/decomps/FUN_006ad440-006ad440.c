
int __thiscall FUN_006ad440(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  uint _FileHandle;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  undefined1 local_1c [4];
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850160;
  local_10 = ExceptionList;
  _FileHandle = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  piVar5 = (int *)(param_1 + 0x18);
  LOCK();
  iVar3 = *piVar5;
  *piVar5 = *piVar5;
  UNLOCK();
  local_14 = param_1;
  if (iVar3 == 0) {
    FUN_006ad5e0();
    puVar2 = (undefined4 *)FUN_004fbb60();
    uVar1 = puVar2[1];
    *param_2 = *puVar2;
    param_2[1] = uVar1;
    iVar3 = 0;
  }
  else {
    FUN_006ad400();
    local_8 = 0;
    FUN_006c9060(local_14,local_1c);
    local_8._0_1_ = 1;
    local_18 = 0;
    while (iVar4 = FUN_006ad980(0,param_2), iVar3 = local_18, iVar4 != 0) {
      iVar3 = eof(_FileHandle);
      if (local_18 != iVar3) {
        local_18 = local_18 + 1;
      }
    }
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_006c90e0();
    local_8 = 0xffffffff;
    FUN_006ad420();
  }
  ExceptionList = local_10;
  return iVar3;
}

