
void __thiscall FUN_00419b20(int param_1,int *param_2,char param_3)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  undefined4 local_2c;
  float local_20;
  float local_1c;
  
  *(int *)(param_1 + 0xc) = *param_2;
  *(int *)(param_1 + 0x10) = param_2[1];
  *(int *)(param_1 + 0x14) = param_2[2];
  *(int *)(param_1 + 0x18) = param_2[3];
  if (*(int *)(param_1 + 0x14) == 0) {
    iVar1 = FUN_0068f090(*(undefined4 *)(param_1 + 0x6c));
  }
  else {
    iVar1 = *(int *)(param_1 + 0x14);
  }
  local_1c = (float)iVar1;
  if (*(int *)(param_1 + 0x18) == 0) {
    iVar1 = FUN_0068f0c0(*(undefined4 *)(param_1 + 0x6c));
  }
  else {
    iVar1 = *(int *)(param_1 + 0x18);
  }
  local_20 = (float)iVar1;
  if ((param_3 != '\0') && ((*(int *)(param_1 + 0x6c) != 0 || (param_2[2] != 0)))) {
    *(int *)(param_1 + 0xc) = (int)((float)(0x800 - *param_2) - (local_1c * 3.0) / 2.0);
  }
  *(float *)(param_1 + 0x44) = (float)DAT_02cecee0 / 2048.0;
  *(float *)(param_1 + 0x48) = (float)DAT_02cecee4 / 1536.0;
  if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x48) ||
      *(float *)(param_1 + 0x44) == *(float *)(param_1 + 0x48)) {
    local_2c = *(undefined4 *)(param_1 + 0x44);
  }
  else {
    local_2c = *(undefined4 *)(param_1 + 0x48);
  }
  *(undefined4 *)(param_1 + 0x40) = local_2c;
  fVar3 = local_1c * 1.5 * *(float *)(param_1 + 0x40);
  fVar4 = local_20 * 1.5 * *(float *)(param_1 + 0x40);
  iVar1 = (int)((local_1c * 1.5 * *(float *)(param_1 + 0x44) - fVar3) / 2.0);
  iVar2 = (int)((local_20 * 1.5 * *(float *)(param_1 + 0x48) - fVar4) / 2.0);
  *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0xc);
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x10);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x14);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x18);
  *(int *)(param_1 + 0x1c) = (int)((float)*(int *)(param_1 + 0x1c) * *(float *)(param_1 + 0x44));
  *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + iVar1;
  *(int *)(param_1 + 0x20) = (int)((float)*(int *)(param_1 + 0x20) * *(float *)(param_1 + 0x48));
  *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + iVar2;
  *(int *)(param_1 + 0x24) = (int)(((float)*(int *)(param_1 + 0x1c) + fVar3) - 1.0);
  *(int *)(param_1 + 0x28) = (int)(((float)*(int *)(param_1 + 0x20) + fVar4) - 1.0);
  *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(param_1 + 0xc);
  *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x10);
  *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_1 + 0x14);
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x18);
  *(int *)(param_1 + 0x2c) = (int)((float)*(int *)(param_1 + 0x2c) * *(float *)(param_1 + 0x44));
  *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x2c) + iVar1;
  *(int *)(param_1 + 0x30) = (int)((float)*(int *)(param_1 + 0x30) * *(float *)(param_1 + 0x48));
  *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + iVar2;
  *(int *)(param_1 + 0x34) = (int)(((float)*(int *)(param_1 + 0x2c) + fVar3) - 1.0);
  *(int *)(param_1 + 0x38) = (int)(((float)*(int *)(param_1 + 0x30) + fVar4) - 1.0);
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  return;
}

