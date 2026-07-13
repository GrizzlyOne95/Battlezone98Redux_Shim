/*
 * Entry: 00415859
 * Name: Inst01MissionClass::Matches
 * Namespace: Inst01MissionClass
 * Signature: int Matches(Inst01MissionClass * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall Inst01MissionClass::Matches(Inst01MissionClass *this,char *param_1)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  bool bVar8;
  
  pbVar2 = *(byte **)&this->field_0x4;
  pbVar4 = (byte *)param_1;
  do {
    bVar1 = *pbVar4;
    bVar8 = bVar1 < *pbVar2;
    if (bVar1 != *pbVar2) {
LAB_00415881:
      iVar3 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
      goto LAB_00415886;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar4[1];
    bVar8 = bVar1 < pbVar2[1];
    if (bVar1 != pbVar2[1]) goto LAB_00415881;
    pbVar4 = pbVar4 + 2;
    pbVar2 = pbVar2 + 2;
  } while (bVar1 != 0);
  iVar3 = 0;
LAB_00415886:
  if (iVar3 != 0) {
    iVar3 = 7;
    bVar8 = true;
    iVar5 = iVar3;
    pcVar6 = param_1;
    pcVar7 = "inst02";
    do {
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      bVar8 = *pcVar6 == *pcVar7;
      pcVar6 = pcVar6 + 1;
      pcVar7 = pcVar7 + 1;
    } while (bVar8);
    if (!bVar8) {
      bVar8 = true;
      iVar5 = iVar3;
      pcVar6 = param_1;
      pcVar7 = "inst03";
      do {
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        bVar8 = *pcVar6 == *pcVar7;
        pcVar6 = pcVar6 + 1;
        pcVar7 = pcVar7 + 1;
      } while (bVar8);
      if (!bVar8) {
        bVar8 = true;
        iVar5 = iVar3;
        pcVar6 = param_1;
        pcVar7 = "inst04";
        do {
          if (iVar5 == 0) break;
          iVar5 = iVar5 + -1;
          bVar8 = *pcVar6 == *pcVar7;
          pcVar6 = pcVar6 + 1;
          pcVar7 = pcVar7 + 1;
        } while (bVar8);
        if (!bVar8) {
          bVar8 = true;
          iVar5 = iVar3;
          pcVar6 = param_1;
          pcVar7 = "inst05";
          do {
            if (iVar5 == 0) break;
            iVar5 = iVar5 + -1;
            bVar8 = *pcVar6 == *pcVar7;
            pcVar6 = pcVar6 + 1;
            pcVar7 = pcVar7 + 1;
          } while (bVar8);
          if (!bVar8) {
            bVar8 = true;
            iVar5 = iVar3;
            pcVar6 = param_1;
            pcVar7 = "inst06";
            do {
              if (iVar5 == 0) break;
              iVar5 = iVar5 + -1;
              bVar8 = *pcVar6 == *pcVar7;
              pcVar6 = pcVar6 + 1;
              pcVar7 = pcVar7 + 1;
            } while (bVar8);
            if (!bVar8) {
              bVar8 = true;
              iVar5 = iVar3;
              pcVar6 = param_1;
              pcVar7 = "inst07";
              do {
                if (iVar5 == 0) break;
                iVar5 = iVar5 + -1;
                bVar8 = *pcVar6 == *pcVar7;
                pcVar6 = pcVar6 + 1;
                pcVar7 = pcVar7 + 1;
              } while (bVar8);
              if (!bVar8) {
                bVar8 = true;
                pcVar6 = "inst08";
                do {
                  if (iVar3 == 0) break;
                  iVar3 = iVar3 + -1;
                  bVar8 = *param_1 == *pcVar6;
                  param_1 = param_1 + 1;
                  pcVar6 = pcVar6 + 1;
                } while (bVar8);
                return (uint)bVar8;
              }
            }
          }
        }
      }
    }
  }
  return 1;
}
