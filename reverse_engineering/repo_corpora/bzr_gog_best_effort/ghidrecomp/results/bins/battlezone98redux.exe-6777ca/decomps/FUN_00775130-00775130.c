
void FUN_00775130(int *param_1,undefined4 param_2,float param_3,int param_4)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_64 [12];
  undefined4 local_58;
  undefined4 local_54 [16];
  undefined4 local_14;
  undefined4 local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  DAT_02ceefc8 = (double)(float)param_1[4];
  DAT_02ceefd0 = (double)(float)param_1[5];
  DAT_02ceefd8 = (double)(float)param_1[6];
  puVar1 = (undefined4 *)FUN_006897e0(local_64,param_2,DAT_02ceefc8,DAT_02ceefd0,DAT_02ceefd8);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = (float)puVar1[2];
  if (local_c <= DAT_02ce99c8 * DAT_02cc50e0) {
    param_3 = param_3 * 0.5;
    param_1[10] = (int)-param_3;
    param_1[0xb] = param_4;
    param_1[0xc] = 0;
    param_1[0xd] = (int)param_3;
    param_1[0xe] = param_4;
    param_1[0xf] = 0;
    param_1[0x10] = (int)param_3;
    param_1[0x11] = 0;
    param_1[0x12] = 0;
    param_1[0x13] = (int)-param_3;
    param_1[0x14] = 0;
    param_1[0x15] = 0;
    puVar1 = (undefined4 *)FUN_0081fe60();
    puVar3 = local_54;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    FUN_00820180(param_1 + 10,param_1 + 10,4,local_54);
    local_58 = DAT_00920ef4;
    DAT_00920ef4 = local_c;
    FUN_0068d2f0(param_2,*param_1 + param_1[2],param_1 + 10,4);
    DAT_00920ef4 = (float)local_58;
  }
  FUN_0083e885();
  return;
}

