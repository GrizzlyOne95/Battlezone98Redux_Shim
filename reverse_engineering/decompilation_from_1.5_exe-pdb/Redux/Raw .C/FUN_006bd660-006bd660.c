
void FUN_006bd660(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 local_a4 [4];
  undefined1 local_a0 [4];
  uint local_9c;
  undefined1 local_98 [88];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_40 [24];
  undefined1 local_28 [16];
  undefined1 local_18 [4];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008513c8;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_9c = 0;
  FUN_006bd380(local_98,local_14);
  uVar1 = FUN_004170c0();
  uVar1 = FUN_0041f870(uVar1);
  FUN_006bd400(local_98,uVar1);
  FUN_006bd580(local_98,local_28);
  basic_string<>();
  local_8 = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::resize
            (local_40,0x10);
  puVar2 = (undefined4 *)FID_conflict_begin(local_a4);
  FUN_006da660(local_a0,local_28,local_18,*puVar2);
  basic_string<>(local_40);
  local_9c = local_9c | 1;
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

