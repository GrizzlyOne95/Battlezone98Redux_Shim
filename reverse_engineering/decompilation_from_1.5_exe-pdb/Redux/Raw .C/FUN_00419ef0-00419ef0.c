
void FUN_00419ef0(void)

{
  uint uVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined8 uVar6;
  undefined1 local_a8 [4];
  undefined1 local_a4 [4];
  undefined1 local_a0 [4];
  undefined1 local_9c [4];
  undefined1 local_98 [4];
  undefined1 local_94 [4];
  undefined1 local_90 [4];
  undefined4 local_8c;
  undefined4 local_88;
  undefined8 local_84;
  undefined4 *local_7c;
  undefined4 local_78;
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844af8;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00418d40(local_14);
  local_8 = 0;
  *local_7c = TouchInputTap::vftable;
  local_7c[0x20] = 0;
  local_7c[0x21] = 0;
  uVar3 = FUN_0068bed0("button_tap_here");
  local_7c[0x1b] = uVar3;
  *(undefined1 *)(local_7c + 0x1f) = 0;
  *(undefined1 *)(local_7c + 0x19) = 0;
  basic_string<>("TAP:ACTIVE");
  local_8._0_1_ = 1;
  FUN_00421e00(&local_78,local_74);
  local_8._0_1_ = 0;
  ~basic_string<>();
  uVar3 = FID_conflict_begin(local_a0);
  cVar2 = FUN_00420f10(uVar3);
  if ((cVar2 != '\0') && (iVar4 = FUN_00421ea0(), *(int *)(iVar4 + 0x18) != 0)) {
    local_8c = 0;
    local_88 = 0;
    local_84 = 0;
    basic_string<>("TAP:TIME");
    local_8._0_1_ = 2;
    puVar5 = (undefined4 *)FUN_00421e00(local_a4,local_5c);
    local_78 = *puVar5;
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    uVar3 = FID_conflict_begin(local_9c);
    cVar2 = FUN_00420f10(uVar3);
    if (cVar2 != '\0') {
      iVar4 = FUN_00421ea0();
      uVar1 = *(uint *)(iVar4 + 0x18);
      uVar6 = FUN_00822ea0();
      local_84 = CONCAT44((((int)uVar1 >> 0x1f) - (int)((ulonglong)uVar6 >> 0x20)) -
                          (uint)(uVar1 < (uint)uVar6),uVar1 - (uint)uVar6);
    }
    if ((local_84._4_4_ < 1) && (local_84 < 0)) {
      local_84 = 0;
    }
    basic_string<>("TAP:X");
    local_8._0_1_ = 3;
    puVar5 = (undefined4 *)FUN_00421e00(local_94,local_2c);
    local_78 = *puVar5;
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    uVar3 = FID_conflict_begin(local_98);
    cVar2 = FUN_00420f10(uVar3);
    if (cVar2 != '\0') {
      iVar4 = FUN_00421ea0();
      local_8c = *(undefined4 *)(iVar4 + 0x18);
    }
    basic_string<>("TAP:Y");
    local_8._0_1_ = 4;
    puVar5 = (undefined4 *)FUN_00421e00(local_90,local_44);
    local_78 = *puVar5;
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    uVar3 = FID_conflict_begin(local_a8);
    cVar2 = FUN_00420f10(uVar3);
    if (cVar2 != '\0') {
      iVar4 = FUN_00421ea0();
      local_88 = *(undefined4 *)(iVar4 + 0x18);
    }
    FUN_0041a3f0(&local_8c,(undefined4)local_84,local_84._4_4_);
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

