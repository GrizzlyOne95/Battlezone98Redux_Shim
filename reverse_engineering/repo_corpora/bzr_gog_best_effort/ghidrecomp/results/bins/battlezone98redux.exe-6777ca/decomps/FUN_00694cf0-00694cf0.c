
void FUN_00694cf0(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int local_28;
  void *local_20;
  int local_1c;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f9e1;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  memset((void *)(param_1 + 100),0,0x40);
  *(undefined4 *)(param_1 + 0x7c) = param_2;
  *(undefined4 *)(param_1 + 0x78) = param_3;
  FUN_00694cc0(param_1,uVar1);
  uVar2 = FUN_0069ee70(0,*(undefined4 *)(param_1 + 0x78),0,*(undefined4 *)(param_1 + 0x7c));
  *(undefined4 *)(param_1 + 0x80) = uVar2;
  local_20 = malloc(*(int *)(param_1 + 0x78) * *(int *)(param_1 + 0x7c) * 0x88);
  for (local_18 = 0; local_18 < *(int *)(param_1 + 0x78); local_18 = local_18 + 1) {
    for (local_1c = 0; local_1c < *(int *)(param_1 + 0x7c); local_1c = local_1c + 1) {
      iVar3 = forward<>(0x88,local_20);
      local_8 = 0;
      if (iVar3 == 0) {
        local_28 = 0;
      }
      else {
        local_28 = FUN_0069d7d0(local_18,local_1c,DAT_00920f04,param_1);
      }
      local_8 = 0xffffffff;
      *(undefined4 *)(local_28 + 100) = 0;
      *(int *)(*(int *)(*(int *)(param_1 + 0x80) + local_18 * 4) + local_1c * 4) = local_28;
      *(undefined4 *)(local_28 + 0x74) = 0;
      *(undefined1 *)(local_28 + 0x78) = 0;
      *(undefined4 *)(local_28 + 0x14) = 0;
      *(undefined4 *)(local_28 + 0x68) = 0;
      *(undefined4 *)(local_28 + 0x6c) = 0;
      *(undefined4 *)(local_28 + 0x70) = 0;
      *(int *)(*(int *)(*(int *)(param_1 + 0x80) + local_18 * 4) + local_1c * 4) = local_28;
      local_20 = (void *)((int)local_20 + 0x88);
    }
  }
  ExceptionList = local_10;
  return;
}

