
undefined * FUN_006b7490(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined *puVar3;
  int iVar4;
  undefined1 local_10 [4];
  undefined1 local_c [8];
  
  FUN_006ca750(local_c,param_1);
  uVar2 = FID_conflict_begin(local_10);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 == '\0') {
    iVar4 = FUN_00421ea0();
    puVar3 = (undefined *)(iVar4 + 0x18);
  }
  else {
    puVar3 = &DAT_0260b0a8;
  }
  return puVar3;
}

