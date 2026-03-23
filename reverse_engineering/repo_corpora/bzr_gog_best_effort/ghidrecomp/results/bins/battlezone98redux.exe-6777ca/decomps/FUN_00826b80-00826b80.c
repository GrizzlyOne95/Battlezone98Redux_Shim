
int FUN_00826b80(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  while( true ) {
    if (param_1 == 0) {
      return 0;
    }
    if ((*(int *)(param_1 + 8) == param_2) && (*(int *)(param_1 + 0xc) == param_3)) break;
    iVar1 = FUN_00826b80(*(undefined4 *)(param_1 + 0x80),param_2,param_3);
    if (iVar1 != 0) {
      return iVar1;
    }
    param_1 = *(int *)(param_1 + 0x7c);
  }
  return param_1;
}

