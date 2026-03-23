
void __fastcall FUN_0072fb60(int param_1)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar1;
  undefined4 uVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_40 [4];
  undefined4 uStack_3c;
  int iStack_38;
  int iStack_34;
  undefined1 *puStack_30;
  undefined1 *puStack_2c;
  int iStack_28;
  uint uStack_24;
  undefined4 local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859c68;
  local_10 = ExceptionList;
  uStack_24 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iStack_28 = param_1 + 8;
  puStack_2c = (undefined1 *)0x72fb94;
  local_14 = param_1;
  iStack_28 = FUN_00417780();
  puStack_2c = &stack0x00000004;
  puStack_30 = (undefined1 *)(local_14 + 8);
  iStack_34 = local_14;
  iStack_38 = 0x72fbac;
  iStack_28 = FUN_0072f970();
  puStack_2c = (undefined1 *)(local_14 + 8);
  puStack_30 = (undefined1 *)0x72fbbc;
  puStack_2c = (undefined1 *)FUN_004242e0();
  puStack_30 = &stack0x00000004;
  iStack_34 = local_14 + 8;
  iStack_38 = local_14;
  uStack_3c = 0x72fbd4;
  pbVar1 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_0070d600();
  local_1c = abStack_40;
  local_20 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       (abStack_40,pbVar1);
  local_8 = 0;
  local_18 = local_20;
  uVar2 = FUN_00731f80(local_14 + 8);
  uVar2 = FUN_0070d600(local_14,local_14 + 8,&stack0x00000004,uVar2);
  local_8 = 0xffffffff;
  FUN_00731f90(uVar2);
  ExceptionList = local_10;
  return;
}

