
int * FUN_0083332e(int *param_1,int *param_2)

{
  int iVar1;
  undefined4 local_c;
  undefined4 uStack_8;
  
  if (param_1[2] != 3) {
    if ((param_1[2] == 4) && (iVar1 = FUN_0082eb45(*param_1 + 0x10,&local_c), iVar1 != 0)) {
      *(ulonglong *)param_2 = CONCAT44(uStack_8,local_c);
      param_2[2] = 3;
      return param_2;
    }
    param_1 = (int *)0x0;
  }
  return param_1;
}

