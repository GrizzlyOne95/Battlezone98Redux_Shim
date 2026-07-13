
void __fastcall FUN_004b07d0(int *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int local_50;
  undefined4 local_48 [10];
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((char)param_1[0x86] == '\0') {
    *(undefined1 *)(param_1 + 0x86) = 1;
    *(uint *)(param_1[0x37] + 0x14) = *(uint *)(param_1[0x37] + 0x14) | 0x1000200;
    *(uint *)(param_1[0x84] + 0x114) = *(uint *)(param_1[0x84] + 0x114) | 0x20;
    if ((*(uint *)(param_1[0x37] + 0x14) & 0x800) != 0) {
      FUN_0068a2d0(param_1[0x37]);
    }
    FUN_007809d0(param_1[0x3c],param_1[0x3e],*(undefined4 *)(param_1[0x38] + 0x17c));
    if ((*(uint *)(param_1[0x37] + 0x14) & 0x400000) == 0) {
      if (((*(uint *)(param_1[0x37] + 0x14) & 0x800000) != 0) ||
         ((*(uint *)(param_1[0x84] + 0x114) & 4) != 0)) {
        if (*(int *)(param_1[0x38] + 0x144) == 0) {
          local_50 = DAT_00917a44;
        }
        else {
          local_50 = *(int *)(param_1[0x38] + 0x144);
        }
        *(uint *)(param_1[0x37] + 0x14) = *(uint *)(param_1[0x37] + 0x14) | 0x800000;
      }
    }
    else {
      local_50 = *(int *)(param_1[0x38] + 0x178);
      if (local_50 == 0) {
        FUN_007d6c70("%s missing xplBlast\n",param_1[0x38] + 0x38);
      }
    }
    puVar2 = (undefined4 *)(param_1[0x37] + 0x20);
    puVar3 = local_48;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    local_20 = (double)(float)param_1[0x3c];
    local_18 = (double)(float)param_1[0x3d];
    local_10 = (double)(float)param_1[0x3e];
    (**(code **)(*param_1 + 0x10))();
    if (local_50 != 0) {
      FUN_004cb7b0(local_48,0);
    }
  }
  FUN_0083e885();
  return;
}

