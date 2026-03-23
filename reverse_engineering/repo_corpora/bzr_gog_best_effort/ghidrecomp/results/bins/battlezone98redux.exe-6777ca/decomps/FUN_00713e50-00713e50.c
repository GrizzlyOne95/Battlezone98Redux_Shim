
void FUN_00713e50(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  bool bVar2;
  undefined4 *puVar3;
  uint uStack_1f4;
  undefined1 local_1bc [8];
  undefined1 local_1b4 [40];
  error_condition local_18c [20];
  undefined4 local_178;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  int local_104;
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857ee8;
  local_10 = ExceptionList;
  uStack_1f4 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_1f4;
  ExceptionList = &local_10;
  local_18 = uStack_1f4;
  FUN_006d08b0(0x400,"handle_read_http_response");
  local_10c = *param_1;
  local_108 = param_1[1];
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    FUN_006d1110(local_104 + 0xa28);
    local_8 = 0;
    if (*(int *)(local_104 + 0xa20) == 0) {
      if (*(int *)(local_104 + 0xa24) != 4) {
        puVar3 = (undefined4 *)make_error_code(local_1bc,9);
        local_10c = *puVar3;
        local_108 = puVar3[1];
      }
    }
    else {
      if (*(int *)(local_104 + 0xa20) == 3) {
        FUN_006d08b0(0x400,"handle_read_http_response invoked after connection was closed");
        local_8 = 0xffffffff;
        FUN_006d1140();
        goto LAB_00714635;
      }
      puVar3 = (undefined4 *)make_error_code(local_1b4,9);
      local_10c = *puVar3;
      local_108 = puVar3[1];
    }
    local_8 = 0xffffffff;
    FUN_006d1140();
  }
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    local_110 = 0;
    local_8 = 1;
    local_178 = FUN_006b8f70(local_104 + 0xa30,param_2);
    local_110 = local_178;
    FUN_00714145();
    return;
  }
  FUN_006de390(7);
  bVar2 = std::error_condition::operator==((error_condition *)&local_10c,local_18c);
  if ((bVar2) && (*(int *)(local_104 + 0xa20) == 3)) {
    FUN_006d08b0(0x400,"got (expected) eof/state error from closed con");
  }
  else {
    FUN_006f90a0(0x10,"handle_read_http_response",&local_10c);
    FUN_006daf10(&local_10c);
  }
LAB_00714635:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

