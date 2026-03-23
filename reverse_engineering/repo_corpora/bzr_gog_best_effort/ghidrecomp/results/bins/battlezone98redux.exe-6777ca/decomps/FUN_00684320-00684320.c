
undefined1 FUN_00684320(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [8];
  
  iVar2 = FUN_00416410();
  iVar3 = FUN_00416410();
  if (iVar2 == iVar3) {
    puVar4 = (undefined4 *)FUN_00424640(local_c);
    uVar6 = *puVar4;
    puVar4 = (undefined4 *)FID_conflict_begin(local_10);
    uVar5 = *puVar4;
    puVar4 = (undefined4 *)FUN_00424640(local_14);
    cVar1 = FUN_00684650(*puVar4,uVar5,uVar6);
    if (cVar1 != '\0') {
      return 1;
    }
  }
  return 0;
}

