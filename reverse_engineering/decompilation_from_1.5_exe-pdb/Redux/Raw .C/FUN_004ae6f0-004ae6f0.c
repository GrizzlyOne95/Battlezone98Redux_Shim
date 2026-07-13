
void __thiscall FUN_004ae6f0(int param_1,undefined1 *param_2,int *param_3)

{
  undefined1 uVar1;
  char cVar2;
  float10 fVar3;
  undefined1 local_14;
  float local_10;
  
  *param_3 = *param_3 + 4;
  if (0.0 < *(float *)(param_1 + 500)) {
    local_14 = (undefined1)(int)(*(float *)(param_1 + 500) * 255.0);
    param_2[1] = local_14;
  }
  else {
    param_2[1] = 0;
  }
  if (0.0 < *(float *)(param_1 + 0x1e8)) {
    local_10 = *(float *)(param_1 + 0x1e8);
    if (1.0 < local_10) {
      local_10 = 1.0;
    }
    FUN_0043d610(local_10 * 255.0);
    uVar1 = FUN_0083f040();
    *param_2 = uVar1;
  }
  else {
    *param_2 = 0;
  }
  param_2[2] = 0;
  if ((*(uint *)(*(int *)(param_1 + 0xdc) + 0x14) & 0x10000000) != 0) {
    param_2[2] = param_2[2] | 1;
  }
  if ((*(uint *)(*(int *)(param_1 + 0xdc) + 0x14) & 0x20000000) != 0) {
    param_2[2] = param_2[2] | 2;
  }
  if ((*(uint *)(*(int *)(param_1 + 0xdc) + 0x14) & 0x40000000) != 0) {
    param_2[2] = param_2[2] | 4;
  }
  param_2[3] = *(undefined1 *)(param_1 + 0x280);
  if ((*(int *)(param_1 + 0xd4) != 0) || (*(int *)(param_1 + 0xe4) != 0)) {
    param_2[2] = param_2[2] | 0x80;
  }
  if ((*(uint *)(*(int *)(param_1 + 0xdc) + 0x14) & 0x400) != 0) {
    param_2[2] = param_2[2] | 0x40;
  }
  cVar2 = FUN_0046fbf0();
  if (cVar2 != '\0') {
    param_2[2] = param_2[2] | 0x20;
  }
  fVar3 = (float10)FUN_0046fbd0();
  if ((float)fVar3 < 0.0) {
    param_2[2] = param_2[2] | 0x10;
  }
  FUN_00422c10(param_2 + 4,param_3);
  return;
}

