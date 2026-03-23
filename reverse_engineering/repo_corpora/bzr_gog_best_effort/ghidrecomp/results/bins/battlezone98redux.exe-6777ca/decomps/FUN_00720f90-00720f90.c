
void FUN_00720f90(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_78 [4];
  undefined1 local_74 [4];
  undefined1 local_70 [4];
  undefined1 local_6c [4];
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  char local_46;
  undefined1 local_45;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00858cc0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  basic_string<>("Upgrade");
  local_8 = 0;
  local_4c = FUN_006b7490(local_44);
  local_8 = 0xffffffff;
  ~basic_string<>(uVar1);
  local_68 = FUN_006ab6b0();
  local_8 = 1;
  local_60 = local_68;
  uVar2 = FUN_004fee40(local_70);
  FUN_0070f510(local_6c,local_4c,"websocket",9,local_68,uVar2);
  local_46 = FID_conflict_operator__(uVar2);
  local_8 = 0xffffffff;
  FUN_00417b50();
  if (local_46 == '\0') {
    basic_string<>("Connection");
    local_8 = 2;
    local_50 = FUN_006b7490(local_2c);
    local_8 = 0xffffffff;
    ~basic_string<>();
    local_64 = FUN_006ab6b0();
    local_8 = 3;
    local_54 = local_64;
    uVar2 = FUN_004fee40(local_78);
    FUN_0070f510(local_74,local_50,"upgrade",7,local_64,uVar2);
    local_45 = FID_conflict_operator__(uVar2);
    local_8 = 0xffffffff;
    FUN_00417b50();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

