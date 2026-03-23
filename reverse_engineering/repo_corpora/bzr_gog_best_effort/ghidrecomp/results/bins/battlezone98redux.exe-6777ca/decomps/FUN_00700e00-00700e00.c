
void __thiscall FUN_00700e00(undefined4 param_1,undefined4 param_2,allocator<char> *param_3)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  undefined4 uVar5;
  char *pcVar6;
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008565db;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar5 = FUN_006b81b0(&DAT_008997ec,local_14,param_1);
  cVar4 = operator!=<>(uVar5);
  if (cVar4 != '\0') {
    make_error_code(param_2,0x12);
    goto LAB_00700fca;
  }
  pcVar6 = "HTTP/1.1";
  uVar5 = std::allocator<char>::allocator<char>(param_3);
  cVar4 = operator!=<>(uVar5,pcVar6);
  if (cVar4 != '\0') {
    make_error_code(param_2,0x13);
    goto LAB_00700fca;
  }
  basic_string<>("Sec-WebSocket-Key1");
  local_8 = 0;
  bVar3 = false;
  bVar2 = false;
  FUN_006b7490(local_2c);
  cVar4 = FUN_0041f890();
  if (cVar4 == '\0') {
    basic_string<>("Sec-WebSocket-Key2");
    local_8 = 1;
    bVar3 = true;
    bVar2 = false;
    FUN_006b7490(local_44);
    cVar4 = FUN_0041f890();
    if (cVar4 != '\0') goto LAB_00700f46;
    basic_string<>("Sec-WebSocket-Key3");
    local_8 = 2;
    bVar3 = true;
    bVar2 = true;
    FUN_006b7490(local_5c);
    cVar4 = FUN_0041f890();
    if (cVar4 != '\0') goto LAB_00700f46;
    bVar1 = false;
  }
  else {
LAB_00700f46:
    bVar1 = true;
  }
  local_8 = 1;
  if (bVar2) {
    ~basic_string<>();
  }
  local_8 = 0;
  if (bVar3) {
    ~basic_string<>();
  }
  local_8 = 0xffffffff;
  ~basic_string<>();
  if (bVar1) {
    make_error_code(param_2,0x15);
  }
  else {
    FUN_006ab750();
  }
LAB_00700fca:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

