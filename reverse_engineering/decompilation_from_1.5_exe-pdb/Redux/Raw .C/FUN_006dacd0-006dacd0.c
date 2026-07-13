
void FUN_006dacd0(undefined2 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  char cVar2;
  undefined1 uVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined1 local_4c [8];
  undefined1 local_44 [8];
  undefined4 local_3c;
  undefined4 local_38 [2];
  int local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853900;
  local_10 = ExceptionList;
  uVar4 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar4;
  cVar2 = FUN_006d4590(0x400);
  if (cVar2 != '\0') {
    FUN_006d08b0(0x400,"connection close");
  }
  local_3c = 0x7b;
  local_38[0] = FUN_004170c0(uVar4);
  puVar5 = (undefined4 *)_Min_value<>(local_38,&local_3c);
  FUN_006e0b60(param_2,0,*puVar5);
  local_8 = 0;
  FUN_006d1110(local_30 + 0xa28);
  local_8._0_1_ = 1;
  if (*(int *)(local_30 + 0xa20) == 1) {
    uVar3 = FUN_006bbaa0(param_1);
    puVar5 = (undefined4 *)FUN_006e9da0(local_44,param_1,local_2c,0,uVar3);
    uVar1 = puVar5[1];
    *param_3 = *puVar5;
    param_3[1] = uVar1;
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_006d1140();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  else {
    puVar5 = (undefined4 *)make_error_code(local_4c,9);
    uVar1 = puVar5[1];
    *param_3 = *puVar5;
    param_3[1] = uVar1;
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_006d1140();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

