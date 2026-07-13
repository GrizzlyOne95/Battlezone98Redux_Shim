
undefined1 FUN_0074c420(undefined4 param_1)

{
  char cVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_10 [8];
  undefined1 local_8 [4];
  
  FUN_00578c20(local_8,param_1);
  uVar3 = FID_conflict_begin(local_10);
  cVar1 = FUN_00420f10(uVar3);
  if (cVar1 == '\0') {
    uVar2 = 1;
  }
  else {
    iVar4 = FUN_00422150();
    uVar2 = *(undefined1 *)(iVar4 + 0x40);
  }
  return uVar2;
}

