
bool FUN_007809d0(float param_1,float param_2,float param_3)

{
  int iVar1;
  byte *pbVar2;
  undefined1 *puVar3;
  int iVar4;
  bool bVar5;
  
  bVar5 = DAT_009454b8 == 0;
  if (bVar5) {
    iVar1 = (int)(param_1 * DAT_02cc50e4);
    iVar4 = (int)(param_2 * DAT_02cc50e4);
    pbVar2 = (byte *)FUN_0050ce30(iVar1 + -1,iVar4 + -1,(int)((param_3 * -0.25) / 0.1),
                                  (int)(param_3 / 0.1));
    *pbVar2 = *pbVar2 >> 1;
    pbVar2 = (byte *)FUN_0050ce30(iVar1,iVar4 + -1);
    *pbVar2 = *pbVar2 >> 2;
    pbVar2 = (byte *)FUN_0050ce30(iVar1 + 1,iVar4 + -1);
    *pbVar2 = *pbVar2 >> 1;
    pbVar2 = (byte *)FUN_0050ce30(iVar1 + -1,iVar4);
    *pbVar2 = *pbVar2 >> 2;
    puVar3 = (undefined1 *)FUN_0050ce30(iVar1,iVar4);
    *puVar3 = 0;
    pbVar2 = (byte *)FUN_0050ce30(iVar1 + 1,iVar4);
    *pbVar2 = *pbVar2 >> 2;
    pbVar2 = (byte *)FUN_0050ce30(iVar1 + -1,iVar4 + 1);
    *pbVar2 = *pbVar2 >> 1;
    pbVar2 = (byte *)FUN_0050ce30(iVar1,iVar4 + 1);
    *pbVar2 = *pbVar2 >> 2;
    pbVar2 = (byte *)FUN_0050ce30(iVar1 + 1,iVar4 + 1);
    *pbVar2 = *pbVar2 >> 1;
  }
  return bVar5;
}

