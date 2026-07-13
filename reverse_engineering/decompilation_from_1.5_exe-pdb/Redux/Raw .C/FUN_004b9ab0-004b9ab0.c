
int FUN_004b9ab0(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  int local_18;
  int local_10;
  undefined4 local_8;
  
  FUN_00430590();
  puVar2 = (undefined4 *)FUN_0046b370(local_1c,&stack0x00000004);
  local_8 = *puVar2;
  uVar3 = FID_conflict_begin(local_20);
  cVar1 = FUN_00420f10(uVar3);
  if ((cVar1 == '\0') || (iVar4 = FUN_00422150(), *(int *)(iVar4 + 4) == 0)) {
    puVar2 = (undefined4 *)FUN_0046b370(local_24,&stack0x00000004);
    local_8 = *puVar2;
    uVar3 = FID_conflict_begin(local_28);
    cVar1 = FUN_00420f10(uVar3);
    if ((cVar1 == '\0') || (iVar4 = FUN_00422150(), *(int *)(iVar4 + 4) == 0)) {
      local_18 = 0;
    }
    else {
      iVar4 = FUN_00422150();
      if (*(int *)(iVar4 + 4) == 0) {
        local_18 = 0;
      }
      else {
        local_18 = *(int *)(iVar4 + 4) + -0x18;
      }
    }
  }
  else {
    iVar4 = FUN_00422150();
    if (*(int *)(iVar4 + 4) == 0) {
      local_10 = 0;
      local_18 = local_10;
    }
    else {
      local_18 = *(int *)(iVar4 + 4) + -0x18;
    }
  }
  return local_18;
}

