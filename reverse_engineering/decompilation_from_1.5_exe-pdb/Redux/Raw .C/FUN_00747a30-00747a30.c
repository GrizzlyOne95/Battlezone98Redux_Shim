
undefined4 FUN_00747a30(undefined4 param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  int local_14;
  undefined4 local_10 [2];
  undefined4 local_8;
  
  puVar2 = (undefined4 *)FUN_0042d8c0(local_18);
  local_8 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_begin(local_1c);
  local_10[0] = *puVar2;
  cVar1 = FUN_00420f10(local_10);
  if (cVar1 == '\0') {
    uVar3 = 0;
  }
  else {
    local_14 = FUN_00422e80();
    cVar1 = FUN_00427310(local_14 + 0xfc,param_1);
    if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
      FUN_0042de70();
    }
    uVar3 = 1;
  }
  return uVar3;
}

