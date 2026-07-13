
void __thiscall FUN_004d2e90(int param_1,float param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_1a8 [64];
  undefined1 local_168 [64];
  float local_128;
  float local_124;
  undefined4 local_120;
  int local_11c;
  int local_118;
  int local_114;
  undefined4 local_110 [16];
  undefined4 local_d0 [16];
  undefined4 local_90 [16];
  undefined1 local_50 [16];
  undefined4 local_40;
  undefined1 local_24 [12];
  undefined4 local_18;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_120 = *(undefined4 *)(*(int *)(param_1 + 0xf8) + 0x168);
  *(float *)(param_1 + 0x244) = *(float *)(param_1 + 0x244) + param_2;
  local_114 = param_1;
  while (0.0 <= *(float *)(local_114 + 0x244)) {
    if ((*(int *)(local_114 + 0x230) == 0) &&
       (*(char *)(*(int *)(local_114 + 0xf8) + 0x16c) != '\0')) {
      FUN_0043a990(local_50);
      local_40 = 0x1001;
      FUN_0043a9e0(local_24);
      local_18 = 1;
      uVar1 = FUN_0043aa30(*(int *)(local_114 + 0xf8) + 0x16c,*(undefined4 *)(local_114 + 0xf4),
                           local_50,local_24);
      *(undefined4 *)(local_114 + 0x230) = uVar1;
    }
    local_11c = *(int *)(local_114 + 0xf4) + 0x20;
    local_124 = *(float *)(*(int *)(local_114 + 0xf8) + 0x184);
    fVar5 = (float10)FUN_004588c0(0x40490fdb);
    fVar5 = (float10)FUN_004464c0((float)fVar5);
    local_128 = (float)fVar5;
    puVar2 = (undefined4 *)FUN_0081ed60(local_168,local_128 * local_124 - 1.5707964);
    puVar4 = local_110;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar2 = local_110;
    puVar4 = local_90;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar2 = (undefined4 *)FUN_0081fe60(local_1a8,local_90,local_11c);
    puVar4 = local_d0;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar2 = local_d0;
    puVar4 = local_90;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
    local_118 = FUN_00586ff0(local_90,*(undefined4 *)(local_114 + 0xf4));
    *(undefined4 *)(local_118 + 0x80) = 0;
    *(float *)(local_118 + 0x10) = *(float *)(local_114 + 0x244) - param_2;
    *(float *)(local_114 + 0x244) =
         *(float *)(local_114 + 0x244) - *(float *)(*(int *)(local_114 + 0xf8) + 0x180);
  }
  FUN_00511460(param_2);
  FUN_0083e885();
  return;
}

