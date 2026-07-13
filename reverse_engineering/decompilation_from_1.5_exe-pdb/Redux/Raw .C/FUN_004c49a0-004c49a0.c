
void __thiscall
FUN_004c49a0(CDialog *param_1,DLGTEMPLATE *param_2,CWnd *param_3,void *param_4,int param_5,
            int param_6)

{
  int iVar1;
  int iVar2;
  ushort *puVar3;
  int iVar4;
  int iVar5;
  int local_14;
  int local_10;
  uint local_c;
  
  if ((*(int *)(param_1 + 0xec) < 1) && (*(int *)(param_1 + 0xf0) < 1)) {
    CDialog::CreateIndirect(param_1,param_2,param_3,param_4);
  }
  if (((*(float *)(param_1 + 0x144) != *(float *)(param_1 + 0xfc)) ||
      (*(int *)(param_1 + 0x13c) != *(int *)(param_1 + 0xec))) ||
     (*(int *)(param_1 + 0x140) != *(int *)(param_1 + 0xf0))) {
    FUN_004c4370();
  }
  iVar5 = (int)param_3 - *(int *)(param_1 + 0xec) / 2;
  iVar1 = *(int *)(param_1 + 0xec);
  iVar4 = (int)param_4 - *(int *)(param_1 + 0xf0) / 2;
  iVar2 = *(int *)(param_1 + 0xf0);
  if (param_6 != 0) {
    FUN_004c10a0(param_3,param_4,*(undefined2 *)param_2,1);
  }
  local_10 = 0;
  for (param_4 = (void *)iVar4; (int)param_4 <= iVar4 + iVar2; param_4 = (void *)((int)param_4 + 1))
  {
    local_14 = 0;
    for (param_3 = (CWnd *)iVar5; (int)param_3 <= iVar5 + iVar1;
        param_3 = (CWnd *)((int)param_3 + 1)) {
      puVar3 = (ushort *)FUN_00492d60(param_3,param_4);
      local_c = (*puVar3 & 0xfff) +
                (int)(*(float *)(param_1 + 0xf4) * 10.0 *
                     *(float *)(param_1 + local_14 * 4 + local_10 * 0x100 + 0x148)) * param_5;
      if ((int)local_c < 0) {
        local_c = 0;
      }
      if (0xfff < (int)local_c) {
        local_c = 0xfff;
      }
      if ((*puVar3 & 0xfff) != local_c) {
        FUN_004c10d0(param_3,param_4,*puVar3);
        *puVar3 = (ushort)local_c;
      }
      local_14 = local_14 + 1;
    }
    local_10 = local_10 + 1;
  }
  FUN_00780b80(iVar5 + -2,iVar4 + -2,iVar5 + iVar1 + 2,iVar4 + iVar2 + 2);
  return;
}

