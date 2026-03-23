
void FUN_00762fb0(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  uint uStack_40;
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined4 local_20;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085cf08;
  local_10 = ExceptionList;
  uStack_40 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_40;
  ExceptionList = &local_10;
  puVar3 = &local_16;
  Getal(&local_17);
  uVar1 = select_on_container_copy_construction(puVar3);
  allocator<>(uVar1);
  FUN_0075ffc0(&local_15);
  local_8 = 1;
  puVar2 = (undefined4 *)FUN_0042d8c0(local_24);
  local_20 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_begin(local_28);
  uVar1 = *puVar2;
  puVar2 = (undefined4 *)FUN_00438c40(local_2c);
  FUN_00763190(local_30,local_20,*puVar2,uVar1);
  FUN_0076306e();
  return;
}

