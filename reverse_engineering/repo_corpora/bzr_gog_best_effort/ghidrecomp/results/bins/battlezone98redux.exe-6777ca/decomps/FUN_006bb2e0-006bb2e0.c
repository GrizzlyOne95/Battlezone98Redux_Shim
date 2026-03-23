
void FUN_006bb2e0(undefined4 param_1,undefined4 *param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  undefined1 auStack_118 [168];
  undefined1 local_70 [8];
  undefined4 local_68;
  undefined4 local_60;
  undefined1 *local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined1 *local_50;
  uint local_4c;
  undefined1 local_48 [28];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00851273;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_4c = 0;
  local_14 = uVar1;
  FUN_00574400(3,1);
  local_8 = 0;
  FUN_004fbb60(uVar1);
  puVar3 = &local_58;
  puVar5 = local_48;
  FUN_00421ec0(puVar5,puVar3);
  FUN_006cad40(puVar5,puVar3);
  iVar2 = FUN_00667170();
  if (iVar2 == 0) {
    puVar3 = (undefined4 *)FUN_006ab750();
    uVar4 = puVar3[1];
    *param_2 = *puVar3;
    param_2[1] = uVar4;
    if (&stack0x00000000 == (undefined1 *)0x128) {
      local_50 = (undefined1 *)0x0;
    }
    else {
      local_50 = auStack_118;
    }
    FUN_006da360(local_50,local_48);
    GetPolicy(param_1);
    local_4c = local_4c | 1;
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  else {
    puVar3 = (undefined4 *)make_error_code(local_70,3);
    uVar4 = puVar3[1];
    *param_2 = *puVar3;
    param_2[1] = uVar4;
    if (&stack0x00000000 == (undefined1 *)0x128) {
      local_5c = (undefined1 *)0x0;
    }
    else {
      local_5c = auStack_118;
    }
    local_68 = FUN_004486a0(local_2c);
    local_8._0_1_ = 1;
    local_60 = local_68;
    uVar4 = FUN_004bc590(local_5c,"Error getting remote endpoint: ",local_58,local_54,&DAT_00884900,
                         local_68,&DAT_008848a8);
    uVar4 = FUN_006da310(uVar4);
    uVar4 = FUN_004bc590(uVar4);
    uVar4 = FUN_00574730(uVar4);
    FUN_004bc590(uVar4);
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    GetPolicy(param_1);
    local_4c = local_4c | 1;
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

