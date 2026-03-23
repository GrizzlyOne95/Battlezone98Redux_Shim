
void __thiscall FUN_006d42f0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008533c8;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  cVar1 = FUN_006ab7d0(local_14,param_1);
  if (cVar1 == '\0') {
    make_error_code(param_2,9);
  }
  else {
    basic_string<>("HTTP/1.1");
    local_8 = 0;
    puVar2 = local_2c;
    FUN_00421ec0(puVar2);
    FUN_006b7470(puVar2);
    local_8 = 0xffffffff;
    ~basic_string<>();
    basic_string<>("CONNECT");
    local_8 = 1;
    puVar2 = local_44;
    FUN_00421ec0(puVar2);
    FUN_006b8960(puVar2);
    local_8 = 0xffffffff;
    ~basic_string<>();
    uVar3 = param_3;
    FUN_00421ec0(param_3);
    FUN_006b8ad0(uVar3);
    basic_string<>(&DAT_00897554);
    local_8 = 2;
    puVar2 = local_5c;
    FUN_00421ec0(puVar2,param_3);
    FUN_006b7810(puVar2,param_3);
    local_8 = 0xffffffff;
    ~basic_string<>();
    FUN_006ab750();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

