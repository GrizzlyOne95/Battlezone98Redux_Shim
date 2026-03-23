
void FUN_0042a3e0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  iVar1 = FUN_004170c0();
  if (iVar1 != 0) {
    FID_conflict_begin(local_8);
    iVar1 = get(param_2);
    iVar2 = FUN_004170c0();
    iVar1 = iVar1 + iVar2;
    FID_conflict_begin(local_c);
    uVar3 = get(iVar1);
    FUN_004180d0(uVar3);
  }
  return;
}

