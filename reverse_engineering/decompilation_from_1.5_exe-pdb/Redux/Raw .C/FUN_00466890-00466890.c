
undefined4 FUN_00466890(int param_1,float *param_2,float *param_3,float *param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  float10 fVar4;
  uint local_14;
  float local_10;
  int local_8;
  
  *param_2 = 0.0;
  *param_3 = 10.0;
  *param_4 = 1.0;
  if ((*(int *)(*(int *)(param_1 + 8) + 0xc) == 0x44495350) ||
     (*(int *)(*(int *)(param_1 + 8) + 0xc) == 0x5244524c)) {
    iVar1 = *(int *)(param_1 + 0xc);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      if (*(int *)(iVar1 + 0x14) == 0x50524f58) {
        *param_3 = 50.0;
        *param_4 = 1.0;
      }
      else if (*(int *)(iVar1 + 0x14) == 0x544f5250) {
        if (*(int *)(iVar1 + 0x198) != 0) {
          *param_2 = *(float *)(*(int *)(iVar1 + 0x198) + 0x50);
        }
        if (*(int *)(*(int *)(param_1 + 8) + 0xc) == 0x5244524c) {
          *param_3 = *(float *)(*(int *)(param_1 + 8) + 0x80);
          *param_4 = *param_3 / *(float *)(iVar1 + 0x17c);
        }
        else {
          *param_3 = *(float *)(iVar1 + 0x18c) * *(float *)(iVar1 + 0x17c);
          *param_4 = *(float *)(iVar1 + 0x18c);
        }
      }
      else {
        *param_3 = 50.0;
        *param_4 = 1.0;
      }
      uVar2 = 1;
    }
  }
  else {
    local_8 = *(int *)(param_1 + 0xc);
    if ((local_8 == 0) && (*(int *)(*(int *)(param_1 + 8) + 0xc) == 0x43485247)) {
      local_14 = FUN_004626d0();
      uVar3 = FUN_004626f0();
      for (; local_14 <= uVar3; local_14 = local_14 + 0x2c) {
        if (*(int *)(local_14 + 0x20) != 0) {
          local_8 = *(int *)(local_14 + 0x20);
          break;
        }
      }
    }
    if (local_8 == 0) {
      uVar2 = 0;
    }
    else {
      local_10 = 0.0;
      if ((*(int *)(local_8 + 0x3c) != 0) && (*(float *)(*(int *)(local_8 + 0x3c) + 0x50) != 0.0)) {
        fVar4 = (float10)FUN_0044fb20(0,*(undefined4 *)(*(int *)(local_8 + 0x3c) + 0x50));
        local_10 = (float)fVar4;
      }
      if ((*(int *)(local_8 + 0x40) != 0) && (*(float *)(*(int *)(local_8 + 0x40) + 0x50) != 0.0)) {
        fVar4 = (float10)FUN_0044fb20(local_10,*(undefined4 *)(*(int *)(local_8 + 0x40) + 0x50));
        local_10 = (float)fVar4;
      }
      if ((*(int *)(local_8 + 0x44) != 0) && (*(float *)(*(int *)(local_8 + 0x44) + 0x50) != 0.0)) {
        fVar4 = (float10)FUN_0044fb20(local_10,*(undefined4 *)(*(int *)(local_8 + 0x44) + 0x50));
        local_10 = (float)fVar4;
      }
      *param_2 = local_10;
      iVar1 = *(int *)(*(int *)(param_1 + 8) + 0xc);
      if (((iVar1 == 0x494d474c) || (iVar1 == 0x4c4e4348)) || (iVar1 == 0x54484d4c)) {
        *param_3 = *(float *)(*(int *)(param_1 + 8) + 0x80);
        *param_4 = *param_3 / *(float *)(local_8 + 0x54);
      }
      else {
        *param_3 = *(float *)(local_8 + 0x50) * *(float *)(local_8 + 0x54);
        *param_4 = *(float *)(local_8 + 0x50);
      }
      uVar2 = 1;
    }
  }
  return uVar2;
}

