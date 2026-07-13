/*
 * Entry: 0044bdce
 * Name: MPMissionClass::Matches
 * Namespace: MPMissionClass
 * Signature: int Matches(MPMissionClass * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall MPMissionClass::Matches(MPMissionClass *this,char *param_1)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  
  pbVar2 = *(byte **)&this->field_0x4;
  pbVar4 = (byte *)param_1;
  do {
    bVar1 = *pbVar4;
    bVar7 = bVar1 < *pbVar2;
    if (bVar1 != *pbVar2) {
LAB_0044bdf6:
      iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
      goto LAB_0044bdfb;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar4[1];
    bVar7 = bVar1 < pbVar2[1];
    if (bVar1 != pbVar2[1]) goto LAB_0044bdf6;
    pbVar4 = pbVar4 + 2;
    pbVar2 = pbVar2 + 2;
  } while (bVar1 != 0);
  iVar3 = 0;
LAB_0044bdfb:
  if (iVar3 != 0) {
    iVar3 = 3;
    bVar7 = true;
    pcVar5 = param_1;
    pcVar6 = "mp";
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar7 = *pcVar5 == *pcVar6;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    } while (bVar7);
    if (!bVar7) {
      iVar3 = 7;
      bVar7 = true;
      pcVar5 = param_1;
      pcVar6 = "bowlmp";
      do {
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        bVar7 = *pcVar5 == *pcVar6;
        pcVar5 = pcVar5 + 1;
        pcVar6 = pcVar6 + 1;
      } while (bVar7);
      if (!bVar7) {
        iVar3 = 6;
        bVar7 = true;
        pcVar5 = param_1;
        pcVar6 = "warmp";
        do {
          if (iVar3 == 0) break;
          iVar3 = iVar3 + -1;
          bVar7 = *pcVar5 == *pcVar6;
          pcVar5 = pcVar5 + 1;
          pcVar6 = pcVar6 + 1;
        } while (bVar7);
        if (!bVar7) {
          bVar7 = true;
          iVar3 = 6;
          pcVar5 = "test5";
          do {
            if (iVar3 == 0) break;
            iVar3 = iVar3 + -1;
            bVar7 = *param_1 == *pcVar5;
            param_1 = param_1 + 1;
            pcVar5 = pcVar5 + 1;
          } while (bVar7);
          return (uint)bVar7;
        }
      }
    }
  }
  return 1;
}
