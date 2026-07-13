
void FUN_00708d60(undefined4 *param_1,uint param_2)

{
  char cVar1;
  bool bVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  uint uStack_254;
  undefined1 local_174 [8];
  undefined1 local_16c [16];
  undefined1 local_15c [20];
  error_condition local_148 [56];
  undefined4 local_110;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_c8;
  int local_c4;
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008573ed;
  local_10 = ExceptionList;
  uStack_254 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_254;
  ExceptionList = &local_10;
  local_18 = uStack_254;
  FUN_006d08b0(0x400,"connection handle_read_handshake");
  local_d4 = *param_1;
  local_d0 = param_1[1];
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    FUN_006d1110(local_c4 + 0xa28);
    local_8 = 0;
    if (*(int *)(local_c4 + 0xa20) == 0) {
      if (*(int *)(local_c4 + 0xa24) != 2) {
        puVar3 = (undefined4 *)make_error_code(local_174,9);
        local_d4 = *puVar3;
        local_d0 = puVar3[1];
      }
    }
    else {
      if (*(int *)(local_c4 + 0xa20) == 3) {
        FUN_006d08b0(0x400,"handle_read_handshake invoked after connection was closed");
        local_8 = 0xffffffff;
        FUN_006d1140();
        goto LAB_00709647;
      }
      puVar3 = (undefined4 *)make_error_code(local_15c,9);
      local_d4 = *puVar3;
      local_d0 = puVar3[1];
    }
    local_8 = 0xffffffff;
    FUN_006d1140();
  }
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    if (param_2 < 0x4001) {
      local_c8 = 0;
      local_8 = 1;
      local_110 = FUN_006b8220(local_c4 + 0xa30,param_2);
      local_c8 = local_110;
      FUN_00709028();
      return;
    }
    FUN_006d47b0(0x20,"Fatal boundaries checking error.");
    uVar4 = make_error_code(local_16c,1);
    FUN_006daf10(uVar4);
  }
  else {
    FUN_006de390(7);
    bVar2 = std::error_condition::operator==((error_condition *)&local_d4,local_148);
    if ((bVar2) && (*(int *)(local_c4 + 0xa20) == 3)) {
      FUN_006d08b0(0x400,"got (expected) eof/state error from closed con");
    }
    else {
      FUN_006f90a0(0x10,"handle_read_handshake",&local_d4);
      FUN_006daf10(&local_d4);
    }
  }
LAB_00709647:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

