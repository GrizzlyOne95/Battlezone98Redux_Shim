
void __thiscall
FUN_004c4700(int param_1,ushort *param_2,int param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  ushort *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint local_10;
  uint local_c;
  
  if ((*(int *)(**(int **)(param_1 + 0xc) + 0xc + *(int *)(param_1 + 0x10) * 0x24) == 0xc) ||
     ((*(int *)(param_1 + 0xec) < 1 && (*(int *)(param_1 + 0xf0) < 1)))) {
    local_c = (uint)(((float)param_5 * *(float *)(param_1 + 0xf8) + (float)(*param_2 & 0xfff) * 0.1)
                     / 0.1 + 0.5);
    if ((int)local_c < 0) {
      local_c = 0;
    }
    if (0xfff < (int)local_c) {
      local_c = 0xfff;
    }
    if ((*param_2 & 0xfff) != local_c) {
      FUN_004c10a0(param_3,param_4,*param_2,param_6);
      *param_2 = (ushort)local_c;
      FUN_00780b80(param_3 + -2,param_4 + -2,param_3 + 2,param_4 + 2);
    }
  }
  else {
    iVar3 = param_3 - *(int *)(param_1 + 0xec) / 2;
    iVar1 = iVar3 + *(int *)(param_1 + 0xec);
    iVar5 = param_4 - *(int *)(param_1 + 0xf0) / 2;
    iVar4 = iVar5 + *(int *)(param_1 + 0xf0);
    param_4 = iVar5;
    if (param_6 != 0) {
      FUN_004c10a0(iVar3,iVar5,*param_2,1);
    }
    for (; param_3 = iVar3, param_4 <= iVar4; param_4 = param_4 + 1) {
      for (; param_3 <= iVar1; param_3 = param_3 + 1) {
        puVar2 = (ushort *)FUN_00492d60(param_3,param_4);
        local_10 = (uint)(((float)param_5 * *(float *)(param_1 + 0xf8) +
                          (float)(*puVar2 & 0xfff) * 0.1) / 0.1 + 0.5);
        if ((int)local_10 < 0) {
          local_10 = 0;
        }
        if (0xfff < (int)local_10) {
          local_10 = 0xfff;
        }
        if ((*puVar2 & 0xfff) != local_10) {
          FUN_004c10d0(param_3,param_4,*puVar2);
          *puVar2 = (ushort)local_10;
        }
      }
    }
    FUN_00780b80(iVar3 + -2,iVar5 + -2,iVar1 + 2,iVar4 + 2);
  }
  return;
}

