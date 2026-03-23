
undefined4 FUN_006b74f0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_10 [8];
  undefined1 local_8 [4];
  
  FUN_006ca750(local_8,param_1);
  uVar2 = FID_conflict_begin(local_10);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 == '\0') {
    FUN_00421ea0();
    iVar3 = FUN_004170c0();
    if (iVar3 != 0) {
      iVar3 = FUN_00421ea0(param_2);
      uVar2 = FUN_006b7860(iVar3 + 0x18,param_2);
      return uVar2;
    }
  }
  return 0;
}

