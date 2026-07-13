
undefined4 FUN_0082ffca(int *param_1,int param_2)

{
  byte *pbVar1;
  byte bVar2;
  
  if (3 < param_1[2]) {
    if (param_1[2] == 4) {
      pbVar1 = (byte *)(*param_1 + 5);
      *pbVar1 = *pbVar1 & 0xfc;
    }
    else {
      bVar2 = *(byte *)(*param_1 + 5);
      if (((bVar2 & 3) != 0) || (((param_1[2] == 7 && (param_2 == 0)) && ((bVar2 & 8) != 0)))) {
        return 1;
      }
    }
  }
  return 0;
}

