
undefined1 __fastcall FUN_0047b8f0(int param_1)

{
  int iVar1;
  undefined1 local_c;
  
  if (*(int *)(param_1 + 0xc) == 0) {
LAB_0047b929:
    local_c = 0;
  }
  else {
    if (*(int *)(*(int *)(param_1 + 0xc) + 0x4c) != 0) {
      iVar1 = FUN_00417c80();
      if (iVar1 < 1) goto LAB_0047b929;
    }
    local_c = 1;
  }
  return local_c;
}

