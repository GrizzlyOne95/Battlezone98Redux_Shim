
void FUN_007d9250(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_64 [8];
  undefined1 local_5c [11];
  undefined1 local_51 [3];
  undefined1 local_4e [2];
  int local_4c;
  undefined1 local_46;
  undefined1 local_45;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863163;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  basic_string<>("unnamed-grammar");
  local_8 = 0;
  FUN_007d8b50(local_4c + 0x20,local_2c);
  local_8._0_1_ = 2;
  ~basic_string<>(uVar1);
  basic_string<>("unnamed-rule");
  local_8._0_1_ = 3;
  FUN_007d8ba0(local_44);
  local_8 = CONCAT31(local_8._1_3_,5);
  ~basic_string<>();
  local_46 = 1;
  local_45 = 0x20;
  uVar2 = FUN_007d9ce0(local_4e,&local_46,0);
  puVar4 = &local_45;
  uVar3 = FUN_007d9d50(local_51,&DAT_0260c08b,0);
  uVar2 = FUN_007d9a70(local_64,uVar3,puVar4,uVar2);
  uVar2 = FUN_007d98b0(local_5c,uVar2);
  FUN_007d9eb0(local_4c + 0x20,uVar2);
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

