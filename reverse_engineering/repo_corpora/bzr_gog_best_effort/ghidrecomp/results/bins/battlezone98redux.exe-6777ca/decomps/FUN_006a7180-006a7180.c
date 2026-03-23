
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_006a7180(int param_1)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  float10 fVar7;
  int local_20;
  int local_18;
  
  if (*(int *)(param_1 + 0xc) == 0) {
    if ((*(int *)(*(int *)(param_1 + 0x40) + 0x60) != 0) &&
       (0 < *(int *)(*(int *)(*(int *)(param_1 + 0x40) + 0x60) + 0x408))) {
      _DAT_009310bc = "Schedule\\scheduler.cpp";
      _DAT_009310c0 = 0x25f;
      FUN_006a5f50(0x800);
    }
    if (*(int *)(param_1 + 0x38) < *(int *)(*(int *)(param_1 + 0x40) + 0x24)) {
      local_20 = 0;
      while ((local_20 < 0x96 &&
             (*(int *)(param_1 + 0x38) < *(int *)(*(int *)(param_1 + 0x40) + 0x24)))) {
        iVar3 = FUN_0069d590(*(int *)(param_1 + 0x40) + 0x1c);
        if ((*(int *)(iVar3 + 0x38) == 0) && (0 < *(int *)(iVar3 + 0x14))) {
          for (local_18 = 0; local_18 < *(int *)(*(int *)(param_1 + 0x28) + 8);
              local_18 = local_18 + 1) {
            piVar4 = (int *)FUN_0069d590(*(undefined4 *)(param_1 + 0x28));
            fVar7 = (float10)(**(code **)(*piVar4 + 0x18))();
            fVar1 = (float)fVar7;
            if ((-5e+08 < fVar1) && ((double)fVar1 < *(double *)(param_1 + 0x80))) {
              *(double *)(param_1 + 0x80) = (double)fVar1;
            }
            if (*(double *)(param_1 + 0x78) <= (double)fVar1 &&
                (double)fVar1 != *(double *)(param_1 + 0x78)) {
              *(double *)(param_1 + 0x78) = (double)fVar1;
            }
            piVar5 = malloc(0x28);
            if ((*(int *)(*(int *)(param_1 + 0x40) + 0x60) != 0) &&
               (2 < *(int *)(*(int *)(*(int *)(param_1 + 0x40) + 0x60) + 0x408))) {
              _DAT_009310bc = "Schedule\\scheduler.cpp";
              _DAT_009310c0 = 0x29d;
              FUN_006a5f50(0x800,"ALLOCATING match @%d",piVar5);
            }
            piVar5[1] = iVar3;
            iVar6 = FUN_006a8850();
            *piVar5 = iVar6;
            *(undefined4 *)(*piVar5 + 0x3c) = 1;
            *(undefined4 *)*piVar5 = *(undefined4 *)(*(int *)(param_1 + 0x40) + 0x44);
            *(int *)(*(int *)(param_1 + 0x40) + 0x44) =
                 *(int *)(*(int *)(param_1 + 0x40) + 0x44) + 1;
            *(undefined4 *)(*piVar5 + 0x40) = *(undefined4 *)(param_1 + 0x40);
            piVar5[2] = (int)piVar4;
            *(double *)(piVar5 + 6) = (double)fVar1;
            piVar5[3] = 0;
            piVar5[4] = *(int *)(iVar3 + 0x34);
            piVar5[8] = 0;
            FUN_006a8630(*(undefined4 *)(param_1 + 0x24),piVar5,(double)fVar1);
            local_20 = local_20 + 1;
          }
        }
        *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + 1;
      }
      uVar2 = 1;
    }
    else {
      *(undefined4 *)(param_1 + 0xc) = 1;
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

