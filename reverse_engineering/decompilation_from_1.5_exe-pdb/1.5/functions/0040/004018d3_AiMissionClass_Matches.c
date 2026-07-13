/*
 * Entry: 004018d3
 * Name: AiMissionClass::Matches
 * Namespace: AiMissionClass
 * Signature: int Matches(AiMissionClass * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall AiMissionClass::Matches(AiMissionClass *this,char *param_1)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  bool bVar4;
  
  pbVar3 = (byte *)this->name;
  do {
    bVar1 = *param_1;
    bVar4 = bVar1 < *pbVar3;
    if (bVar1 != *pbVar3) {
LAB_004018f8:
      iVar2 = (1 - (uint)bVar4) - (uint)(bVar4 != 0);
      goto LAB_004018fd;
    }
    if (bVar1 == 0) break;
    bVar1 = param_1[1];
    bVar4 = bVar1 < pbVar3[1];
    if (bVar1 != pbVar3[1]) goto LAB_004018f8;
    param_1 = param_1 + 2;
    pbVar3 = pbVar3 + 2;
  } while (bVar1 != 0);
  iVar2 = 0;
LAB_004018fd:
  return (uint)(iVar2 == 0);
}
