
undefined2 FUN_007589b0(undefined4 param_1)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_10 [4];
  undefined1 local_c [8];
  
  FUN_00747fe0(local_c,param_1);
  uVar3 = FID_conflict_begin(local_10);
  cVar1 = FUN_00420f10(uVar3);
  if (cVar1 == '\0') {
    uVar2 = 0;
  }
  else {
    iVar4 = FUN_00421ea0();
    uVar2 = *(undefined2 *)(iVar4 + 0x10);
  }
  return uVar2;
}

