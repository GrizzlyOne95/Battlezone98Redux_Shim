
undefined4 __thiscall FUN_00437f30(int param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  int local_10;
  undefined1 local_c [4];
  int local_8;
  
  if (param_2 == 0) {
    uVar2 = 1;
  }
  else if (param_2 == *(int *)(param_1 + 0x3c)) {
    uVar2 = 0;
  }
  else {
    local_8 = param_1;
    FUN_0042d8c0(local_c);
    while( true ) {
      uVar2 = FID_conflict_begin(local_18);
      cVar1 = FUN_00420f10(uVar2);
      if (cVar1 == '\0') break;
      piVar3 = (int *)FUN_0042de50();
      local_10 = *piVar3;
      if (*(int *)(local_10 + 4) == param_2) {
        return 0;
      }
      FUN_00438c10(local_14,0);
    }
    uVar2 = 1;
  }
  return uVar2;
}

