
void FUN_006f8260(error_condition *param_1)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 local_68 [8];
  error_condition local_60 [8];
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855810;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar3;
  FUN_006de390(5);
  bVar1 = std::error_condition::operator==(param_1,local_60);
  if (bVar1) {
    FUN_006d08b0(0x400,"asio close handshake timer cancelled");
  }
  else {
    cVar2 = FUN_006ab7d0(uVar3);
    if (cVar2 == '\0') {
      FUN_006d08b0(0x400,"asio close handshake timer expired");
      uVar4 = make_error_code(local_68,0x17);
      FUN_006daf10(uVar4);
    }
    else {
      local_58 = FUN_006ab780(local_44);
      local_8 = 0;
      local_54 = local_58;
      local_50 = FUN_006dd7f0(local_2c,"asio open handle_close_handshake_timeout error: ",local_58);
      local_8._0_1_ = 1;
      local_4c = local_50;
      FUN_006d4480(0x400,local_50);
      local_8 = (uint)local_8._1_3_ << 8;
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

