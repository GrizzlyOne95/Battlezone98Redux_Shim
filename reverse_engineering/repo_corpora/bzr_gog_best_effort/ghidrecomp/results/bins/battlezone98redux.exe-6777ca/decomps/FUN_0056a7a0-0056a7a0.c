
void __thiscall FUN_0056a7a0(int param_1,float param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_9c [64];
  float local_5c;
  int local_58;
  float local_54;
  float local_50;
  int local_4c;
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_4c = param_1;
  if ((*(uint *)(*(int *)(param_1 + 0x14) + 0x14) & 8) != 0) {
    local_54 = *(float *)(*(int *)(param_1 + 0xc) + 0x54);
    local_50 = *(float *)(*(int *)(param_1 + 0xc) + 0xd4) * param_2;
    iVar2 = *(int *)(param_1 + 0x14);
    local_58 = iVar2 + 0x20;
    *(float *)(param_1 + 0x30) =
         (*(float *)(iVar2 + 0x38) * local_54 - *(float *)(param_1 + 0x30)) * local_50 +
         *(float *)(param_1 + 0x30);
    *(float *)(param_1 + 0x34) =
         (*(float *)(iVar2 + 0x3c) * local_54 - *(float *)(param_1 + 0x34)) * local_50 +
         *(float *)(param_1 + 0x34);
    *(float *)(param_1 + 0x38) =
         (*(float *)(iVar2 + 0x40) * local_54 - *(float *)(param_1 + 0x38)) * local_50 +
         *(float *)(param_1 + 0x38);
    fVar4 = (float10)FUN_0045c420(*(undefined4 *)(param_1 + 0x30),*(undefined4 *)(param_1 + 0x34),
                                  *(undefined4 *)(param_1 + 0x38));
    *(float *)(local_4c + 0x20) = (float)fVar4;
    if (*(float *)(local_4c + 0x20) <= 0.0) {
      local_5c = 1e+30;
    }
    else {
      local_5c = 1.0 / *(float *)(local_4c + 0x20);
    }
    *(float *)(local_4c + 0x24) = local_5c;
    puVar1 = (undefined4 *)
             FUN_00444d50(local_9c,*(int *)(local_4c + 0x14) + 0x20,*(undefined4 *)(local_4c + 0x3c)
                          ,*(undefined4 *)(local_4c + 0x40),*(undefined4 *)(local_4c + 0x44),param_2
                         );
    puVar3 = local_48;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = local_48;
    puVar3 = (undefined4 *)(*(int *)(local_4c + 0x14) + 0x20);
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  FUN_005bd060(param_2);
  FUN_0083e885();
  return;
}

