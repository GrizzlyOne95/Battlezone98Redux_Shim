
void FUN_008376eb(undefined4 param_1,int *param_2)

{
  int iVar1;
  
  FUN_0082cced(param_1,&DAT_0086fc70);
  FUN_0082ce65(param_1,0xffffd8f0);
  FUN_0082cced(param_1,param_1);
  FUN_0082ce65(param_1,0xfffffffe);
  iVar1 = FUN_0082d490(param_1,0xffffffff);
  if (iVar1 == 6) {
    FUN_0082cd77(param_1,(&PTR_DAT_0086fc74)[*param_2]);
    if (param_2[5] < 0) {
      FUN_0082cd45(param_1);
    }
    else {
      FUN_0082ccca(param_1,param_2[5]);
    }
    FUN_0082c585(param_1,2,0);
  }
  return;
}

