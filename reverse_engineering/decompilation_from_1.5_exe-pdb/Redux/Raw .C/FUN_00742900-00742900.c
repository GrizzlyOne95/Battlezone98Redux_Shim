
void __thiscall FUN_00742900(int *param_1,int param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  undefined1 local_e0 [16];
  undefined1 local_d0 [8];
  undefined1 local_c8 [16];
  undefined1 local_b8 [4];
  undefined1 local_b4 [4];
  undefined1 local_b0 [4];
  int local_ac;
  undefined1 local_a8 [4];
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  char *local_98;
  undefined4 local_8c;
  undefined1 local_88 [4];
  undefined1 local_84 [4];
  int local_80;
  undefined4 local_7c;
  int *local_78;
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b1fb;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_78 = param_1;
  if (param_2 == 0) goto LAB_00742cd1;
  FUN_007659f0(local_14);
  FUN_0073bb30();
  FUN_00747cf0();
  FUN_00428520();
  local_8 = 0;
  FUN_0042d8c0(local_88);
  FID_conflict_begin(local_b4);
  while( true ) {
    cVar1 = FUN_00420f10(local_b4);
    if (cVar1 == '\0') break;
    iVar2 = FUN_0042da60();
    FUN_00578af0(local_d0,iVar2 + 8);
    FUN_0042da80();
  }
  local_ac = (**(code **)(*local_78 + 0x44))(param_2 + 0x10);
  for (local_80 = 0; local_80 < local_ac; local_80 = local_80 + 1) {
    (**(code **)(*local_78 + 0x48))(local_c8,param_2 + 0x10,local_80);
    FUN_00578b10(local_c8);
    FUN_00744a50(param_2,local_c8);
  }
  FUN_00424640(local_84);
  FID_conflict_begin(local_a8);
  while( true ) {
    cVar1 = FUN_00420f10(local_a8);
    if (cVar1 == '\0') break;
    local_8c = FUN_004237d0();
    FUN_0042d8c0(&local_7c);
    FID_conflict_begin(local_b0);
    while( true ) {
      cVar1 = FUN_00420f10(local_b0);
      if (cVar1 == '\0') break;
      uVar5 = local_8c;
      FUN_0042da60(local_8c);
      cVar1 = FUN_0056f780(uVar5);
      if (cVar1 != '\0') {
        iVar2 = FUN_0042da60();
        iVar2 = iVar2 + 8;
        FUN_007659f0(iVar2);
        FUN_0073bab0(iVar2);
        iVar2 = FUN_0042da60();
        uVar3 = (uint)*(ushort *)(iVar2 + 0x28);
        FUN_007659f0(uVar3);
        FUN_00574aa0(uVar3);
        local_9c = local_7c;
        FUN_00747ca0(local_b8,local_7c);
        (**(code **)(*local_78 + 0x4c))(param_2 + 0x10,local_8c);
        break;
      }
      FUN_0042da80();
    }
    FUN_00422190();
  }
  cVar1 = FUN_00742d50(param_2 + 0x10);
  if (cVar1 == '\x01') {
    basic_string<>("userCount");
    local_8._0_1_ = 1;
    local_98 = (char *)(**(code **)(*local_78 + 0x2c))(param_2 + 0x10,local_5c);
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    if (local_98 == (char *)0x0) {
LAB_00742c14:
      uVar5 = FUN_00416410();
      local_a4 = FUN_0073b940(local_74,uVar5);
      local_8._0_1_ = 2;
      local_a0 = local_a4;
      uVar5 = FUN_0041f870();
      basic_string<>(uVar5);
      local_8._0_1_ = 3;
      basic_string<>("userCount");
      local_8._0_1_ = 4;
      puVar7 = local_2c;
      puVar6 = local_44;
      uVar5 = FUN_0073bcf0(local_e0);
      (**(code **)(*local_78 + 0x20))(uVar5,puVar6,puVar7);
      local_8._0_1_ = 3;
      ~basic_string<>();
      local_8._0_1_ = 2;
      ~basic_string<>();
      local_8 = (uint)local_8._1_3_ << 8;
      ~basic_string<>();
    }
    else {
      iVar2 = atoi(local_98);
      iVar4 = FUN_00416410();
      if (iVar2 != iVar4) goto LAB_00742c14;
    }
    FUN_00742560();
  }
  local_8 = 0xffffffff;
  FUN_0045c7d0();
LAB_00742cd1:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

