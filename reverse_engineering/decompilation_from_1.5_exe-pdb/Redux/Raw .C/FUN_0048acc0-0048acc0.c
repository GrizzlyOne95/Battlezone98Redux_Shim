
undefined4 __thiscall FUN_0048acc0(int param_1,undefined4 param_2,undefined4 param_3)

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
  int local_24;
  int local_20;
  int local_14;
  int local_10;
  int local_c;
  undefined1 local_6;
  undefined1 local_5;
  
  iVar1 = get();
  FUN_00422190();
  puVar2 = (undefined4 *)FUN_00417780(iVar1);
  pcVar3 = (char *)FUN_004242d0(*puVar2);
  local_c = iVar1;
  if (*pcVar3 == '\0') {
    puVar2 = (undefined4 *)FUN_004242f0(iVar1);
    pcVar3 = (char *)FUN_004242d0(*puVar2);
    if (*pcVar3 == '\0') {
      local_c = get();
      piVar4 = (int *)FUN_004242f0(local_c);
      local_14 = *piVar4;
    }
    else {
      piVar4 = (int *)FUN_00417780(iVar1);
      local_14 = *piVar4;
    }
  }
  else {
    piVar4 = (int *)FUN_004242f0(iVar1);
    local_14 = *piVar4;
  }
  if (local_c == iVar1) {
    piVar4 = (int *)FUN_004242e0(iVar1);
    local_10 = *piVar4;
    pcVar3 = (char *)FUN_004242d0(local_14);
    if (*pcVar3 == '\0') {
      piVar4 = (int *)FUN_004242e0(local_14);
      *piVar4 = local_10;
    }
    piVar4 = (int *)FUN_00422ea0();
    if (*piVar4 == iVar1) {
      piVar4 = (int *)FUN_00422ea0();
      *piVar4 = local_14;
    }
    else {
      piVar4 = (int *)FUN_00417780(local_10);
      if (*piVar4 == iVar1) {
        piVar4 = (int *)FUN_00417780(local_10);
        *piVar4 = local_14;
      }
      else {
        piVar4 = (int *)FUN_004242f0(local_10);
        *piVar4 = local_14;
      }
    }
    piVar4 = (int *)FUN_00422e60();
    if (*piVar4 == iVar1) {
      pcVar3 = (char *)FUN_004242d0(local_14);
      local_20 = local_10;
      if (*pcVar3 == '\0') {
        local_20 = FUN_00424310(local_14);
      }
      piVar4 = (int *)FUN_00422e60();
      *piVar4 = local_20;
    }
    piVar4 = (int *)FUN_00422e80();
    if (*piVar4 == iVar1) {
      pcVar3 = (char *)FUN_004242d0(local_14);
      local_24 = local_10;
      if (*pcVar3 == '\0') {
        local_24 = FUN_00425010(local_14);
      }
      piVar4 = (int *)FUN_00422e80();
      *piVar4 = local_24;
    }
  }
  else {
    puVar2 = (undefined4 *)FUN_00417780(iVar1);
    piVar4 = (int *)FUN_004242e0(*puVar2);
    *piVar4 = local_c;
    puVar2 = (undefined4 *)FUN_00417780(iVar1);
    puVar5 = (undefined4 *)FUN_00417780(local_c);
    *puVar5 = *puVar2;
    piVar4 = (int *)FUN_004242f0(iVar1);
    if (local_c == *piVar4) {
      local_10 = local_c;
    }
    else {
      piVar4 = (int *)FUN_004242e0(local_c);
      local_10 = *piVar4;
      pcVar3 = (char *)FUN_004242d0(local_14);
      if (*pcVar3 == '\0') {
        piVar4 = (int *)FUN_004242e0(local_14);
        *piVar4 = local_10;
      }
      piVar4 = (int *)FUN_00417780(local_10);
      *piVar4 = local_14;
      puVar2 = (undefined4 *)FUN_004242f0(iVar1);
      puVar5 = (undefined4 *)FUN_004242f0(local_c);
      *puVar5 = *puVar2;
      puVar2 = (undefined4 *)FUN_004242f0(iVar1);
      piVar4 = (int *)FUN_004242e0(*puVar2);
      *piVar4 = local_c;
    }
    piVar4 = (int *)FUN_00422ea0();
    if (*piVar4 == iVar1) {
      piVar4 = (int *)FUN_00422ea0();
      *piVar4 = local_c;
    }
    else {
      puVar2 = (undefined4 *)FUN_004242e0(iVar1);
      piVar4 = (int *)FUN_00417780(*puVar2);
      if (*piVar4 == iVar1) {
        puVar2 = (undefined4 *)FUN_004242e0(iVar1);
        piVar4 = (int *)FUN_00417780(*puVar2);
        *piVar4 = local_c;
      }
      else {
        puVar2 = (undefined4 *)FUN_004242e0(iVar1);
        piVar4 = (int *)FUN_004242f0(*puVar2);
        *piVar4 = local_c;
      }
    }
    puVar2 = (undefined4 *)FUN_004242e0(iVar1);
    puVar5 = (undefined4 *)FUN_004242e0(local_c);
    *puVar5 = *puVar2;
    pcVar3 = (char *)FUN_00425000(iVar1);
    pcVar6 = (char *)FUN_00425000(local_c);
    std::swap<char,void>(pcVar6,pcVar3);
  }
  pcVar3 = (char *)FUN_00425000(iVar1);
  if (*pcVar3 != '\x01') {
LAB_0048b3bd:
    uVar9 = FUN_00424300(iVar1);
    uVar9 = FUN_00417780(uVar9);
    Getal(&local_5);
    destroy<>(uVar9);
    uVar9 = 1;
    Getal(&local_6);
    deallocate(iVar1,uVar9);
    if (*(int *)(param_1 + 4) != 0) {
      *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + -1;
    }
    _Vector_iterator<>(param_3,param_1);
    return param_2;
  }
