
void __thiscall FUN_005f61e0(int param_1,undefined1 *param_2,int *param_3)

{
  undefined1 uVar1;
  int iVar2;
  
  *param_3 = *param_3 + 3;
  switch(*(undefined4 *)(param_1 + 0x210)) {
  case 0:
    param_2[2] = 3;
    break;
  case 1:
    param_2[2] = 1;
    break;
  case 2:
    param_2[2] = 2;
    break;
  case 3:
    param_2[2] = 0;
  }
  if (((*(uint *)(*(int *)(param_1 + 0xdc) + 0x14) & 0x10) != 0) &&
     (iVar2 = FUN_004e96a0(), iVar2 != 0)) {
    param_2[2] = param_2[2] | 0x40;
  }
  if ((*(int *)(param_1 + 0xd4) != 0) || (*(int *)(param_1 + 0xe4) != 0)) {
    param_2[2] = param_2[2] | 0x80;
  }
  if (0.0 < *(float *)(param_1 + 0x1e8)) {
    FUN_0043d610(*(float *)(param_1 + 0x1e8) * 255.0);
    uVar1 = FUN_0083f040();
    *param_2 = uVar1;
  }
  else {
    *param_2 = 0;
  }
  if (0.0 < *(float *)(param_1 + 500)) {
    FUN_0043d610(*(float *)(param_1 + 500) * 255.0);
    uVar1 = FUN_0083f040();
    param_2[1] = uVar1;
  }
  else {
    param_2[1] = 0;
  }
  if (*(int *)(param_1 + 0x210) == 0) {
    FUN_004ef640(param_2 + 3,param_3);
  }
  return;
}

