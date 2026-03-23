
void __fastcall FUN_0073d020(int *param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  bool bVar6;
  uint local_a4;
  byte *local_a0;
  byte *local_9c;
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085aafc;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  if ((DAT_02cc385c & 1) == 0) {
    DAT_02cc385c = DAT_02cc385c | 1;
    local_8 = 0;
    basic_string<>("gameSettings");
    FUN_0083e979(FUN_00867b00);
  }
  if ((DAT_02cc385c & 2) == 0) {
    DAT_02cc385c = DAT_02cc385c | 2;
    local_8 = 1;
    basic_string<>("GameVersion");
    FUN_0083e979(FUN_00867af0);
  }
  local_8 = 0xffffffff;
  iVar3 = FUN_0056f900(uVar2);
  if (iVar3 == 0) goto LAB_0073d383;
  FUN_0073c0b0(local_2c,1);
  local_8._0_1_ = 2;
  local_8._1_3_ = 0;
  local_a0 = (byte *)(**(code **)(*param_1 + 0x2c))(iVar3 + 0x10,&DAT_02cc37fc);
  if (local_a0 == (byte *)0x0) {
LAB_0073d1e3:
    *(int *)(iVar3 + 0xd8) = *(int *)(iVar3 + 0xd8) + 1;
    uVar4 = FUN_0073c0b0(local_8c,1);
    FUN_0045e0f0(uVar4);
    ~basic_string<>();
    pcVar5 = (char *)(**(code **)(*param_1 + 0x2c))(iVar3 + 0x10,&DAT_02cc382c);
    uVar4 = FUN_0041f870();
    basic_string<>(uVar4);
    local_8._0_1_ = 3;
    (**(code **)(*param_1 + 0x20))(iVar3 + 0x10,&DAT_02cc37fc,local_44);
    local_8._0_1_ = 2;
    ~basic_string<>();
    if ((pcVar5 == (char *)0x0) || (*pcVar5 == '\0')) {
      basic_string<>(PTR_s_2_2_301_008eda3c);
      local_8._0_1_ = 4;
      basic_string<>("GameVersion");
      local_8._0_1_ = 5;
      (**(code **)(*param_1 + 0x20))(iVar3 + 0x10,local_74,local_5c);
      local_8._0_1_ = 4;
      ~basic_string<>();
      local_8._0_1_ = 2;
      ~basic_string<>();
    }
  }
  else {
    local_9c = (byte *)FUN_0041f870();
    do {
      bVar1 = *local_a0;
      bVar6 = bVar1 < *local_9c;
      if (bVar1 != *local_9c) {
LAB_0073d1bf:
        local_a4 = -(uint)bVar6 | 1;
        goto LAB_0073d1ca;
      }
      if (bVar1 == 0) break;
      bVar1 = local_a0[1];
      bVar6 = bVar1 < local_9c[1];
      if (bVar1 != local_9c[1]) goto LAB_0073d1bf;
      local_a0 = local_a0 + 2;
      local_9c = local_9c + 2;
    } while (bVar1 != 0);
    local_a4 = 0;
LAB_0073d1ca:
    if (local_a4 != 0) goto LAB_0073d1e3;
  }
  *(undefined4 *)(iVar3 + 0x4c) = *(undefined4 *)(iVar3 + 0xf8);
  *(undefined1 *)(iVar3 + 0x48) = *(undefined1 *)(iVar3 + 0xf4);
  FID_conflict_operator_(iVar3 + 0xc0);
  local_8 = 0xffffffff;
  ~basic_string<>();
LAB_0073d383:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

