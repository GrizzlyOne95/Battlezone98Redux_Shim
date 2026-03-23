
undefined1 FUN_007537a0(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  undefined1 local_5;
  
  local_5 = 0;
  puVar2 = (undefined4 *)FUN_00753a00(local_14,&stack0x00000004);
  local_10 = *puVar2;
  uVar3 = FID_conflict_begin(local_18);
  cVar1 = FUN_004221b0(uVar3);
  if (cVar1 == '\0') {
    iVar4 = FUN_00421ea0();
    local_5 = *(undefined1 *)(iVar4 + 4);
  }
  else {
    local_5 = 0;
  }
  return local_5;
}

