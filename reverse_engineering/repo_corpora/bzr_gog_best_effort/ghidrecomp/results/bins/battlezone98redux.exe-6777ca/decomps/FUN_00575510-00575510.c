
undefined * FUN_00575510(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined *puVar3;
  int iVar4;
  undefined1 local_10 [4];
  undefined1 local_c [8];
  
  FUN_00578f30(local_c,&stack0x00000004);
  uVar2 = FID_conflict_begin(local_10);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 == '\0') {
    iVar4 = FUN_00421ea0();
    puVar3 = (undefined *)(iVar4 + 4);
  }
  else {
    puVar3 = &DAT_009c8fa8;
  }
  return puVar3;
}

