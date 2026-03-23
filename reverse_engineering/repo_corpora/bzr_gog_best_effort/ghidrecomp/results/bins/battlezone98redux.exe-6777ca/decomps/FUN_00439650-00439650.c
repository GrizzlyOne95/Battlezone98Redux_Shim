
undefined4 __thiscall FUN_00439650(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  char local_5;
  
  local_5 = '\0';
  if (*(int *)(param_1 + 4) == 0) {
    uVar1 = 0x800401f0;
  }
  else {
    piVar2 = (int *)FUN_00439550();
    if (piVar2 == (int *)0x0) {
      uVar1 = 0x80004005;
    }
    else {
      iVar3 = FUN_004394a0(piVar2,&local_5);
      if (iVar3 < 0) {
        uVar1 = 0x80004005;
      }
      else {
        if (local_5 != '\0') {
          iVar3 = FUN_004392b0(piVar2,0);
          if (iVar3 < 0) {
            return 0x80004005;
          }
          FUN_00439770();
        }
        uVar1 = (**(code **)(*piVar2 + 0x30))(piVar2,0,param_2,param_3);
      }
    }
  }
  return uVar1;
}

