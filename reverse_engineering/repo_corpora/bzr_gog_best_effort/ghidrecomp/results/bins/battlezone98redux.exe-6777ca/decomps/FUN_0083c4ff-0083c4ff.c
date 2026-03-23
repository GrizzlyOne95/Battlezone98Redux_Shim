
void FUN_0083c4ff(int *param_1,int param_2)

{
  param_2 = param_1[9] + param_2;
  if ((int)(uint)*(byte *)(*param_1 + 0x4b) < param_2) {
    if (0xf9 < param_2) {
      FUN_008390b7(param_1[3],"function or expression too complex");
    }
    *(char *)(*param_1 + 0x4b) = (char)param_2;
  }
  return;
}

