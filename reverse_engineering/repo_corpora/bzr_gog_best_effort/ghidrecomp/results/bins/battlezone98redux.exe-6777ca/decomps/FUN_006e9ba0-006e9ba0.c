
void FUN_006e9ba0(undefined4 *param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined1 auStack_118 [160];
  undefined1 local_78 [8];
  undefined1 local_70 [8];
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined1 *local_54;
  undefined4 local_50;
  undefined4 local_4c;
  int local_48;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008549db;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  FUN_006d08b0(0x400,"connection handle_transport_init");
  local_50 = *param_1;
  local_4c = param_1[1];
  if (*(int *)(local_48 + 0xa24) != 1) {
    FUN_006d08b0(0x400,"handle_transport_init must be called from transport init state");
    puVar3 = (undefined4 *)make_error_code(local_78,9,uVar2);
    local_50 = *puVar3;
    local_4c = puVar3[1];
  }
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    if (*(char *)(local_48 + 0x4be0) == '\0') {
      *(undefined4 *)(local_48 + 0xa24) = 3;
      local_58 = FUN_006f88c0(local_70,0xd);
      FID_conflict_operator_(local_58);
      FUN_006ca8c0();
      FUN_006f8390();
    }
    else {
      *(undefined4 *)(local_48 + 0xa24) = 2;
      FUN_006f8080(1);
    }
  }
  else {
    FUN_00574400(3,1);
    local_8 = 0;
    if (&stack0x00000000 == (undefined1 *)0x128) {
      local_54 = (undefined1 *)0x0;
    }
    else {
      local_54 = auStack_118;
    }
    local_68 = FUN_006ab780(local_2c);
    local_8._0_1_ = 1;
    local_5c = local_68;
    uVar4 = FUN_004bc590(local_54,"handle_transport_init received error: ",local_68);
    FUN_00574730(uVar4);
    local_8._0_1_ = 0;
    ~basic_string<>();
    local_64 = GetPolicy(local_44);
    local_8._0_1_ = 2;
    local_60 = local_64;
    FUN_006d46a0(0x10,local_64);
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    FUN_006daf10(&local_50);
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

