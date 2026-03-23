
undefined4 * __thiscall
FUN_004390b0(undefined4 *param_1,int param_2,undefined4 param_3,uint param_4,undefined4 param_5)

{
  undefined4 uVar1;
  uint local_8;
  
  *param_1 = CSound::vftable;
  uVar1 = FUN_0083d92c(-(uint)((int)((ulonglong)param_4 * 4 >> 0x20) != 0) |
                       (uint)((ulonglong)param_4 * 4));
  param_1[1] = uVar1;
  for (local_8 = 0; local_8 < param_4; local_8 = local_8 + 1) {
    *(undefined4 *)(param_1[1] + local_8 * 4) = *(undefined4 *)(param_2 + local_8 * 4);
  }
  param_1[2] = param_3;
  param_1[4] = param_4;
  param_1[3] = param_5;
  FUN_004392b0(*(undefined4 *)param_1[1],0);
  for (local_8 = 0; local_8 < param_4; local_8 = local_8 + 1) {
    (**(code **)(**(int **)(param_1[1] + local_8 * 4) + 0x34))
              (*(undefined4 *)(param_1[1] + local_8 * 4),0);
  }
  return param_1;
}

