
bool FUN_004e3620(int param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  undefined1 local_18 [4];
  int local_14;
  undefined4 local_c;
  int local_8;
  
  local_8 = param_1 + 0x68;
  FUN_004e3220(*(undefined4 *)(param_1 + 0x70),&local_c,local_18);
  local_14 = FUN_004e3210(local_c,param_2);
  if (local_14 == *(int *)(local_8 + 8)) {
    bVar2 = *(int *)(param_1 + 100) != 0;
  }
  else {
    *(int *)(local_8 + 8) = local_14;
    iVar1 = FUN_004e35a0(param_1,local_c,param_2);
    if (iVar1 == 0) {
      if ((param_2 == 1) || (iVar1 = FUN_004e35a0(param_1,local_c,0), iVar1 == 0)) {
        *(undefined4 *)(param_1 + 100) = 0;
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
    }
    else {
      bVar2 = true;
    }
  }
  return bVar2;
}

