
void FUN_007559b0(undefined4 param_1,undefined4 param_2,char *param_3)

{
  bool bVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  int local_14c [48];
  undefined1 local_8c [23];
  char local_75;
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c4cb;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  basic_string<>("cNetFriendsGog::OnGameJoinRequested called :");
  local_8 = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_44,param_3);
  uVar3 = FUN_0041f870(uVar2);
  FUN_007d6a70(uVar3);
  FUN_0073a6b0();
  basic_string<>();
  local_8._0_1_ = 1;
  basic_string<>(param_3);
  local_8._0_1_ = 2;
  FUN_004203f0(local_74,3,1);
  local_8._0_1_ = 4;
  ~basic_string<>();
  FUN_004272a0(local_14c,local_5c,0x3d);
  FUN_0073ba90(local_14c,local_8c);
  basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,5);
  bVar1 = std::ios_base::eof((ios_base *)((int)local_14c + *(int *)(local_14c[0] + 4)));
  if (!bVar1) {
    local_75 = ' ';
    std::basic_istream<char,struct_std::char_traits<char>_>::get
              ((basic_istream<char,struct_std::char_traits<char>_> *)local_14c,&local_75);
    if (local_75 == ',') {
      FUN_004272a0(local_14c,local_2c,0);
    }
  }
  uVar3 = FUN_0073a710(&param_1);
  puVar5 = local_2c;
  puVar4 = local_8c;
  FUN_00764760(puVar4,puVar5,uVar3);
  FUN_007408c0(puVar4,puVar5,uVar3);
  local_8._0_1_ = 4;
  ~basic_string<>();
  local_8._0_1_ = 1;
  FUN_00417f10();
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

