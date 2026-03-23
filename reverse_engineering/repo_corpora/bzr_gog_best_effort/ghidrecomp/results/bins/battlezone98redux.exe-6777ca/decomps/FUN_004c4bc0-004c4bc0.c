
void __thiscall
FUN_004c4bc0(int param_1,undefined2 *param_2,int param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  ushort *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  if ((*(int *)(param_1 + 0xec) < 1) && (*(int *)(param_1 + 0xf0) < 1)) {
    FUN_004c1130(param_2,param_3,param_4,param_5);
  }
  if (((*(float *)(param_1 + 0x144) != *(float *)(param_1 + 0xfc)) ||
      (*(int *)(param_1 + 0x13c) != *(int *)(param_1 + 0xec))) ||
     (*(int *)(param_1 + 0x140) != *(int *)(param_1 + 0xf0))) {
    FUN_004c4370();
  }
  iVar3 = param_3 - *(int *)(param_1 + 0xec) / 2;
  iVar1 = iVar3 + *(int *)(param_1 + 0xec);
  iVar5 = param_4 - *(int *)(param_1 + 0xf0) / 2;
  iVar4 = iVar5 + *(int *)(param_1 + 0xf0);
  if (param_6 != 0) {
    FUN_004c10a0(param_3,param_4,*param_2,1);
  }
  local_10 = 0;
  for (param_4 = iVar5; param_4 <= iVar4; param_4 = param_4 + 1) {
    local_14 = 0;
    for (param_3 = iVar3; param_3 <= iVar1; param_3 = param_3 + 1) {
      puVar2 = (ushort *)FUN_00492d60(param_3,param_4);
      local_c = (uint)(((float)param_5 * *(float *)(param_1 + 0xf8) *
                        *(float *)(param_1 + 0x148 + local_10 * 0x100 + local_14 * 4) +
                       (float)(*puVar2 & 0xfff) * 0.1) / 0.1 + 0.5);
      if ((int)local_c < 0) {
        local_c = 0;
      }
      if (0xfff < (int)local_c) {
        local_c = 0xfff;
      }
      if ((*puVar2 & 0xfff) != local_c) {
        FUN_004c10d0(param_3,param_4,*puVar2);
        *puVar2 = (ushort)local_c;
      }
      local_14 = local_14 + 1;
    }
    local_10 = local_10 + 1;
  }
  FUN_00780b80(iVar3 + -2,iVar5 + -2,iVar1 + 2,iVar4 + 2);
  return;
}

