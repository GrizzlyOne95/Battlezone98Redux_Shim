
void FUN_00742df0(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined1 local_5c [16];
  int local_4c;
  int *local_48;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b240;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  basic_string<>(&DAT_00873ef0);
  local_8 = 0;
  basic_string<>("launched");
  local_8._0_1_ = 1;
  puVar4 = local_2c;
  puVar3 = local_44;
  uVar2 = FUN_0073bcf0(local_5c);
  (**(code **)(*local_48 + 0x20))(uVar2,puVar3,puVar4,uVar1);
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  ~basic_string<>();
  local_4c = FUN_0056f900();
  if (local_4c != 0) {
    *(undefined1 *)(local_4c + 0xb1) = 1;
    if (*(char *)(local_4c + 0x114) == '\0') {
      (**(code **)(*local_48 + 0x34))(0);
    }
    else {
      (**(code **)(*local_48 + 0x34))(1);
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

