
int FUN_0082bae0(undefined4 param_1,undefined4 param_2,int param_3,undefined4 *param_4)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  byte *pbVar7;
  bool bVar8;
  
  if (param_3 == 0) {
    pbVar2 = (byte *)FUN_0082ba59(param_1,param_2,0);
  }
  else {
    pbVar2 = (byte *)FUN_0082c225(param_1,param_2,param_3);
  }
  iVar6 = 0;
  pbVar3 = (byte *)*param_4;
  do {
    pbVar7 = pbVar2;
    if (pbVar3 == (byte *)0x0) {
      uVar5 = FUN_0082cc9e(param_1,"invalid option \'%s\'",pbVar2);
      iVar6 = FUN_0082b8e4(param_1,param_2,uVar5);
      return iVar6;
    }
    do {
      bVar1 = *pbVar3;
      bVar8 = bVar1 < *pbVar7;
      if (bVar1 != *pbVar7) {
LAB_0082bb53:
        uVar4 = -(uint)bVar8 | 1;
        goto LAB_0082bb58;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar8 = bVar1 < pbVar7[1];
      if (bVar1 != pbVar7[1]) goto LAB_0082bb53;
      pbVar3 = pbVar3 + 2;
      pbVar7 = pbVar7 + 2;
    } while (bVar1 != 0);
    uVar4 = 0;
LAB_0082bb58:
    if (uVar4 == 0) {
      return iVar6;
    }
    iVar6 = iVar6 + 1;
    pbVar3 = (byte *)param_4[iVar6];
  } while( true );
}

