
void FUN_004261c0(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  char *pcVar4;
  int *piVar5;
  
  puVar2 = (undefined4 *)FUN_00417780(param_1);
  uVar1 = *puVar2;
  puVar2 = (undefined4 *)FUN_004242f0(uVar1);
  puVar3 = (undefined4 *)FUN_00417780(param_1);
  *puVar3 = *puVar2;
  puVar2 = (undefined4 *)FUN_004242f0(uVar1);
  pcVar4 = (char *)FUN_004242d0(*puVar2);
  if (*pcVar4 == '\0') {
    puVar2 = (undefined4 *)FUN_004242f0(uVar1);
    piVar5 = (int *)FUN_004242e0(*puVar2);
    *piVar5 = param_1;
  }
  puVar2 = (undefined4 *)FUN_004242e0(param_1);
  puVar3 = (undefined4 *)FUN_004242e0(uVar1);
  *puVar3 = *puVar2;
  piVar5 = (int *)FUN_00422ea0();
  if (param_1 == *piVar5) {
    puVar2 = (undefined4 *)FUN_00422ea0();
    *puVar2 = uVar1;
  }
  else {
    puVar2 = (undefined4 *)FUN_004242e0(param_1);
    piVar5 = (int *)FUN_004242f0(*puVar2);
    if (param_1 == *piVar5) {
      puVar2 = (undefined4 *)FUN_004242e0(param_1);
      puVar2 = (undefined4 *)FUN_004242f0(*puVar2);
      *puVar2 = uVar1;
    }
    else {
      puVar2 = (undefined4 *)FUN_004242e0(param_1);
      puVar2 = (undefined4 *)FUN_00417780(*puVar2);
      *puVar2 = uVar1;
    }
  }
  piVar5 = (int *)FUN_004242f0(uVar1);
  *piVar5 = param_1;
  puVar2 = (undefined4 *)FUN_004242e0(param_1);
  *puVar2 = uVar1;
  return;
}

