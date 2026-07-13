
int FUN_0083a118(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 1;
  FUN_0083b5a6(param_1,param_2,0);
  iVar1 = FUN_0083b6c3(param_1,0x2c);
  while (iVar1 != 0) {
    FUN_0083c800(*(undefined4 *)(param_1 + 0x30),param_2);
    FUN_0083b5a6(param_1,param_2,0);
    iVar2 = iVar2 + 1;
    iVar1 = FUN_0083b6c3(param_1,0x2c);
  }
  return iVar2;
}