LAB_0048b041:
  piVar4 = (int *)FUN_00422ea0();
  if ((local_14 == *piVar4) || (pcVar3 = (char *)FUN_00425000(local_14), *pcVar3 != '\x01'))
  goto LAB_0048b3ae;
  piVar4 = (int *)FUN_00417780(local_10);
  if (local_14 == *piVar4) {
    puVar2 = (undefined4 *)FUN_004242f0(local_10);
    local_c = *puVar2;
    pcVar3 = (char *)FUN_00425000(local_c);
    if (*pcVar3 == '\0') {
      puVar7 = (undefined1 *)FUN_00425000(local_c);
      *puVar7 = 1;
      puVar7 = (undefined1 *)FUN_00425000(local_10);
      *puVar7 = 0;
      FUN_00426090(local_10);
      puVar2 = (undefined4 *)FUN_004242f0(local_10);
      local_c = *puVar2;
    }
    pcVar3 = (char *)FUN_004242d0(local_c);
    if (*pcVar3 == '\0') {
      puVar2 = (undefined4 *)FUN_00417780(local_c);
      pcVar3 = (char *)FUN_00425000(*puVar2);
      if (*pcVar3 == '\x01') {
        puVar2 = (undefined4 *)FUN_004242f0(local_c);
        pcVar3 = (char *)FUN_00425000(*puVar2);
        if (*pcVar3 == '\x01') {
          puVar7 = (undefined1 *)FUN_00425000(local_c);
          *puVar7 = 0;
          goto LAB_0048b030;
        }
      }
      puVar2 = (undefined4 *)FUN_004242f0(local_c);
      pcVar3 = (char *)FUN_00425000(*puVar2);
      if (*pcVar3 == '\x01') {
        puVar2 = (undefined4 *)FUN_00417780(local_c);
        puVar7 = (undefined1 *)FUN_00425000(*puVar2);
        *puVar7 = 1;
        puVar7 = (undefined1 *)FUN_00425000(local_c);
        *puVar7 = 0;
        FUN_004261c0(local_c);
        puVar2 = (undefined4 *)FUN_004242f0(local_10);
        local_c = *puVar2;
      }
      puVar7 = (undefined1 *)FUN_00425000(local_10);
      puVar8 = (undefined1 *)FUN_00425000(local_c);
      *puVar8 = *puVar7;
      puVar7 = (undefined1 *)FUN_00425000(local_10);
      *puVar7 = 1;
      puVar2 = (undefined4 *)FUN_004242f0(local_c);
      puVar7 = (undefined1 *)FUN_00425000(*puVar2);
      *puVar7 = 1;
      FUN_00426090(local_10);
LAB_0048b3ae:
      puVar7 = (undefined1 *)FUN_00425000(local_14);
      *puVar7 = 1;
      goto LAB_0048b3bd;
    }
  }
  else {
    puVar2 = (undefined4 *)FUN_00417780(local_10);
    local_c = *puVar2;
    pcVar3 = (char *)FUN_00425000(local_c);
    if (*pcVar3 == '\0') {
      puVar7 = (undefined1 *)FUN_00425000(local_c);
      *puVar7 = 1;
      puVar7 = (undefined1 *)FUN_00425000(local_10);
      *puVar7 = 0;
      FUN_004261c0(local_10);
      puVar2 = (undefined4 *)FUN_00417780(local_10);
      local_c = *puVar2;
    }
    pcVar3 = (char *)FUN_004242d0(local_c);
    if (*pcVar3 == '\0') {
      puVar2 = (undefined4 *)FUN_004242f0(local_c);
      pcVar3 = (char *)FUN_00425000(*puVar2);
      if (*pcVar3 == '\x01') {
        puVar2 = (undefined4 *)FUN_00417780(local_c);
        pcVar3 = (char *)FUN_00425000(*puVar2);
        if (*pcVar3 == '\x01') {
          puVar7 = (undefined1 *)FUN_00425000(local_c);
          *puVar7 = 0;
          goto LAB_0048b030;
        }
      }
      puVar2 = (undefined4 *)FUN_00417780(local_c);
      pcVar3 = (char *)FUN_00425000(*puVar2);
      if (*pcVar3 == '\x01') {
        puVar2 = (undefined4 *)FUN_004242f0(local_c);
        puVar7 = (undefined1 *)FUN_00425000(*puVar2);
        *puVar7 = 1;
        puVar7 = (undefined1 *)FUN_00425000(local_c);
        *puVar7 = 0;
        FUN_00426090(local_c);
        puVar2 = (undefined4 *)FUN_00417780(local_10);
        local_c = *puVar2;
      }
      puVar7 = (undefined1 *)FUN_00425000(local_10);
      puVar8 = (undefined1 *)FUN_00425000(local_c);
      *puVar8 = *puVar7;
      puVar7 = (undefined1 *)FUN_00425000(local_10);
      *puVar7 = 1;
      puVar2 = (undefined4 *)FUN_00417780(local_c);
      puVar7 = (undefined1 *)FUN_00425000(*puVar2);
      *puVar7 = 1;
      FUN_004261c0(local_10);
      goto LAB_0048b3ae;
    }
  }
LAB_0048b030:
  local_14 = local_10;
  piVar4 = (int *)FUN_004242e0(local_10);
  local_10 = *piVar4;
  goto LAB_0048b041;
}

