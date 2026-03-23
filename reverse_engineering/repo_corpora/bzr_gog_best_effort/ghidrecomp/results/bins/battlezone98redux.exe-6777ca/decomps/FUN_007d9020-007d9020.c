
void FUN_007d9020(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  undefined *puVar7;
  undefined1 local_e0 [24];
  undefined1 local_c8 [16];
  undefined1 local_b8 [8];
  undefined1 local_b0 [8];
  undefined1 local_a8 [8];
  undefined1 local_a0 [8];
  undefined1 local_98 [8];
  undefined1 local_90 [8];
  undefined1 local_88 [8];
  undefined1 local_80 [8];
  undefined1 local_78 [8];
  undefined1 local_70 [10];
  undefined1 local_66 [4];
  undefined1 local_62 [3];
  undefined1 local_5f [3];
  undefined1 local_5c [2];
  undefined1 local_5a [2];
  undefined4 local_58;
  undefined4 local_54;
  undefined1 local_4e [2];
  int local_4c;
  undefined1 local_47;
  undefined1 local_46;
  undefined1 local_45;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863113;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  basic_string<>("unnamed-grammar");
  local_8 = 0;
  FUN_007d8b50(local_4c + 0x20,local_44);
  local_8._0_1_ = 2;
  ~basic_string<>(uVar1);
  basic_string<>("unnamed-rule");
  local_8._0_1_ = 3;
  FUN_007d8ba0(local_2c);
  local_8 = CONCAT31(local_8._1_3_,5);
  ~basic_string<>();
  local_46 = 1;
  local_47 = 1;
  local_45 = 0x20;
  local_54 = 0;
  local_58 = 0;
  uVar2 = FUN_007d9ce0(local_5a,&local_46,0);
  puVar7 = &DAT_008716db;
  uVar3 = FUN_007d9d50(local_5f,&DAT_0260c0a4,0);
  uVar2 = FUN_007d98b0(local_70,uVar3,puVar7,uVar2);
  uVar3 = FUN_007d9ce0(local_5c,&local_47,0);
  puVar6 = &local_45;
  puVar5 = local_b8;
  uVar4 = 0;
  uVar2 = FUN_007d9df0(local_4e,&DAT_0260c048,&DAT_0260c07f,0,puVar5,puVar6,uVar3,uVar2);
  FUN_007d9e10(local_66,uVar2,uVar4);
  uVar2 = FUN_007d9e50(puVar5,puVar6);
  uVar3 = 0;
  uVar2 = FUN_007d98f0(local_a0,&DAT_0260c07f,&local_54,0,uVar2);
  uVar2 = FUN_007d98f0(local_80,&DAT_0260c048,&local_58,uVar2);
  uVar2 = FUN_007d9d90(local_c8,uVar2);
  uVar2 = FUN_007d9db0(local_e0,uVar2,uVar3);
  uVar2 = FUN_007d98b0(local_b0,uVar2);
  uVar2 = FUN_007d98b0(local_90,uVar2);
  puVar7 = &DAT_008716db;
  uVar3 = FUN_007d9d50(local_62,&DAT_0260c08b,0);
  uVar2 = FUN_007d98b0(local_98,uVar3,puVar7,uVar2);
  uVar2 = FUN_007d98b0(local_a8,uVar2);
  uVar2 = FUN_007d98b0(local_78,uVar2);
  uVar2 = FUN_007d98b0(local_88,uVar2);
  FUN_007d9e90(local_4c + 0x20,uVar2);
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

