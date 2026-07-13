
int FUN_0077c820(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_14 [4];
  undefined1 local_10 [11];
  undefined1 local_5;
  
  FUN_00579160(local_10,param_1);
  uVar2 = FID_conflict_begin(local_14);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 == '\0') {
    uVar2 = get();
    uVar2 = FUN_00422f10(uVar2);
    FUN_00422f60(&local_5);
    cVar1 = FUN_00579190(param_1,uVar2);
    if (cVar1 == '\0') {
      iVar3 = FUN_00421ea0();
      return iVar3 + 4;
    }
  }
                    /* WARNING: Subroutine does not return */
  std::_Xout_of_range("invalid map<K, T> key");
}

