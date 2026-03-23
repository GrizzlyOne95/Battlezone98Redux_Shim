
int FUN_0083c7b7(int param_1,int *param_2)

{
  FUN_0083c667(param_1,param_2);
  if (*param_2 == 0xc) {
    if (param_2[4] == param_2[5]) goto LAB_0083c7f9;
    if ((int)(uint)*(byte *)(param_1 + 0x32) <= param_2[2]) {
      FUN_0083c26e(param_1,param_2,param_2[2]);
      goto LAB_0083c7f9;
    }
  }
  FUN_0083c800(param_1,param_2);
LAB_0083c7f9:
  return param_2[2];
}

