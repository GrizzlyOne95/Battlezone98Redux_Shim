
void __thiscall FUN_004c22b0(undefined4 param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  
  iVar1 = param_2[1];
  iVar2 = FUN_0068f090(*(undefined4 *)(*param_2 + 0x10),param_1);
  iVar3 = FUN_0068f0c0(*(undefined4 *)(*param_2 + 0x10));
  local_18 = 0x11;
  for (local_c = 0; local_c < 2; local_c = local_c + 1) {
    local_14 = 0x11;
    for (local_10 = 0; local_10 < iVar1 / 2; local_10 = local_10 + 1) {
      puVar4 = (undefined4 *)((local_c * (iVar1 / 2) + local_10) * 0x24 + *param_2);
      uVar5 = FUN_0068bed0(*puVar4);
      puVar4[4] = uVar5;
      puVar4[5] = local_18;
      puVar4[6] = local_14;
      puVar4[7] = puVar4[5] + 9 + iVar2;
      puVar4[8] = puVar4[6] + 9 + iVar3;
      local_14 = local_14 + 0xb + iVar3;
    }
    local_18 = local_18 + 0xb + iVar2;
  }
  param_2[2] = 0x10;
  param_2[3] = 0x10;
  param_2[4] = param_2[2] + 0x16 + iVar2 * 2;
  param_2[5] = param_2[3] + (iVar3 + 0xb) * (param_2[1] / 2);
  param_2[6] = 0;
  return;
}

