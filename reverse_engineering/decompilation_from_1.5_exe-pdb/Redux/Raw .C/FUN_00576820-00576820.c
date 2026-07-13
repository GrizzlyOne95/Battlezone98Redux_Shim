
void FUN_00576820(undefined2 param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 local_30 [4];
  undefined1 local_2c [12];
  undefined4 local_20;
  int local_1c;
  int *local_18;
  undefined4 local_14;
  int local_10;
  undefined1 *local_c;
  undefined2 local_8;
  
  FUN_005789b0(&local_14,&param_1);
  puVar2 = &local_14;
  FID_conflict_begin(local_2c);
  cVar1 = FUN_004221b0(puVar2);
  if (cVar1 != '\0') {
    local_20 = 0;
    local_8 = 0;
    local_1c = FUN_00764760();
    if (local_1c == 0) {
      return;
    }
    local_10 = FUN_00746720(param_1);
    if (local_10 == 0) {
      return;
    }
    if (*(char *)(local_10 + 0x61) != '\0') {
      return;
    }
    local_20 = *(undefined4 *)(local_10 + 0x80);
    local_8 = *(undefined2 *)(local_10 + 0x28);
    cVar1 = FUN_00578500(local_10 + 8,local_8,local_10 + 0x2c,local_20);
    if (cVar1 == '\0') {
      return;
    }
    puVar2 = (undefined4 *)FUN_005789b0(local_30,&param_1);
    local_14 = *puVar2;
  }
  iVar3 = FUN_00422150();
  local_c = *(undefined1 **)(iVar3 + 4);
  if (local_c != (undefined1 *)0x0) {
    *local_c = 0;
    if (*(int *)(local_c + 0x40) == 0) {
      uVar4 = FUN_00822d90();
      *(undefined4 *)(local_c + 0x40) = uVar4;
      FUN_005757d0();
      local_18 = (int *)FUN_0045ca50();
      if (local_18 != (int *)0x0) {
        (**(code **)(*local_18 + 0x28))(local_c);
      }
    }
    if ((*(int *)(local_c + 0x24) != 0) && (iVar3 = FUN_00572d80(), iVar3 != 0)) {
      FUN_005d8ee0(local_c);
      *(undefined4 *)(local_c + 0x24) = 0;
    }
    iVar3 = FUN_00822e60();
    if ((*(int *)(local_c + 0x48) != 0) && (DAT_00917fa8 < iVar3 - *(int *)(local_c + 0x48))) {
      DAT_00917fa8 = iVar3 - *(int *)(local_c + 0x48);
    }
    *(int *)(local_c + 0x48) = iVar3;
  }
  return;
}

