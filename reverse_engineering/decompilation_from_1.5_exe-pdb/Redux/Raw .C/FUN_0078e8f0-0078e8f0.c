
void __fastcall FUN_0078e8f0(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  int local_14;
  float local_10;
  float local_c;
  
  FUN_0078c4e0();
  switch(*(undefined4 *)(param_1 + 0x148)) {
  case 0:
    for (local_14 = 0; iVar2 = size(), local_14 < iVar2; local_14 = local_14 + 1) {
      puVar3 = (undefined4 *)FUN_004200d0(local_14);
      (**(code **)(*(int *)*puVar3 + 0x34))();
    }
    if ((*(int *)(param_1 + 0x164) != 0) && (cVar1 = FUN_007d3d60(), cVar1 != '\0')) {
      FUN_0078cb40();
    }
    break;
  case 1:
  case 3:
    iVar2 = FUN_00822e60();
    iVar2 = iVar2 - *(int *)(param_1 + 0x14c);
    local_10 = (float)((double)iVar2 + (double)(&DAT_008a2fd0)[-(iVar2 >> 0x1f)]) / 1000.0;
    if (local_10 < 0.0) {
      local_10 = 0.0;
    }
    if (1.0 < local_10) {
      local_10 = 1.0;
    }
    FUN_007d2db0(1.0 - local_10);
    break;
  case 2:
    iVar2 = FUN_00822e60();
    iVar2 = iVar2 - *(int *)(param_1 + 0x14c);
    local_c = (float)((double)iVar2 + (double)(&DAT_008a2fd0)[-(iVar2 >> 0x1f)]) / 1000.0;
    if (local_c < 0.0) {
      local_c = 0.0;
    }
    if (1.0 < local_c) {
      local_c = 1.0;
    }
    FUN_007d2db0(local_c);
  }
  piVar4 = (int *)FUN_007647b0();
  if ((((*(int *)(param_1 + 0x178) != 0) && (cVar1 = FUN_007d3360(), cVar1 == '\0')) &&
      (piVar4 != (int *)0x0)) && (cVar1 = (**(code **)(*piVar4 + 4))(), cVar1 != '\0')) {
    (**(code **)(**(int **)(param_1 + 0x178) + 0x24))(1);
  }
  FUN_0078eb50();
  return;
}

