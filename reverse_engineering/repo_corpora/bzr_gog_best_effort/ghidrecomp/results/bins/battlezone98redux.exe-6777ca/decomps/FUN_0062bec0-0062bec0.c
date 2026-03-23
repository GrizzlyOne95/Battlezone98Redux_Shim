
void FUN_0062bec0(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  undefined1 local_14 [12];
  int local_8;
  
  local_8 = FUN_0062be60(*(undefined4 *)(param_1 + 0x84));
  if (*(int *)(&DAT_008ec7bc + local_8 * 0x34) == 0) {
    puVar1 = (undefined4 *)FUN_00440000(local_14,0,0,0);
    *param_2 = *puVar1;
    param_2[1] = puVar1[1];
    param_2[2] = puVar1[2];
    *param_3 = 0;
  }
  else {
    (**(code **)(&DAT_008ec7bc + local_8 * 0x34))(param_1,param_2,param_3);
  }
  return;
}

