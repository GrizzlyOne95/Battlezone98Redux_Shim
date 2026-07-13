
void __thiscall FUN_005eca60(int param_1,float param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined1 local_2a0 [64];
  undefined1 local_260 [64];
  undefined1 local_220 [64];
  undefined1 local_1e0 [64];
  int *local_1a0;
  undefined4 local_19c;
  undefined4 local_198;
  int local_194;
  char local_18d;
  int local_18c;
  undefined4 local_188 [16];
  undefined4 local_148 [16];
  undefined4 local_108 [16];
  undefined4 local_c8 [16];
  undefined4 local_88 [16];
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18c = param_1;
  if ((-1 < *(int *)(param_1 + 0x308)) &&
     ((iVar1 = FUN_0062a540(*(undefined4 *)(param_1 + 0x308),&local_1a0), iVar1 != 0 ||
      (*local_1a0 != 1)))) {
    FUN_0062a5d0(*(undefined4 *)(local_18c + 0x308));
    *(undefined4 *)(local_18c + 0x308) = 0xffffffff;
  }
  local_198 = *(undefined4 *)(local_18c + 0x228);
  switch(local_198) {
  case 0:
    if (*(int *)(*(int *)(local_18c + 0x230) + 0xe0) != 0) {
      *(undefined4 *)(*(int *)(local_18c + 0x230) + 0xe0) = 0;
      *(undefined4 *)(local_18c + 0x228) = 1;
      FUN_004376c0(*(int *)(local_18c + 0xf8) + 0x5d0,*(undefined4 *)(local_18c + 0xf4),0);
      FUN_0062a270(*(undefined4 *)(local_18c + 0xf4),0,local_18c + 0x308);
      *(undefined4 *)(local_18c + 0x30c) = *(undefined4 *)(local_18c + 0x310);
    }
    break;
  case 1:
    *(float *)(local_18c + 0x30c) = *(float *)(local_18c + 0x30c) - param_2;
    if (*(float *)(local_18c + 0x30c) <= 0.0) {
      if (*(int *)(local_18c + 0x300) == 0) {
        FUN_005ec4c0(local_18c);
      }
      *(undefined4 *)(local_18c + 0x228) = 2;
      if (*(int *)(local_18c + 0x300) == 0) {
        *(undefined4 *)(local_18c + 0x30c) = 0x3f800000;
      }
    }
    break;
  case 2:
    if ((*(int *)(local_18c + 0x300) == 0) &&
       (*(float *)(local_18c + 0x30c) = *(float *)(local_18c + 0x30c) - param_2,
       *(float *)(local_18c + 0x30c) <= 0.0)) {
      *(undefined4 *)(*(int *)(local_18c + 0x230) + 0xe0) = 1;
    }
    if (*(int *)(*(int *)(local_18c + 0x230) + 0xe0) != 0) {
      *(undefined4 *)(*(int *)(local_18c + 0x230) + 0xe0) = 0;
      *(undefined4 *)(local_18c + 0x228) = 3;
      FUN_004376c0(*(int *)(local_18c + 0xf8) + 0x5e0,*(undefined4 *)(local_18c + 0xf4),0);
      FUN_0062a270(*(undefined4 *)(local_18c + 0xf4),1,local_18c + 0x308);
      *(undefined4 *)(local_18c + 0x30c) = *(undefined4 *)(local_18c + 0x314);
    }
    break;
  case 3:
    *(float *)(local_18c + 0x30c) = *(float *)(local_18c + 0x30c) - param_2;
    if ((*(int *)(local_18c + 0x308) < 0) && (*(float *)(local_18c + 0x30c) <= 0.0)) {
      if (*(int *)(local_18c + 0x300) != 0) {
        FUN_005ec660(local_18c);
      }
      *(undefined4 *)(local_18c + 0x228) = 0;
    }
  }
  local_18d = (*(uint *)(*(int *)(local_18c + 0xf4) + 0x14) & 0x200) == 0;
  FUN_004ebfd0(param_2);
  if ((local_18d != '\0') && (*(int *)(local_18c + 0x300) != 0)) {
    local_19c = (**(code **)(*(int *)(*(int *)(local_18c + 0x300) + 0x18) + 0x30))();
    if (*(int *)(local_18c + 0x318) == 0) {
      *(undefined4 *)(local_18c + 0x318) = *(undefined4 *)(local_18c + 0xf4);
    }
    puVar2 = (undefined4 *)FUN_0062e070(local_1e0,*(undefined4 *)(local_18c + 0x318),0);
    puVar3 = local_c8;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar2 = local_c8;
    puVar3 = local_88;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    if (*(int *)(local_18c + 0x31c) == 0) {
      puVar2 = local_88;
      puVar3 = local_48;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
    }
    else {
      puVar2 = (undefined4 *)FUN_0062e070(local_260,*(undefined4 *)(local_18c + 0x31c),local_19c);
      puVar3 = local_108;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar2 = local_108;
      puVar3 = local_48;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar2 = (undefined4 *)FUN_008203f0(local_220,local_48);
      puVar3 = local_188;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar2 = local_188;
      puVar3 = local_48;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar2 = (undefined4 *)FUN_0081fe60(local_2a0,local_48,local_88);
      puVar3 = local_148;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar2 = local_148;
      puVar3 = local_48;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
    }
    FUN_0056d6a0(local_48);
    local_194 = FUN_0045c490();
    *(undefined4 *)(local_194 + 0x18) = *(undefined4 *)(local_18c + 300);
    *(undefined4 *)(local_194 + 0x1c) = *(undefined4 *)(local_18c + 0x130);
    *(undefined4 *)(local_194 + 0x20) = *(undefined4 *)(local_18c + 0x134);
    *(undefined4 *)(local_194 + 8) = *(undefined4 *)(local_18c + 0x11c);
    *(undefined4 *)(local_194 + 0xc) = *(undefined4 *)(local_18c + 0x120);
    *(undefined4 *)(local_194 + 0x24) = *(undefined4 *)(local_18c + 0x138);
    *(undefined4 *)(local_194 + 0x28) = *(undefined4 *)(local_18c + 0x13c);
    *(undefined4 *)(local_194 + 0x2c) = *(undefined4 *)(local_18c + 0x140);
    *(undefined4 *)(local_194 + 0x30) = *(undefined4 *)(local_18c + 0x144);
    *(undefined4 *)(local_194 + 0x34) = *(undefined4 *)(local_18c + 0x148);
    *(undefined4 *)(local_194 + 0x38) = *(undefined4 *)(local_18c + 0x14c);
    *(undefined4 *)(local_194 + 0x3c) = *(undefined4 *)(local_18c + 0x150);
    *(undefined4 *)(local_194 + 0x40) = *(undefined4 *)(local_18c + 0x154);
    *(undefined4 *)(local_194 + 0x44) = *(undefined4 *)(local_18c + 0x158);
  }
  FUN_0083e885();
  return;
}

