
bool FUN_00835f1e(uint param_1,char *param_2,byte *param_3)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  bool bVar5;
  
  bVar5 = param_2[1] != '^';
  if (!bVar5) {
    param_2 = param_2 + 1;
  }
  pbVar4 = (byte *)(param_2 + 1);
  if (pbVar4 < param_3) {
    pbVar3 = (byte *)(param_2 + 3);
    do {
      if (*pbVar4 == 0x25) {
        pbVar4 = pbVar4 + 1;
        pbVar3 = pbVar3 + 1;
        iVar2 = FUN_00835e4f(param_1,*pbVar4);
        if (iVar2 != 0) {
          return bVar5;
        }
      }
      else if ((pbVar4[1] == 0x2d) && (pbVar3 < param_3)) {
        bVar1 = *pbVar4;
        pbVar4 = pbVar4 + 2;
        pbVar3 = pbVar3 + 2;
        if (((int)(uint)bVar1 <= (int)param_1) && ((int)param_1 <= (int)(uint)*pbVar4)) {
          return bVar5;
        }
      }
      else if (*pbVar4 == param_1) {
        return bVar5;
      }
      pbVar4 = pbVar4 + 1;
      pbVar3 = pbVar3 + 1;
    } while (pbVar4 < param_3);
  }
  return !bVar5;
}

