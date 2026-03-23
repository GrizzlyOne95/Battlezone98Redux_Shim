
undefined4 FUN_005771b0(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  FUN_005789b0(local_8,&stack0x00000004);
  uVar2 = FID_conflict_begin(local_c);
  cVar1 = FUN_00420f10(uVar2);
  if (cVar1 == '\0') {
    uVar2 = 0;
  }
  else {
    iVar3 = FUN_00422150();
    uVar2 = *(undefined4 *)(iVar3 + 4);
  }
  return uVar2;
}

