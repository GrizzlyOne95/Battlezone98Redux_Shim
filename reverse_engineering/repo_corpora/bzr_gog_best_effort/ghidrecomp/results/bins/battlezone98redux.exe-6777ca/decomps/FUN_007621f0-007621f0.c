
undefined4 __thiscall
FUN_007621f0(int *param_1,undefined4 param_2,char param_3,int param_4,undefined4 param_5,
            undefined4 param_6)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 *puVar4;
  char *pcVar5;
  int *piVar6;
  undefined1 *puVar7;
  int local_8;
  
  iVar1 = FID_conflict_max_size();
  if ((uint)param_1[1] < iVar1 - 1U) {
    uVar2 = FUN_00417780(param_5);
    iVar1 = FUN_00431ef0(param_6,uVar2);
    param_1[1] = param_1[1] + 1;
    *(int *)(iVar1 + 4) = param_4;
    local_8 = iVar1;
    if (param_4 == *param_1) {
      piVar3 = (int *)FUN_00422ea0();
      *piVar3 = iVar1;
      piVar3 = (int *)FUN_00422e60();
      *piVar3 = iVar1;
      piVar3 = (int *)FUN_00422e80();
      *piVar3 = iVar1;
    }
    else if (param_3 == '\0') {
      piVar3 = (int *)FUN_004242f0(param_4);
      *piVar3 = iVar1;
      piVar3 = (int *)FUN_00422e80();
      if (param_4 == *piVar3) {
        piVar3 = (int *)FUN_00422e80();
        *piVar3 = iVar1;
      }
    }
    else {
      piVar3 = (int *)FUN_00417780(param_4);
      *piVar3 = iVar1;
      piVar3 = (int *)FUN_00422e60();
      if (param_4 == *piVar3) {
        piVar3 = (int *)FUN_00422e60();
        *piVar3 = iVar1;
      }
    }
    while( true ) {
      puVar4 = (undefined4 *)FUN_004242e0(local_8);
      pcVar5 = (char *)FUN_00425000(*puVar4);
      if (*pcVar5 != '\0') break;
      piVar3 = (int *)FUN_004242e0(local_8);
      puVar4 = (undefined4 *)FUN_004242e0(local_8);
      puVar4 = (undefined4 *)FUN_004242e0(*puVar4);
      piVar6 = (int *)FUN_00417780(*puVar4);
      if (*piVar3 == *piVar6) {
        puVar4 = (undefined4 *)FUN_004242e0(local_8);
        puVar4 = (undefined4 *)FUN_004242e0(*puVar4);
        puVar4 = (undefined4 *)FUN_004242f0(*puVar4);
        uVar2 = *puVar4;
        pcVar5 = (char *)FUN_00425000(uVar2);
        if (*pcVar5 == '\0') {
          puVar4 = (undefined4 *)FUN_004242e0(local_8);
          puVar7 = (undefined1 *)FUN_00425000(*puVar4);
          *puVar7 = 1;
          puVar7 = (undefined1 *)FUN_00425000(uVar2);
          *puVar7 = 1;
          puVar4 = (undefined4 *)FUN_004242e0(local_8);
          puVar4 = (undefined4 *)FUN_004242e0(*puVar4);
          puVar7 = (undefined1 *)FUN_00425000(*puVar4);
          *puVar7 = 0;
          puVar4 = (undefined4 *)FUN_004242e0(local_8);
          piVar3 = (int *)FUN_004242e0(*puVar4);
          local_8 = *piVar3;
        }
        else {
          puVar4 = (undefined4 *)FUN_004242e0(local_8);
          piVar3 = (int *)FUN_004242f0(*puVar4);
          if (local_8 == *piVar3) {
            piVar3 = (int *)FUN_004242e0(local_8);
            local_8 = *piVar3;
            FUN_00426090(local_8);
          }
          puVar4 = (undefined4 *)FUN_004242e0(local_8);
          puVar7 = (undefined1 *)FUN_00425000(*puVar4);
          *puVar7 = 1;
          puVar4 = (undefined4 *)FUN_004242e0(local_8);
          puVar4 = (undefined4 *)FUN_004242e0(*puVar4);
          puVar7 = (undefined1 *)FUN_00425000(*puVar4);
          *puVar7 = 0;
          puVar4 = (undefined4 *)FUN_004242e0(local_8);
          puVar4 = (undefined4 *)FUN_004242e0(*puVar4);
          FUN_004261c0(*puVar4);
        }
      }
      else {
        puVar4 = (undefined4 *)FUN_004242e0(local_8);
        puVar4 = (undefined4 *)FUN_004242e0(*puVar4);
        puVar4 = (undefined4 *)FUN_00417780(*puVar4);
        uVar2 = *puVar4;
        pcVar5 = (char *)FUN_00425000(uVar2);
        if (*pcVar5 == '\0') {
          puVar4 = (undefined4 *)FUN_004242e0(local_8);
          puVar7 = (undefined1 *)FUN_00425000(*puVar4);
          *puVar7 = 1;
          puVar7 = (undefined1 *)FUN_00425000(uVar2);
          *puVar7 = 1;
          puVar4 = (undefined4 *)FUN_004242e0(local_8);
          puVar4 = (undefined4 *)FUN_004242e0(*puVar4);
          puVar7 = (undefined1 *)FUN_00425000(*puVar4);
          *puVar7 = 0;
          puVar4 = (undefined4 *)FUN_004242e0(local_8);
          piVar3 = (int *)FUN_004242e0(*puVar4);
          local_8 = *piVar3;
        }
        else {
          puVar4 = (undefined4 *)FUN_004242e0(local_8);
          piVar3 = (int *)FUN_00417780(*puVar4);
          if (local_8 == *piVar3) {
            piVar3 = (int *)FUN_004242e0(local_8);
            local_8 = *piVar3;
            FUN_004261c0(local_8);
          }
          puVar4 = (undefined4 *)FUN_004242e0(local_8);
          puVar7 = (undefined1 *)FUN_00425000(*puVar4);
          *puVar7 = 1;
          puVar4 = (undefined4 *)FUN_004242e0(local_8);
          puVar4 = (undefined4 *)FUN_004242e0(*puVar4);
          puVar7 = (undefined1 *)FUN_00425000(*puVar4);
          *puVar7 = 0;
          puVar4 = (undefined4 *)FUN_004242e0(local_8);
          puVar4 = (undefined4 *)FUN_004242e0(*puVar4);
          FUN_00426090(*puVar4);
        }
      }
    }
    puVar4 = (undefined4 *)FUN_00422ea0();
    puVar7 = (undefined1 *)FUN_00425000(*puVar4);
    *puVar7 = 1;
    _Vector_iterator<>(iVar1,param_1);
    return param_2;
  }
  FUN_004328f0(param_6);
                    /* WARNING: Subroutine does not return */
  std::_Xlength_error("map/set<T> too long");
}

