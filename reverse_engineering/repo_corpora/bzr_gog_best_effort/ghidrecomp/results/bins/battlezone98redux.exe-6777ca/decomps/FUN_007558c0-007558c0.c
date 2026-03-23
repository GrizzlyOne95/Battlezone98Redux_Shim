
void FUN_007558c0(undefined4 param_1,undefined4 param_2,char *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 extraout_var;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e248;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  basic_string<>("cNetFriendsGog::OnGameInvitationReceived called :");
  local_8 = 0;
  uVar2 = extraout_var;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,param_3);
  uVar2 = FUN_0041f870(uVar1,uVar2);
  FUN_007d6a70(uVar2);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

