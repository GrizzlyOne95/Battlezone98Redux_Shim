
void FUN_00681a00(int param_1,int param_2)

{
  uint *puVar1;
  undefined1 local_40 [16];
  int *local_30;
  int *local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (param_1 != 0) {
    puVar1 = (uint *)FUN_0081f1e0(local_40,param_2);
    local_28 = *puVar1;
    local_24 = puVar1[1];
    local_20 = puVar1[2];
    local_1c = puVar1[3];
    local_2c = *(int **)(param_1 + 200);
    local_18 = local_28;
    local_14 = local_24;
    local_10 = local_20;
    local_c = local_1c;
    if (local_2c != (int *)0x0) {
      (**(code **)(*local_2c + 0x20))(local_1c,local_28 ^ 0x80000000,local_24,local_20);
      if (*(int *)(param_1 + 0x84) != 0x28) {
        (**(code **)(*local_2c + 0x2c))
                  (-(float)*(double *)(param_2 + 0x28),(float)*(double *)(param_2 + 0x30),
                   (float)*(double *)(param_2 + 0x38));
      }
    }
    local_30 = *(int **)(param_1 + 0xcc);
    if (local_30 != (int *)0x0) {
      (**(code **)(*local_30 + 0x20))(local_c,local_18 ^ 0x80000000,local_14,local_10);
      if (*(int *)(param_1 + 0x84) != 0x28) {
        (**(code **)(*local_30 + 0x2c))
                  (-(float)*(double *)(param_2 + 0x28),(float)*(double *)(param_2 + 0x30),
                   (float)*(double *)(param_2 + 0x38));
      }
    }
  }
  FUN_0083e885();
  return;
}

