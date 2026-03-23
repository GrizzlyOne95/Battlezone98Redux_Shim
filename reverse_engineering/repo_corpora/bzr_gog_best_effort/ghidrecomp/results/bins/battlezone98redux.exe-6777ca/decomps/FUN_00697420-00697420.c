
undefined4 __thiscall FUN_00697420(int param_1,int *param_2)

{
  int iVar1;
  undefined4 uVar2;
  IUnknown *pIVar3;
  
  iVar1 = FUN_00417f90();
  if (iVar1 == 0) {
    if (*(int *)(param_1 + 0x14) == 0) {
      uVar2 = 0;
    }
    else if (*(int *)(*(int *)(param_1 + 0x14) + 0x34) < *(int *)(param_1 + 0x48)) {
      uVar2 = 0;
    }
    else {
      *param_2 = *(int *)(*(int *)(param_1 + 0x14) + 0x34) - *(int *)(param_1 + 0x48);
      pIVar3 = CWnd::GetControlUnknown(*(CWnd **)(param_1 + 0x44));
      if ((int)pIVar3 < *(int *)(param_1 + 0x48)) {
        uVar2 = 0;
      }
      else {
        uVar2 = 1;
      }
    }
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

