
int FUN_00713b90(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined1 local_20 [4];
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857e48;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006f6af0(param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *(undefined1 *)(local_14 + 0xc) = *(undefined1 *)(param_1 + 0xc);
  uVar2 = *(undefined4 *)(param_1 + 0x14);
  *(undefined4 *)(local_14 + 0x10) = *(undefined4 *)(param_1 + 0x10);
  *(undefined4 *)(local_14 + 0x14) = uVar2;
  puVar1 = (undefined4 *)FID_conflict_begin(local_20);
  *(undefined4 *)(local_14 + 0x18) = *puVar1;
  *(undefined4 *)(local_14 + 0x1c) = *(undefined4 *)(param_1 + 0x1c);
  FUN_0041fc00(&local_1c);
  local_18 = *(undefined4 *)(param_1 + 0x18);
  uVar2 = distance<>(local_1c,local_18);
  advance<>(local_14 + 0x18,uVar2);
  ExceptionList = local_10;
  return local_14;
}

