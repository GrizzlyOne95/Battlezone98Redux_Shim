
void FUN_00799aa0(void)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  undefined1 local_a0 [16];
  undefined1 local_90 [16];
  int local_80;
  int local_7c;
  int local_78;
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085f670;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  FUN_00764760(uVar2);
  local_80 = FUN_0073bd10();
  if ((*(char *)(local_80 + 0x60) == '\0') || (*(char *)(local_80 + 0x7c) != '\0')) {
    FUN_00764760(uVar2);
    local_7c = FUN_0056f900();
    cVar1 = FUN_00427310(local_7c + 0x50,local_7c + 0xc0);
    if (cVar1 != '\0') {
      uVar3 = FUN_0041f870();
      basic_string<>(uVar3);
      local_8 = 2;
      basic_string<>("ready");
      local_8._0_1_ = 3;
      puVar5 = local_2c;
      puVar4 = local_5c;
      uVar3 = FUN_0073bcf0(local_90);
      (**(code **)(**(int **)(local_78 + 0x1bc) + 0x1c))(uVar3,puVar4,puVar5);
      local_8 = CONCAT31(local_8._1_3_,2);
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
  }
  else {
    basic_string<>(&DAT_008a1ad8);
    local_8 = 0;
    basic_string<>("ready");
    local_8._0_1_ = 1;
    puVar5 = local_74;
    puVar4 = local_44;
    uVar3 = FUN_0073bcf0(local_a0);
    (**(code **)(**(int **)(local_78 + 0x1bc) + 0x1c))(uVar3,puVar4,puVar5);
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

