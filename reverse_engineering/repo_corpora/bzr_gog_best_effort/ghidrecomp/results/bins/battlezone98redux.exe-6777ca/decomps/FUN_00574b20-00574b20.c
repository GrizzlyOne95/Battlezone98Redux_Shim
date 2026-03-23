
undefined4 FUN_00574b20(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_10 [4];
  undefined1 local_c [8];
  
  FUN_00578a50(local_c,param_2);
  uVar2 = FID_conflict_begin(local_10);
  cVar1 = FUN_00420f10(uVar2);
  if (cVar1 == '\0') {
    FUN_0073a6b0();
  }
  else {
    iVar3 = FUN_00421ea0();
    FUN_0073a740(iVar3 + 8);
  }
  return param_1;
}

