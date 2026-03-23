
undefined4
FUN_004405e0(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            )

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(param_2 + 0x24);
  if (iVar1 == 1) {
    uVar2 = FUN_00440690(param_1,param_2,param_3,param_4,param_5,1,0);
  }
  else if (iVar1 == 2) {
    uVar2 = FUN_004403f0(param_1,param_2,param_3,param_4,param_5);
  }
  else if (iVar1 == 3) {
    uVar2 = FUN_00440870(param_1,param_2,param_3,param_4,param_5);
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

