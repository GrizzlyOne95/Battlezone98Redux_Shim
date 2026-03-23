
undefined1 * __thiscall FUN_006be3e0(undefined1 *param_1,undefined1 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_2c [8];
  undefined1 local_24 [8];
  undefined1 local_1c [8];
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00851539;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  local_14 = param_1;
  basic_string<>(uVar1);
  local_8 = 0;
  FUN_006adfa0();
  local_8._0_1_ = 1;
  FUN_006adfa0();
  local_8._0_1_ = 2;
  FUN_006cb0a0(local_14 + 0x24);
  local_8._0_1_ = 3;
  FUN_006cb0a0(local_14 + 0x24);
  local_8._0_1_ = 4;
  FUN_006cb0a0(local_14 + 0x24);
  local_8._0_1_ = 5;
  FUN_006cb210(local_14 + 0x24);
  local_8._0_1_ = 6;
  FUN_006cb540();
  local_8._0_1_ = 7;
  FUN_0068b0a0();
  local_8._0_1_ = 8;
  local_14[0x2e8] = param_2;
  basic_string<>();
  local_8._0_1_ = 9;
  basic_string<>();
  local_8._0_1_ = 10;
  local_14[0x324] = 1;
  FUN_006cb470();
  FUN_006cb470();
  FUN_00421c40();
  local_8._0_1_ = 0xb;
  basic_string<>();
  local_8._0_1_ = 0xc;
  basic_string<>();
  local_8._0_1_ = 0xd;
  basic_string<>();
  local_8._0_1_ = 0xe;
  basic_string<>();
  local_8._0_1_ = 0xf;
  basic_string<>();
  local_8._0_1_ = 0x10;
  basic_string<>();
  local_8._0_1_ = 0x11;
  basic_string<>();
  local_8._0_1_ = 0x12;
  FUN_0066ae30();
  local_8 = CONCAT31(local_8._1_3_,0x13);
  FUN_006cb470();
  local_14[0xc34] = 0;
  local_14[0x2d8] = 0;
  *(undefined4 *)(local_14 + 0x2dc) = 0;
  *(undefined4 *)(local_14 + 0xc38) = 0;
  *(undefined4 *)(local_14 + 0xc3c) = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (local_14 + 0xc),s_ws___battlezone98mp_webdev_rebel_008f0690);
  FUN_006cb140(&DAT_0260b0c0);
  uVar2 = FUN_006db740(local_24,FUN_006c32a0,local_14,*DAT_0260b098);
  FUN_006db780(uVar2);
  FUN_006b29f0(2);
  FUN_006cb0f0(local_1c);
  uVar2 = FUN_006db740(local_2c,FUN_006c6a10,local_14,DAT_0260b043);
  FUN_006db780(uVar2);
  FUN_006be750();
  ExceptionList = local_10;
  return local_14;
}

