
undefined4 __thiscall FUN_0066a560(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  char *pcVar3;
  int *piVar4;
  undefined4 *puVar5;
  char *pcVar6;
  undefined1 *puVar7;
  undefined1 *puVar8;
  undefined4 uVar9;
  int local_20;
  int local_1c;
  int local_10;
  int local_c;
  int local_8;
  
  iVar1 = get();
  FUN_00422190();
  puVar2 = (undefined4 *)FUN_00417780(iVar1);
  pcVar3 = (char *)FUN_004242d0(*puVar2);
  local_8 = iVar1;
  if (*pcVar3 == '\0') {
    puVar2 = (undefined4 *)FUN_004242f0(iVar1);
    pcVar3 = (char *)FUN_004242d0(*puVar2);
    if (*pcVar3 == '\0') {
      local_8 = get();
      piVar4 = (int *)FUN_004242f0(local_8);
      local_10 = *piVar4;
    }
    else {
      piVar4 = (int *)FUN_00417780(iVar1);
      local_10 = *piVar4;
    }
  }
  else {
    piVar4 = (int *)FUN_004242f0(iVar1);
    local_10 = *piVar4;
  }
  if (local_8 == iVar1) {
    piVar4 = (int *)FUN_004242e0(iVar1);
    local_c = *piVar4;
    pcVar3 = (char *)FUN_004242d0(local_10);
    if (*pcVar3 == '\0') {
      piVar4 = (int *)FUN_004242e0(local_10);
      *piVar4 = local_c;
    }
    piVar4 = (int *)FUN_00422ea0();
    if (*piVar4 == iVar1) {
      piVar4 = (int *)FUN_00422ea0();
      *piVar4 = local_10;
    }
    else {
      piVar4 = (int *)FUN_00417780(local_c);
      if (*piVar4 == iVar1) {
        piVar4 = (int *)FUN_00417780(local_c);
        *piVar4 = local_10;
      }
      else {
        piVar4 = (int *)FUN_004242f0(local_c);
        *piVar4 = local_10;
      }
    }
    piVar4 = (int *)FUN_00422e60();
    if (*piVar4 == iVar1) {
      pcVar3 = (char *)FUN_004242d0(local_10);
      local_1c = local_c;
      if (*pcVar3 == '\0') {
        local_1c = FUN_00424310(local_10);
      }
      piVar4 = (int *)FUN_00422e60();
      *piVar4 = local_1c;
    }
    piVar4 = (int *)FUN_00422e80();
    if (*piVar4 == iVar1) {
      pcVar3 = (char *)FUN_004242d0(local_10);
      local_20 = local_c;
      if (*pcVar3 == '\0') {
        local_20 = FUN_00425010(local_10);
      }
      piVar4 = (int *)FUN_00422e80();
      *piVar4 = local_20;
    }
  }
  else {
    puVar2 = (undefined4 *)FUN_00417780(iVar1);
    piVar4 = (int *)FUN_004242e0(*puVar2);
    *piVar4 = local_8;
    puVar2 = (undefined4 *)FUN_00417780(iVar1);
    puVar5 = (undefined4 *)FUN_00417780(local_8);
    *puVar5 = *puVar2;
    piVar4 = (int *)FUN_004242f0(iVar1);
    if (local_8 == *piVar4) {
      local_c = local_8;
    }
    else {
      piVar4 = (int *)FUN_004242e0(local_8);
      local_c = *piVar4;
      pcVar3 = (char *)FUN_004242d0(local_10);
      if (*pcVar3 == '\0') {
        piVar4 = (int *)FUN_004242e0(local_10);
        *piVar4 = local_c;
      }
      piVar4 = (int *)FUN_00417780(local_c);
      *piVar4 = local_10;
      puVar2 = (undefined4 *)FUN_004242f0(iVar1);
      puVar5 = (undefined4 *)FUN_004242f0(local_8);
      *puVar5 = *puVar2;
      puVar2 = (undefined4 *)FUN_004242f0(iVar1);
      piVar4 = (int *)FUN_004242e0(*puVar2);
      *piVar4 = local_8;
    }
    piVar4 = (int *)FUN_00422ea0();
    if (*piVar4 == iVar1) {
      piVar4 = (int *)FUN_00422ea0();
      *piVar4 = local_8;
    }
    else {
      puVar2 = (undefined4 *)FUN_004242e0(iVar1);
      piVar4 = (int *)FUN_00417780(*puVar2);
      if (*piVar4 == iVar1) {
        puVar2 = (undefined4 *)FUN_004242e0(iVar1);
        piVar4 = (int *)FUN_00417780(*puVar2);
        *piVar4 = local_8;
      }
      else {
        puVar2 = (undefined4 *)FUN_004242e0(iVar1);
        piVar4 = (int *)FUN_004242f0(*puVar2);
        *piVar4 = local_8;
      }
    }
    puVar2 = (undefined4 *)FUN_004242e0(iVar1);
    puVar5 = (undefined4 *)FUN_004242e0(local_8);
    *puVar5 = *puVar2;
    pcVar3 = (char *)FUN_00425000(iVar1);
    pcVar6 = (char *)FUN_00425000(local_8);
    std::swap<char,void>(pcVar6,pcVar3);
  }
  pcVar3 = (char *)FUN_00425000(iVar1);
  if (*pcVar3 != '\x01') {
LAB_0066ac5d:
    uVar9 = FUN_00424300(iVar1);
    uVar9 = FUN_00417780(uVar9);
    FUN_004b4350(uVar9);
    FUN_0066ec00(uVar9);
    uVar9 = 1;
    FUN_004b4350(iVar1,1);
    FUN_004b3230(iVar1,uVar9);
    if (*(int *)(param_1 + 4) != 0) {
      *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + -1;
    }
    _Vector_iterator<>(param_3,param_1);
    return param_2;
  }
LAB_0066a8e1:
  piVar4 = (int *)FUN_00422ea0();
  if ((local_10 == *piVar4) || (pcVar3 = (char *)FUN_00425000(local_10), *pcVar3 != '\x01'))
  goto LAB_0066ac4e;
  piVar4 = (int *)FUN_00417780(local_c);
  if (local_10 == *piVar4) {
    puVar2 = (undefined4 *)FUN_004242f0(local_c);
    local_8 = *puVar2;
    pcVar3 = (char *)FUN_00425000(local_8);
    if (*pcVar3 == '\0') {
      puVar7 = (undefined1 *)FUN_00425000(local_8);
      *puVar7 = 1;
      puVar7 = (undefined1 *)FUN_00425000(local_c);
      *puVar7 = 0;
      FUN_00426090(local_c);
      puVar2 = (undefined4 *)FUN_004242f0(local_c);
      local_8 = *puVar2;
    }
    pcVar3 = (char *)FUN_004242d0(local_8);
    if (*pcVar3 == '\0') {
      puVar2 = (undefined4 *)FUN_00417780(local_8);
      pcVar3 = (char *)FUN_00425000(*puVar2);
      if (*pcVar3 == '\x01') {
        puVar2 = (undefined4 *)FUN_004242f0(local_8);
        pcVar3 = (char *)FUN_00425000(*puVar2);
        if (*pcVar3 == '\x01') {
          puVar7 = (undefined1 *)FUN_00425000(local_8);
          *puVar7 = 0;
          goto LAB_0066a8d0;
        }
      }
      puVar2 = (undefined4 *)FUN_004242f0(local_8);
      pcVar3 = (char *)FUN_00425000(*puVar2);
      if (*pcVar3 == '\x01') {
        puVar2 = (undefined4 *)FUN_00417780(local_8);
        puVar7 = (undefined1 *)FUN_00425000(*puVar2);
        *puVar7 = 1;
        puVar7 = (undefined1 *)FUN_00425000(local_8);
        *puVar7 = 0;
        FUN_004261c0(local_8);
        puVar2 = (undefined4 *)FUN_004242f0(local_c);
        local_8 = *puVar2;
      }
      puVar7 = (undefined1 *)FUN_00425000(local_c);
      puVar8 = (undefined1 *)FUN_00425000(local_8);
      *puVar8 = *puVar7;
      puVar7 = (undefined1 *)FUN_00425000(local_c);
      *puVar7 = 1;
      puVar2 = (undefined4 *)FUN_004242f0(local_8);
      puVar7 = (undefined1 *)FUN_00425000(*puVar2);
      *puVar7 = 1;
      FUN_00426090(local_c);
LAB_0066ac4e:
      puVar7 = (undefined1 *)FUN_00425000(local_10);
      *puVar7 = 1;
      goto LAB_0066ac5d;
    }
  }
  else {
    puVar2 = (undefined4 *)FUN_00417780(local_c);
    local_8 = *puVar2;
    pcVar3 = (char *)FUN_00425000(local_8);
    if (*pcVar3 == '\0') {
      puVar7 = (undefined1 *)FUN_00425000(local_8);
      *puVar7 = 1;
      puVar7 = (undefined1 *)FUN_00425000(local_c);
      *puVar7 = 0;
      FUN_004261c0(local_c);
      puVar2 = (undefined4 *)FUN_00417780(local_c);
      local_8 = *puVar2;
    }
    pcVar3 = (char *)FUN_004242d0(local_8);
    if (*pcVar3 == '\0') {
      puVar2 = (undefined4 *)FUN_004242f0(local_8);
      pcVar3 = (char *)FUN_00425000(*puVar2);
      if (*pcVar3 == '\x01') {
        puVar2 = (undefined4 *)FUN_00417780(local_8);
        pcVar3 = (char *)FUN_00425000(*puVar2);
        if (*pcVar3 == '\x01') {
          puVar7 = (undefined1 *)FUN_00425000(local_8);
          *puVar7 = 0;
          goto LAB_0066a8d0;
        }
      }
      puVar2 = (undefined4 *)FUN_00417780(local_8);
      pcVar3 = (char *)FUN_00425000(*puVar2);
      if (*pcVar3 == '\x01') {
        puVar2 = (undefined4 *)FUN_004242f0(local_8);
        puVar7 = (undefined1 *)FUN_00425000(*puVar2);
        *puVar7 = 1;
        puVar7 = (undefined1 *)FUN_00425000(local_8);
        *puVar7 = 0;
        FUN_00426090(local_8);
        puVar2 = (undefined4 *)FUN_00417780(local_c);
        local_8 = *puVar2;
      }
      puVar7 = (undefined1 *)FUN_00425000(local_c);
      puVar8 = (undefined1 *)FUN_00425000(local_8);
      *puVar8 = *puVar7;
      puVar7 = (undefined1 *)FUN_00425000(local_c);
      *puVar7 = 1;
      puVar2 = (undefined4 *)FUN_00417780(local_8);
      puVar7 = (undefined1 *)FUN_00425000(*puVar2);
      *puVar7 = 1;
      FUN_004261c0(local_c);
      goto LAB_0066ac4e;
    }
  }
LAB_0066a8d0:
  local_10 = local_c;
  piVar4 = (int *)FUN_004242e0(local_c);
  local_c = *piVar4;
  goto LAB_0066a8e1;
}

