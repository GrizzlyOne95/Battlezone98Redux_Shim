
undefined4 FUN_00577200(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  cVar1 = FUN_0073a900();
  if (cVar1 != '\0') {
    FUN_00578c20(local_8,param_1);
    uVar2 = FID_conflict_begin(local_c);
    cVar1 = FUN_00420f10(uVar2);
    if ((cVar1 != '\0') && (iVar3 = FUN_00422150(), *(int *)(iVar3 + 0x10) != 0)) {
      FUN_00422150(param_1);
      cVar1 = FUN_0056f780(param_1);
      if (cVar1 != '\0') {
        iVar3 = FUN_00422150();
        return *(undefined4 *)(iVar3 + 0x10);
      }
    }
  }
  return 0;
}

