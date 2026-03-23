
void FUN_00702230(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar3;
  undefined4 extraout_var;
  undefined4 uVar4;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined1 local_d4 [24];
  undefined1 local_bc [24];
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008568dc;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  basic_string<>("Sec-WebSocket-Key");
  local_8 = 0;
  uVar4 = extraout_var;
  pbVar3 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_006b7490(local_8c);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar3);
  local_8._0_1_ = 2;
  ~basic_string<>(uVar2,uVar4);
  FUN_007058f0(&local_dc,local_2c);
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    basic_string<>("Sec-WebSocket-Accept");
    local_8._0_1_ = 3;
    FUN_006b7810(local_44,local_2c);
    local_8._0_1_ = 2;
    ~basic_string<>();
    basic_string<>("websocket");
    local_8._0_1_ = 4;
    basic_string<>("Upgrade");
    local_8._0_1_ = 5;
    FUN_006b7570(local_5c,local_74);
    local_8._0_1_ = 4;
    ~basic_string<>();
    local_8._0_1_ = 2;
    ~basic_string<>();
    basic_string<>("upgrade");
    local_8._0_1_ = 6;
    basic_string<>("Connection");
    local_8._0_1_ = 7;
    FUN_006b7570(local_a4,local_d4);
    local_8._0_1_ = 6;
    ~basic_string<>();
    local_8._0_1_ = 2;
    ~basic_string<>();
    cVar1 = FUN_0041f890();
    if (cVar1 == '\0') {
      basic_string<>("Sec-WebSocket-Protocol");
      local_8._0_1_ = 8;
      FUN_006b7810(local_bc,param_3);
      local_8._0_1_ = 2;
      ~basic_string<>();
    }
    FUN_006ab750();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  else {
    *param_1 = local_dc;
    param_1[1] = local_d8;
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

