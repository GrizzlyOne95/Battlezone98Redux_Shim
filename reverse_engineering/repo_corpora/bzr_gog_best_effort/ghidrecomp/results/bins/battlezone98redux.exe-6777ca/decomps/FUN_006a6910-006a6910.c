
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_006a6910(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  float10 fVar4;
  int local_10;
  
  if (*param_1 == 0) {
    if ((*(int *)(param_1[0x10] + 0x60) != 0) &&
       (0 < *(int *)(*(int *)(param_1[0x10] + 0x60) + 0x408))) {
      _DAT_009310bc = "Schedule\\scheduler.cpp";
      _DAT_009310c0 = 0x85;
      FUN_006a5f50(0x800,"\n\nPreparing Goals %d",*(undefined4 *)(param_1[0xc] + 8));
    }
    param_1[0x20] = 0;
    param_1[0x21] = 0x41cdcd65;
    param_1[0x1e] = 0;
    param_1[0x1f] = -0x3e32329b;
    for (local_10 = 0; local_10 < 0xb; local_10 = local_10 + 1) {
      param_1[local_10 + 0x12] = 0;
    }
    iVar2 = FUN_006a8590(*(undefined4 *)(param_1[0xc] + 8));
    param_1[8] = iVar2;
    local_10 = *(int *)(param_1[0xc] + 8);
    while (local_10 = local_10 + -1, -1 < local_10) {
      piVar3 = (int *)FUN_0069d590(param_1[0xc],local_10);
      (**(code **)(*piVar3 + 4))();
      piVar3[8] = 0;
      if (piVar3[1] != 0) {
        fVar4 = (float10)(**(code **)(*piVar3 + 0x1c))();
        if (piVar3[1] != 0) {
          piVar3[7] = -0x319194d8;
          (**(code **)(*piVar3 + 0x14))();
          FUN_006a8630(param_1[8],piVar3,(double)fVar4);
        }
      }
      piVar3[6] = 0;
      if (piVar3[10] == 0) {
        FUN_0069d440(param_1[0xc],piVar3[0xd]);
      }
    }
    param_1[7] = *(int *)(param_1[8] + 8) + -1;
    iVar2 = FUN_0069d250();
    param_1[0xb] = iVar2;
    iVar2 = FUN_0069d250();
    param_1[10] = iVar2;
    if ((*(int *)(param_1[0x10] + 0x60) != 0) &&
       (1 < *(int *)(*(int *)(param_1[0x10] + 0x60) + 0x408))) {
      for (local_10 = 0; local_10 < *(int *)(param_1[8] + 8); local_10 = local_10 + 1) {
        piVar3 = (int *)FUN_006a8750(param_1[8],local_10);
        (**(code **)(*piVar3 + 8))();
        _DAT_009310bc = "Schedule\\scheduler.cpp";
        _DAT_009310c0 = 0xf0;
        FUN_006a5f50(0x800,"    GOAL %d........P: %f   S: %d",piVar3[1],(double)(float)piVar3[8],
                     piVar3[4]);
      }
    }
    *param_1 = 1;
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

