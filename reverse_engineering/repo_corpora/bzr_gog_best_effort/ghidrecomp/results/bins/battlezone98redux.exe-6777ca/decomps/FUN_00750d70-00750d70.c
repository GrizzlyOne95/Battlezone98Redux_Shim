
void FUN_00750d70(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 local_44 [12];
  undefined4 local_38;
  undefined4 local_34;
  int *local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856e98;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_30 = (int *)FUN_007508c0(local_14);
  if (local_30 != (int *)0x0) {
    local_38 = FUN_0045e1d0(local_2c,0,0xffa);
    local_8 = 0;
    local_34 = local_38;
    uVar1 = FUN_0041f870();
    uVar1 = FUN_0041f870(uVar1);
    puVar2 = (undefined4 *)FUN_0073a970(local_44);
    (**(code **)(*local_30 + 0x50))(*puVar2,puVar2[1],uVar1);
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

