
void __fastcall FUN_00592af0(int param_1)

{
  float *pfVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  float fVar5;
  undefined4 uVar6;
  int local_10;
  int local_c;
  
  uVar3 = *(undefined4 *)(*(int *)(param_1 + 0x10) + 4 + *(int *)(param_1 + 4) * 8);
  iVar4 = *(int *)(param_1 + 0x10);
  *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(*(int *)(param_1 + 0x10) + *(int *)(param_1 + 4) * 8)
  ;
  *(undefined4 *)(iVar4 + 0xc) = uVar3;
  *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + -1;
  fVar5 = *(float *)(*(int *)(param_1 + 0x10) + 8);
  uVar3 = *(undefined4 *)(*(int *)(param_1 + 0x10) + 0xc);
  local_10 = 1;
  while (local_10 <= *(int *)(param_1 + 4) >> 1) {
    local_c = local_10 * 2;
    if ((local_c < *(int *)(param_1 + 4)) &&
       (fVar2 = *(float *)(*(int *)(param_1 + 0x10) + 8 + local_10 * 0x10),
       pfVar1 = (float *)(*(int *)(param_1 + 0x10) + local_10 * 0x10),
       *pfVar1 <= fVar2 && fVar2 != *pfVar1)) {
      local_c = local_c + 1;
    }
    if (*(float *)(*(int *)(param_1 + 0x10) + local_c * 8) <= fVar5) break;
    uVar6 = *(undefined4 *)(*(int *)(param_1 + 0x10) + 4 + local_c * 8);
    iVar4 = *(int *)(param_1 + 0x10);
    *(undefined4 *)(iVar4 + local_10 * 8) = *(undefined4 *)(*(int *)(param_1 + 0x10) + local_c * 8);
    *(undefined4 *)(iVar4 + 4 + local_10 * 8) = uVar6;
    local_10 = local_c;
  }
  iVar4 = *(int *)(param_1 + 0x10);
  *(float *)(iVar4 + local_10 * 8) = fVar5;
  *(undefined4 *)(iVar4 + 4 + local_10 * 8) = uVar3;
  return;
}

