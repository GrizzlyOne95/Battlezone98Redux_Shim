
int __thiscall FUN_006ac3d0(int param_1,undefined4 *param_2,code *param_3)

{
  undefined4 uVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850020;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_006c8ce0(param_1);
  local_8 = 0;
  for (local_14 = *(int *)(param_1 + 0x1c); local_14 != 0; local_14 = *(int *)(local_14 + 0x10)) {
    cVar2 = FUN_006ac330(local_14 + 4,param_2);
    if (cVar2 != '\0') {
      local_8 = 0xffffffff;
      FUN_006c8d50();
      ExceptionList = local_10;
      return local_14;
    }
  }
  FUN_006c8de0(uVar3);
  iVar4 = (*param_3)(*(undefined4 *)(param_1 + 0x18));
  local_8 = CONCAT31(local_8._1_3_,1);
  uVar1 = param_2[1];
  *(undefined4 *)(iVar4 + 4) = *param_2;
  *(undefined4 *)(iVar4 + 8) = uVar1;
  FUN_006c8db0();
  local_14 = *(int *)(param_1 + 0x1c);
  while( true ) {
    if (local_14 == 0) {
      *(undefined4 *)(iVar4 + 0x10) = *(undefined4 *)(param_1 + 0x1c);
      *(int *)(param_1 + 0x1c) = iVar4;
      iVar4 = *(int *)(param_1 + 0x1c);
      local_8 = local_8 & 0xffffff00;
      FUN_006ac260();
      local_8 = 0xffffffff;
      FUN_006c8d50();
      ExceptionList = local_10;
      return iVar4;
    }
    cVar2 = FUN_006ac330(local_14 + 4,param_2);
    if (cVar2 != '\0') break;
    local_14 = *(int *)(local_14 + 0x10);
  }
  local_8 = local_8 & 0xffffff00;
  FUN_006ac260();
  local_8 = 0xffffffff;
  FUN_006c8d50();
  ExceptionList = local_10;
  return local_14;
}

