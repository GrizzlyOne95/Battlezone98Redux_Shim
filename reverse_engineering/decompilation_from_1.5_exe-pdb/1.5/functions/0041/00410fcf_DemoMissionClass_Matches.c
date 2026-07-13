/*
 * Entry: 00410fcf
 * Name: DemoMissionClass::Matches
 * Namespace: DemoMissionClass
 * Signature: int Matches(DemoMissionClass * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall DemoMissionClass::Matches(DemoMissionClass *this,char *param_1)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  char *pcVar6;
  bool bVar7;
  
  pbVar2 = *(byte **)&this->field_0x4;
  pbVar5 = (byte *)param_1;
  do {
    bVar1 = *pbVar5;
    bVar7 = bVar1 < *pbVar2;
    if (bVar1 != *pbVar2) {
LAB_00410ff7:
      iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
      goto LAB_00410ffc;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar5[1];
    bVar7 = bVar1 < pbVar2[1];
    if (bVar1 != pbVar2[1]) goto LAB_00410ff7;
    pbVar5 = pbVar5 + 2;
    pbVar2 = pbVar2 + 2;
  } while (bVar1 != 0);
  iVar3 = 0;
LAB_00410ffc:
  if (iVar3 == 0) {
    uVar4 = 1;
  }
  else {
    iVar3 = 5;
    bVar7 = true;
    pcVar6 = "demo";
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar7 = *param_1 == *pcVar6;
      param_1 = param_1 + 1;
      pcVar6 = pcVar6 + 1;
    } while (bVar7);
    uVar4 = (uint)bVar7;
  }
  return uVar4;
}
