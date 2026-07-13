
void FUN_00824710(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined1 local_38 [16];
  undefined1 local_28 [16];
  undefined1 local_18 [16];
  int local_8;
  
  if (param_1 == 0) {
    *(ushort *)(param_2 + 2) = *(ushort *)(param_2 + 2) & 0xfff0 | 8;
    *(ushort *)(param_2 + 2) = *(ushort *)(param_2 + 2) & 0xfc3f;
  }
  else {
    local_8 = *(int *)(param_1 + 0x84);
    if (local_8 == 0x33) {
      puVar1 = (undefined4 *)FUN_00584da0(local_18,param_1);
      *param_2 = *puVar1;
      param_2[1] = puVar1[1];
      param_2[2] = puVar1[2];
      param_2[3] = puVar1[3];
    }
    else if (local_8 == 0x34) {
      puVar1 = (undefined4 *)FUN_004c99d0(local_28,param_1);
      *param_2 = *puVar1;
      param_2[1] = puVar1[1];
      param_2[2] = puVar1[2];
      param_2[3] = puVar1[3];
    }
    else {
      puVar1 = (undefined4 *)FUN_004df7f0(local_38,param_1);
      *param_2 = *puVar1;
      param_2[1] = puVar1[1];
      param_2[2] = puVar1[2];
      param_2[3] = puVar1[3];
    }
  }
  return;
}

