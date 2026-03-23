
void FUN_006bd7b0(uint *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  int local_8;
  
  local_c = param_1[1];
  local_10 = param_1[2];
  local_14 = param_1[3];
  local_1c = param_1[4];
  local_18 = *param_1;
  for (local_8 = 0; local_8 < 0x10; local_8 = local_8 + 1) {
    iVar2 = FUN_006bd760(local_18,5);
    uVar4 = local_c & local_10;
    uVar5 = ~local_c & local_14;
    iVar2 = iVar2 + local_1c;
    iVar1 = *(int *)(param_2 + local_8 * 4);
    local_1c = local_14;
    local_14 = local_10;
    local_10 = FUN_006bd760(local_c,0x1e);
    local_c = local_18;
    local_18 = (uVar4 | uVar5) + iVar2 + 0x5a827999 + iVar1;
  }
  for (; local_8 < 0x14; local_8 = local_8 + 1) {
    uVar3 = FUN_006bd760(*(uint *)(param_2 + -0xc + local_8 * 4) ^
                         *(uint *)(param_2 + -0x20 + local_8 * 4) ^
                         *(uint *)(param_2 + -0x38 + local_8 * 4) ^
                         *(uint *)(param_2 + -0x40 + local_8 * 4),1);
    *(undefined4 *)(param_2 + local_8 * 4) = uVar3;
    iVar2 = FUN_006bd760(local_18,5);
    uVar4 = local_c & local_10;
    uVar5 = ~local_c & local_14;
    iVar2 = iVar2 + local_1c;
    iVar1 = *(int *)(param_2 + local_8 * 4);
    local_1c = local_14;
    local_14 = local_10;
    local_10 = FUN_006bd760(local_c,0x1e);
    local_c = local_18;
    local_18 = (uVar4 | uVar5) + iVar2 + 0x5a827999 + iVar1;
  }
  for (; local_8 < 0x28; local_8 = local_8 + 1) {
    uVar3 = FUN_006bd760(*(uint *)(param_2 + -0xc + local_8 * 4) ^
                         *(uint *)(param_2 + -0x20 + local_8 * 4) ^
                         *(uint *)(param_2 + -0x38 + local_8 * 4) ^
                         *(uint *)(param_2 + -0x40 + local_8 * 4),1);
    *(undefined4 *)(param_2 + local_8 * 4) = uVar3;
    iVar2 = FUN_006bd760(local_18,5);
    uVar4 = local_c ^ local_10 ^ local_14;
    iVar2 = iVar2 + local_1c;
    iVar1 = *(int *)(param_2 + local_8 * 4);
    local_1c = local_14;
    local_14 = local_10;
    local_10 = FUN_006bd760(local_c,0x1e);
    local_c = local_18;
    local_18 = uVar4 + iVar2 + 0x6ed9eba1 + iVar1;
  }
  for (; local_8 < 0x3c; local_8 = local_8 + 1) {
    uVar3 = FUN_006bd760(*(uint *)(param_2 + -0xc + local_8 * 4) ^
                         *(uint *)(param_2 + -0x20 + local_8 * 4) ^
                         *(uint *)(param_2 + -0x38 + local_8 * 4) ^
                         *(uint *)(param_2 + -0x40 + local_8 * 4),1);
    *(undefined4 *)(param_2 + local_8 * 4) = uVar3;
    iVar2 = FUN_006bd760(local_18,5);
    uVar4 = local_c & (local_10 | local_14);
    uVar5 = local_10 & local_14;
    iVar2 = iVar2 + local_1c;
    iVar1 = *(int *)(param_2 + local_8 * 4);
    local_1c = local_14;
    local_14 = local_10;
    local_10 = FUN_006bd760(local_c,0x1e);
    local_c = local_18;
    local_18 = (uVar4 | uVar5) + iVar2 + -0x70e44324 + iVar1;
  }
  for (; local_8 < 0x50; local_8 = local_8 + 1) {
    uVar3 = FUN_006bd760(*(uint *)(param_2 + -0xc + local_8 * 4) ^
                         *(uint *)(param_2 + -0x20 + local_8 * 4) ^
                         *(uint *)(param_2 + -0x38 + local_8 * 4) ^
                         *(uint *)(param_2 + -0x40 + local_8 * 4),1);
    *(undefined4 *)(param_2 + local_8 * 4) = uVar3;
    iVar2 = FUN_006bd760(local_18,5);
    uVar4 = local_c ^ local_10 ^ local_14;
    iVar2 = iVar2 + local_1c;
    iVar1 = *(int *)(param_2 + local_8 * 4);
    local_1c = local_14;
    local_14 = local_10;
    local_10 = FUN_006bd760(local_c,0x1e);
    local_c = local_18;
    local_18 = uVar4 + iVar2 + -0x359d3e2a + iVar1;
  }
  *param_1 = *param_1 + local_18;
  param_1[1] = param_1[1] + local_c;
  param_1[2] = param_1[2] + local_10;
  param_1[3] = param_1[3] + local_14;
  param_1[4] = param_1[4] + local_1c;
  return;
}

