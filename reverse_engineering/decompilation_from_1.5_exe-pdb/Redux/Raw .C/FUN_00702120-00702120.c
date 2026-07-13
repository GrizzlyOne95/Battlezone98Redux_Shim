
void __thiscall FUN_00702120(undefined4 param_1,undefined4 param_2,allocator<char> *param_3)

{
  char cVar1;
  undefined4 uVar2;
  char *pcVar3;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845608;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = FUN_006b81b0(&DAT_008997ec,local_14,param_1);
  cVar1 = operator!=<>(uVar2);
  if (cVar1 == '\0') {
    pcVar3 = "HTTP/1.1";
    uVar2 = std::allocator<char>::allocator<char>(param_3);
    cVar1 = operator!=<>(uVar2,pcVar3);
    if (cVar1 == '\0') {
      basic_string<>("Sec-WebSocket-Key");
      local_8 = 0;
      FUN_006b7490(local_2c);
      cVar1 = FUN_0041f890();
      local_8 = 0xffffffff;
      ~basic_string<>();
      if (cVar1 == '\0') {
        FUN_006ab750();
      }
      else {
        make_error_code(param_2,0x15);
      }
    }
    else {
      make_error_code(param_2,0x13);
    }
  }
  else {
    make_error_code(param_2,0x12);
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

