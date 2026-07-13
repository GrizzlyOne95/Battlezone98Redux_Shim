
void FUN_004da0b0(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_124 [64];
  undefined4 local_e4;
  undefined4 *local_e0;
  char *local_dc;
  uint local_d8;
  int local_d4;
  undefined4 local_d0;
  int local_cc;
  int local_c8;
  undefined4 local_c4;
  uint local_c0;
  void *local_bc;
  int local_b8;
  void *local_b4;
  undefined4 local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  undefined4 *local_98;
  undefined4 local_94 [16];
  undefined4 local_54 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a0a7;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004dab30(local_14);
  local_8 = 0;
  FUN_004b7950();
  local_8._0_1_ = 1;
  *local_98 = GameObject::vftable;
  local_98[6] = GameObject::vftable;
  FUN_00477ce0();
  FUN_00477ce0();
  local_98[0x3d] = param_1;
  local_98[0x3e] = param_2;
  FUN_0049f1a0();
  *(undefined4 **)(local_98[0x3d] + 0x8c) = local_98;
  if (DAT_00917a74 == 0) {
    local_b4 = operator_new(0xc);
    local_8._0_1_ = 2;
    if (local_b4 == (void *)0x0) {
      local_c8 = 0;
    }
    else {
      local_c8 = vector<>();
    }
    local_d4 = local_c8;
    local_8._0_1_ = 1;
    DAT_00917a74 = local_c8;
    FUN_004bae50(0x1000);
  }
  if ((*(uint *)(local_98[0x3d] + 0x14) & 0x10) != 0) {
    DAT_00917afc = local_98;
    DAT_00917b00 = FUN_0047e9a0(local_98[0x3d]);
    DAT_00917a70 = FUN_005e0bc0(DAT_00917b00);
  }
  local_98[0x57] = DAT_008e8660;
  DAT_008e8660 = DAT_008e8660 + 1;
  local_98[100] = 0;
  local_98[0x65] = 0;
  local_98[0x5f] = 0;
  local_98[0x5d] = 0xffffffff;
  local_98[0x5e] = 0xffffffff;
  uVar1 = FUN_0047e9a0(local_98[0x3d]);
  FUN_004db4f0(uVar1);
  if (*(int *)(local_98[0x3d] + 0x78) == 0) {
    uVar1 = FUN_0062c890(param_1);
    local_98[0x3c] = uVar1;
    local_e0 = local_98;
    FUN_0041fe40(&local_e0);
    if (local_98[0x3c] != 0) {
      FUN_00820180(local_98 + 0x42,local_98[0x3c] + 8,1,local_98[0x3d] + 0x20);
    }
  }
  else {
    local_98[0x3c] = 0;
    puVar2 = (undefined4 *)FUN_0062e070(local_124,local_98[0x3d],0);
    puVar4 = local_54;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar2 = local_54;
    puVar4 = local_94;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
    FUN_00820180(local_98 + 0x42,local_98[0x3d] + 0xa0,1,local_94);
  }
  *(undefined1 *)(local_98 + 0x27) = 0;
  local_98[0x28] = 0;
  local_98[0x32] = 0;
  local_98[0x33] = 0;
  local_98[0x34] = 0;
  local_98[0x35] = 0;
  local_98[0x36] = 0;
  local_98[0x37] = 0;
  local_98[0x38] = 0;
  local_98[0x39] = 0;
  local_98[0x33] = 0;
  puVar2 = local_98 + 0x32;
  puVar4 = local_98 + 0x2a;
  for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  local_98[0x3f] = 0;
  local_98[0x40] = 0;
  local_98[0x41] = 1;
  local_98[0x3b] = 0;
  local_98[0x61] = 0;
  FUN_004d9730(param_2 + 100);
  local_98[0x77] = 0xf149f2ca;
  local_98[0x76] = 0xf149f2ca;
  local_98[0x79] = 0xf149f2ca;
  local_98[0x78] = 0xf149f2ca;
  local_98[0x7b] = 0xf149f2ca;
  local_98[0x7a] = 0xf149f2ca;
  local_98[0x7d] = 0;
  local_98[0x26] = 0;
  local_98[0x7e] = 0;
  local_98[0x7f] = 0xf149f2ca;
  uVar1 = FUN_0047e9a0(local_98[0x3d],param_2);
  iVar3 = FUN_004e1c60(uVar1);
  local_98[0x82] = (float)iVar3;
  FUN_004a76a0(local_98[0x82]);
  local_98[0x80] = 0x3f800000;
  FUN_004d96d0(*(undefined4 *)(param_2 + 0x5c));
  uVar1 = FUN_0046d060();
  FUN_004a7700(uVar1);
  iVar3 = FUN_0046d060();
  if (iVar3 < 1) {
    local_c4 = 0;
  }
  else {
    local_c4 = 0x3f800000;
  }
  local_98[0x83] = local_c4;
  local_a8 = *(int *)(param_2 + 0xc4);
  local_e4 = 5;
  local_98[0x86] = 0;
  for (local_a4 = 0; local_a4 < 5; local_a4 = local_a4 + 1) {
    local_cc = local_a8 % 10;
    if (local_cc < 1) {
      local_c0 = 0;
    }
    else {
      local_c0 = 0x10;
    }
    local_d8 = local_c0;
    local_98[0x86] = (int)local_98[0x86] >> 1 | local_c0;
    local_a8 = local_a8 / 10;
  }
  if (*(float *)(param_2 + 200) <= 0.0) {
    iVar3 = FUN_00462400();
    local_98[0x59] = *(undefined4 *)(iVar3 + 0xc);
  }
  else {
    local_98[0x59] = *(undefined4 *)(param_2 + 200);
  }
  uVar1 = FUN_00822d90();
  local_98[0x5a] = uVar1;
  local_98[0x66] = 0;
  local_98[0x67] = 0;
  local_98[0x68] = 0;
  for (local_9c = 0; local_9c < 5; local_9c = local_9c + 1) {
    local_b8 = *(int *)(param_2 + 0xf8 + local_9c * 4);
    local_dc = (char *)(param_2 + 0xe4 + local_9c * 4);
    local_a0 = 0;
    local_ac = 0;
    if (*local_dc != '\0') {
      if (local_98[0x68] == 0) {
        local_bc = operator_new(0x3c);
        local_8._0_1_ = 3;
        if (local_bc == (void *)0x0) {
          local_b0 = 0;
        }
        else {
          local_b0 = FUN_004d9800(local_98);
        }
        local_d0 = local_b0;
        local_8._0_1_ = 1;
        local_98[0x68] = local_b0;
      }
      local_a0 = FUN_004d9ca0(local_98[0x3d],param_2 + 0xe4 + local_9c * 4);
      if (local_b8 != 0) {
        if (local_a0 == 0) {
          FUN_007d6830("Object \'%.8s\' slot #%d: no hardpoint named \'%s\'",param_2 + 0x30,local_9c
                       ,param_2 + 0xe4 + local_9c * 4);
        }
        else {
          local_ac = FUN_006121c0(local_98[0x3d],local_a0);
          if (local_ac == 0) {
            FUN_007d6830("Object \'%.8s\' slot #%d: couldn\'t add weapon \'%.8s\' to hardpoint \'%s\'"
                         ,param_2 + 0x30,local_9c,*(int *)(param_2 + 0xf8 + local_9c * 4) + 0x18,
                         param_2 + 0xe4 + local_9c * 4);
          }
        }
      }
      FUN_00472420(local_9c,local_a0);
      FUN_004a77a0(local_9c,local_ac);
    }
  }
  if (local_98[0x68] != 0) {
    FUN_004d9950(0xffffffff);
    FUN_004d9880(0xffffffff);
    FUN_004d9970();
  }
  local_98[0x3a] = 0;
  local_98[0x87] = 0;
  local_98[0x89] = 0;
  local_98[0x88] = 0;
  uVar1 = get();
  FUN_00477530(uVar1);
  *(undefined1 *)((int)local_98 + 0x189) = 0;
  *(undefined1 *)((int)local_98 + 0x18a) = 0;
  *(undefined1 *)(local_98 + 0x62) = 0;
  local_98[99] = 0;
  FUN_00444970(local_98 + 0x45);
  FUN_004db100();
  FUN_004d4ac0(local_98);
  *(undefined8 *)(local_98 + 0x16) = 0xbff0000000000000;
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

