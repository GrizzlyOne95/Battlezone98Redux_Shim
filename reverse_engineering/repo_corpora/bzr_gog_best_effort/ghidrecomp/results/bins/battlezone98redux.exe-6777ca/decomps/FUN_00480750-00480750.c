
void __thiscall FUN_00480750(int param_1,int *param_2,float *param_3)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_d4 [64];
  int local_94;
  int local_90;
  int local_8c;
  undefined4 local_88 [16];
  undefined4 local_48 [10];
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_8c = param_1;
  puVar2 = (undefined4 *)FUN_0081f920(local_d4,param_3,*(int *)(param_1 + 0x14) + 0x38);
  puVar4 = local_88;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  puVar2 = local_88;
  puVar4 = local_48;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  local_20 = (double)(*param_3 * 0.01) + *(double *)(*(int *)(local_8c + 0x14) + 0x48);
  local_18 = (double)(param_3[1] * 0.01) + *(double *)(*(int *)(local_8c + 0x14) + 0x50);
  local_10 = (double)(param_3[2] * 0.01) + *(double *)(*(int *)(local_8c + 0x14) + 0x58);
  if (param_2 == (int *)0x0) {
    if (*(int *)(*(int *)(local_8c + 0xc) + 0x3c) != 0) {
      FUN_004cb7b0(local_48,*(undefined4 *)(local_8c + 0xd8));
    }
  }
  else {
    local_94 = (**(code **)(param_2[6] + 0x30))();
    (**(code **)(param_2[6] + 0x38))(local_8c + 0x60,*(int *)(local_8c + 0x14) + 0x38);
    param_2[0x26] = *(int *)(local_8c + 0xc);
    local_90 = *(int *)(local_94 + 0x84) + -1;
    switch(*(int *)(local_94 + 0x84)) {
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
      if (*(int *)(*(int *)(local_8c + 0xc) + 0x40) != 0) {
        FUN_004cb7b0(local_48,*(undefined4 *)(local_8c + 0xd8));
      }
      break;
    case 2:
    case 8:
    case 10:
      if (*(int *)(*(int *)(local_8c + 0xc) + 0x44) != 0) {
        FUN_004cb7b0(local_48,*(undefined4 *)(local_8c + 0xd8));
      }
      break;
    default:
      if (*(int *)(*(int *)(local_8c + 0xc) + 0x3c) != 0) {
        FUN_004cb7b0(local_48,*(undefined4 *)(local_8c + 0xd8));
      }
    }
    cVar1 = FUN_004b9860();
    if (((cVar1 != '\0') && (iVar3 = FUN_0062e000(local_94), iVar3 != 0)) &&
       ((iVar3 = FUN_00417e20(local_94), iVar3 == 0 ||
        (cVar1 = (**(code **)(*param_2 + 0x6c))(), cVar1 != '\0')))) {
      *(uint *)(*(int *)(local_8c + 0x14) + 0x14) = *(uint *)(*(int *)(local_8c + 0x14) + 0x14) | 2;
    }
  }
  *(uint *)(*(int *)(local_8c + 0x14) + 0x14) = *(uint *)(*(int *)(local_8c + 0x14) + 0x14) | 0x200;
  FUN_0083e885();
  return;
}

