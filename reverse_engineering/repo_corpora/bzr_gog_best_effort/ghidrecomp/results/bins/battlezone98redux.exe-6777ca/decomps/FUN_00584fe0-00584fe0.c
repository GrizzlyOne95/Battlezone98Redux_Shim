
void __thiscall FUN_00584fe0(int param_1,undefined4 *param_2,int param_3)

{
  undefined2 uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined4 auStack_16c [11];
  undefined4 uStack_140;
  undefined1 *puStack_13c;
  undefined4 local_138;
  undefined1 *local_134;
  int *local_130;
  undefined1 local_124 [64];
  undefined1 local_e4 [20];
  undefined1 local_d0 [8];
  undefined1 local_c8 [4];
  undefined4 local_c4;
  undefined1 local_c0 [4];
  int local_bc;
  int local_b8;
  int local_b4;
  ushort local_b0;
  byte local_ad;
  int local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined2 local_a0;
  undefined4 local_9c [16];
  undefined1 local_5c [16];
  undefined4 local_4c;
  undefined1 local_30 [12];
  undefined4 local_24;
  undefined4 local_14;
  undefined4 local_10;
  undefined2 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (param_3 == 0) {
    *(undefined4 *)(*(int *)(param_1 + 0x14) + 0x14) = 0;
  }
  else {
    *(uint *)(*(int *)(param_1 + 0x14) + 0x14) = *(uint *)(param_3 + 0x14) & 0xf0000;
  }
  puVar2 = (undefined4 *)(*(int *)(param_1 + 0x14) + 0x20);
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar2 = *param_2;
    param_2 = param_2 + 1;
    puVar2 = puVar2 + 1;
  }
  local_130 = (int *)0x585046;
  local_ac = param_1;
  iVar4 = FUN_00572a70();
  if (iVar4 != 0) {
    puVar2 = (undefined4 *)(*(int *)(local_ac + 0x14) + 0x20);
    puVar5 = auStack_16c;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
    puVar2 = (undefined4 *)FUN_00625c50(local_e4);
    local_138 = *puVar2;
    local_134 = (undefined1 *)puVar2[1];
    local_a0 = *(undefined2 *)(puVar2 + 2);
    local_130 = (int *)CONCAT22(local_130._2_2_,local_a0);
    puStack_13c = local_124;
    uStack_140 = 0x5850d2;
    local_a8 = local_138;
    local_a4 = local_134;
    local_14 = local_138;
    local_10 = local_134;
    local_c = local_a0;
    puVar2 = (undefined4 *)FUN_00625a30();
    puVar5 = local_9c;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
    puVar2 = local_9c;
    puVar5 = (undefined4 *)(*(int *)(local_ac + 0x14) + 0x20);
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
  }
  local_130 = (int *)**(undefined4 **)(*(int *)(local_ac + 0xc) + 0x34);
  local_134 = *(undefined1 **)(local_ac + 0x14);
  local_138 = 0x58511b;
  FUN_0062d410();
  *(undefined4 *)(local_ac + 0x60) = 0;
  *(undefined4 *)(local_ac + 100) = 0;
  *(undefined4 *)(local_ac + 0x68) = 0;
  *(undefined4 *)(local_ac + 0x6c) = 0;
  *(int *)(local_ac + 0x60) = param_3;
  *(undefined4 *)(local_ac + 100) = *(undefined4 *)(local_ac + 0x14);
  local_130 = *(int **)(local_ac + 0x14);
  local_134 = (undefined1 *)0x585161;
  local_c4 = FUN_0047e9a0();
  *(ushort *)(local_ac + 0x68) =
       *(ushort *)(local_ac + 0x68) & 0xfc3f | ((ushort)local_c4 & 0xf) << 6;
  if (param_3 != 0) {
    local_b0 = (ushort)((*(uint *)(param_3 + 0x14) & 0x30) != 0);
    *(ushort *)(local_ac + 0x68) = *(ushort *)(local_ac + 0x68) & 0xffef | local_b0 << 4;
    local_130 = (int *)param_3;
    local_134 = (undefined1 *)0x5851f5;
    local_b4 = FUN_00479f30();
    if (local_b4 != 0) {
      local_130 = (int *)0x585215;
      local_ad = FUN_004b9830();
      *(ushort *)(local_ac + 0x68) = *(ushort *)(local_ac + 0x68) & 0xffdf | (local_ad & 1) << 5;
    }
  }
  *(ushort *)(local_ac + 0x68) =
       *(ushort *)(local_ac + 0x68) & 0xfff0 | *(ushort *)(*(int *)(local_ac + 0xc) + 0x5c) & 0xf;
  *(undefined4 *)(local_ac + 0x6c) = *(undefined4 *)(*(int *)(local_ac + 0xc) + 0x58);
  *(int *)(local_ac + 0xd8) = param_3;
  if (param_3 == 0) {
    *(undefined4 *)(local_ac + 0xdc) = 0;
  }
  else {
    local_130 = (int *)param_3;
    local_134 = (undefined1 *)0x5852b9;
    uVar3 = FUN_00439cc0();
    *(undefined4 *)(local_ac + 0xdc) = uVar3;
  }
  local_130 = (int *)(*(int *)(local_ac + 0xc) + 0x20);
  local_134 = (undefined1 *)param_3;
  local_138 = 0x5852de;
  FUN_0062cf50();
  local_130 = (int *)(local_ac + 0x18);
  local_134 = (undefined1 *)0x5852f0;
  FUN_00444970();
  *(undefined4 *)(local_ac + 0x78) = *(undefined4 *)(*(int *)(local_ac + 0xc) + 0x50);
  *(undefined4 *)(local_ac + 0x70) = 0;
  if (*(char *)(*(int *)(local_ac + 0xc) + 0x5f) != '\0') {
    local_130 = (int *)local_5c;
    local_134 = (undefined1 *)0x585338;
    FUN_0043a990();
    local_4c = 0x2001;
    local_130 = (int *)local_30;
    local_134 = (undefined1 *)0x58534b;
    FUN_0043a9e0();
    local_24 = 1;
    local_130 = (int *)local_30;
    local_134 = local_5c;
    local_138 = *(undefined4 *)(local_ac + 0x14);
    puStack_13c = (undefined1 *)(*(int *)(local_ac + 0xc) + 0x5f);
    uStack_140 = 0x585379;
    uVar3 = FUN_0043aa30();
    *(undefined4 *)(local_ac + 0x70) = uVar3;
  }
  if (*(int *)(*(int *)(local_ac + 0xc) + 0x70) != 0) {
    local_130 = (int *)(*(int *)(local_ac + 0x14) + 0x20);
    local_134 = (undefined1 *)(local_ac + 0x74);
    local_138 = 0x5853ca;
    (**(code **)(**(int **)(*(int *)(local_ac + 0xc) + 0x70) + 8))();
  }
  local_bc = local_ac;
  local_130 = &local_bc;
  local_134 = (undefined1 *)0x5853e7;
  FUN_00438b80();
  local_130 = (int *)local_c8;
  local_134 = (undefined1 *)0x5853f8;
  puVar2 = (undefined4 *)FUN_0042d8c0();
  *(undefined4 *)(local_ac + 8) = *puVar2;
  local_130 = (int *)0x585408;
  iVar4 = FUN_00572a70();
  if (iVar4 != 0) {
    local_130 = (int *)0x585415;
    uVar1 = FUN_00572d90();
    *(undefined2 *)(local_ac + 0x7c) = uVar1;
    DAT_00918130 = DAT_00918130 + 1;
    *(short *)(local_ac + 0x7e) = DAT_00918130;
    *(undefined4 *)(local_ac + 0x80) = 1;
    local_130 = (int *)(local_ac + 0x7e);
    local_134 = (undefined1 *)(local_ac + 0x7c);
    local_138 = 0x58546f;
    FUN_004bcc60();
    local_b8 = local_ac;
    local_130 = &local_b8;
    local_134 = local_c0;
    local_138 = 0x585494;
    local_130 = (int *)FUN_00585bb0();
    local_134 = local_d0;
    local_138 = 0x5854a6;
    FUN_00585bf0();
  }
  puVar2 = (undefined4 *)(*(int *)(local_ac + 0x14) + 0x20);
  puVar5 = (undefined4 *)(local_ac + 0x88);
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar5 = puVar5 + 1;
  }
  local_130 = (int *)0x5854ca;
  fVar6 = (float10)FUN_00822d80();
  *(float *)(local_ac + 200) = (float)fVar6;
  *(undefined4 *)(local_ac + 0xcc) = 0;
  *(undefined4 *)(local_ac + 0xd0) = 0;
  if (*(char *)(*(int *)(*(int *)(local_ac + 0xc) + 0x34) + 0x84) != '\0') {
    local_130 = (int *)0x0;
    local_134 = (undefined1 *)0x58551d;
    iVar4 = FUN_00684ca0();
    if (iVar4 != 0) {
      local_130 = (int *)local_ac;
      local_134 = (undefined1 *)0x585530;
      FUN_0067ec70();
      local_130 = (int *)local_ac;
      local_134 = (undefined1 *)0x58553f;
      FUN_006804c0();
    }
  }
  FUN_0083e885();
  return;
}

