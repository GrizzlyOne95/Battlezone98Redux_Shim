
int FUN_007001b0(undefined1 param_1,
                basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                *param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_54 [16];
  undefined1 local_44 [16];
  code *local_34;
  undefined4 local_30;
  code *local_2c;
  undefined4 local_28;
  int local_24;
  int local_20;
  undefined4 local_1c;
  void *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856418;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00704ec0(param_1,param_3,param_4);
  local_8 = 0;
  local_20 = local_14;
  local_2c = FUN_007099f0;
  local_28 = 0;
  uVar2 = FUN_0070ed50(local_44,FUN_007099f0,0,&local_20,_1_exref,_2_exref,uVar1);
  FUN_0070ede0(uVar2);
  local_8._0_1_ = 1;
  local_24 = local_14;
  local_34 = FUN_0070a470;
  local_30 = 0;
  uVar2 = FUN_0070eda0(local_54,FUN_0070a470,0,&local_24,_1_exref);
  FUN_0070ee50(uVar2);
  local_8._0_1_ = 2;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (local_14 + 0x900),param_2);
  local_8._0_1_ = 3;
  FUN_0068b0a0();
  local_8._0_1_ = 4;
  FUN_006caaf0();
  local_8._0_1_ = 5;
  FUN_006caaf0();
  local_8._0_1_ = 6;
  FUN_006caaf0();
  local_8._0_1_ = 7;
  FUN_006caaf0();
  local_8._0_1_ = 8;
  FUN_006caaf0();
  local_8._0_1_ = 9;
  FUN_006caaf0();
  local_8._0_1_ = 10;
  FUN_006caaf0();
  local_8._0_1_ = 0xb;
  FUN_006caaf0();
  local_8._0_1_ = 0xc;
  FUN_006caaf0();
  local_8._0_1_ = 0xd;
  FUN_006caaf0();
  local_8._0_1_ = 0xe;
  *(undefined4 *)(local_14 + 0xa10) = 5000;
  *(undefined4 *)(local_14 + 0xa14) = 5000;
  *(undefined4 *)(local_14 + 0xa18) = 5000;
  *(undefined **)(local_14 + 0xa1c) = &DAT_01e84800;
  *(undefined4 *)(local_14 + 0xa20) = 0;
  *(undefined4 *)(local_14 + 0xa24) = 0;
  FUN_006b4800();
  local_8._0_1_ = 0xf;
  FUN_006b4800();
  local_8._0_1_ = 0x10;
  FUN_006caaf0();
  local_8 = CONCAT31(local_8._1_3_,0x11);
  local_18 = operator_new(8);
  if (local_18 == (void *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = FUN_00704870();
  }
  FUN_0070eec0(local_1c);
  local_8._0_1_ = 0x12;
  FUN_0068b0a0();
  local_8._0_1_ = 0x13;
  FUN_0068b0a0();
  local_8._0_1_ = 0x14;
  basic_string<>();
  local_8._0_1_ = 0x15;
  FUN_0068b0a0();
  local_8._0_1_ = 0x16;
  FUN_00705260();
  local_8._0_1_ = 0x17;
  *(undefined4 *)(local_14 + 0x4a9c) = 0;
  vector<>();
  local_8._0_1_ = 0x18;
  vector<>();
  local_8._0_1_ = 0x19;
  *(undefined1 *)(local_14 + 0x4ab8) = 0;
  *(undefined1 *)(local_14 + 0x4ab9) = 1;
  FUN_006b8100();
  local_8._0_1_ = 0x1a;
  FUN_006b8e60();
  local_8._0_1_ = 0x1b;
  FUN_0068b0a0();
  local_8._0_1_ = 0x1c;
  basic_string<>();
  local_8._0_1_ = 0x1d;
  vector<>();
  local_8._0_1_ = 0x1e;
  *(undefined1 *)(local_14 + 0x4be0) = param_1;
  *(undefined4 *)(local_14 + 0x4be4) = param_3;
  *(undefined4 *)(local_14 + 0x4be8) = param_4;
  *(undefined4 *)(local_14 + 0x4bec) = param_5;
  *(undefined2 *)(local_14 + 0x4bf0) = 0x3ee;
  basic_string<>();
  local_8._0_1_ = 0x1f;
  *(undefined2 *)(local_14 + 0x4c0c) = 0x3ee;
  basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,0x20);
  FUN_006ab750();
  *(undefined1 *)(local_14 + 0x4c30) = 0;
  *(undefined4 *)(local_14 + 0x4c34) = 0;
  *(undefined1 *)(local_14 + 0x4c38) = 0;
  FUN_006d08b0(0x400,"connection constructor");
  ExceptionList = local_10;
  return local_14;
}

