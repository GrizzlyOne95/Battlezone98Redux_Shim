
void FUN_008319de(int param_1,undefined4 param_2)

{
  int iVar1;
  
  if ((param_1 == 0) || (iVar1 = param_1 + 0x10, iVar1 == 0)) {
    param_1 = 0;
    FUN_00831758(&param_1,4,param_2);
  }
  else {
    param_1 = *(int *)(param_1 + 0xc) + 1;
    FUN_00831758(&param_1,4,param_2);
    FUN_00831758(iVar1,param_1,param_2);
  }
  return;
}

