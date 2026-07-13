/*
 * Entry: 00570b24
 * Name: CheckPlayerSide
 * Namespace: Global
 * Signature: int CheckPlayerSide(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CheckPlayerSide(void)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  _USAMission *p_Var4;
  _USSRMission *p_Var5;
  _TrainingMission *p_Var6;
  _USAMission *p_Var7;
  _USSRMission *p_Var8;
  _TrainingMission *p_Var9;
  bool bVar10;
  
  p_Var7 = USAMissionList;
  do {
    pbVar2 = &msn_filename;
    p_Var4 = p_Var7;
    do {
      bVar1 = *pbVar2;
      bVar10 = bVar1 < (byte)p_Var4->cMissionName[0];
      if (bVar1 != p_Var4->cMissionName[0]) {
LAB_00570b5c:
        iVar3 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
        goto LAB_00570b61;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar2[1];
      bVar10 = bVar1 < (byte)p_Var4->cMissionName[1];
      if (bVar1 != p_Var4->cMissionName[1]) goto LAB_00570b5c;
      pbVar2 = pbVar2 + 2;
      p_Var4 = (_USAMission *)(p_Var4->cMissionName + 2);
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_00570b61:
    if (iVar3 == 0) {
      return 1;
    }
    p_Var7 = p_Var7 + 1;
  } while ((int)p_Var7 < 0x6383cc);
  p_Var8 = USSRMissionList;
  do {
    pbVar2 = &msn_filename;
    p_Var5 = p_Var8;
    do {
      bVar1 = *pbVar2;
      bVar10 = bVar1 < (byte)p_Var5->cMissionName[0];
      if (bVar1 != p_Var5->cMissionName[0]) {
LAB_00570b9b:
        iVar3 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
        goto LAB_00570ba0;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar2[1];
      bVar10 = bVar1 < (byte)p_Var5->cMissionName[1];
      if (bVar1 != p_Var5->cMissionName[1]) goto LAB_00570b9b;
      pbVar2 = pbVar2 + 2;
      p_Var5 = (_USSRMission *)(p_Var5->cMissionName + 2);
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_00570ba0:
    if (iVar3 == 0) {
      return 2;
    }
    p_Var8 = p_Var8 + 1;
  } while ((int)p_Var8 < 0x63a3f0);
  p_Var9 = TrnMissionList;
  do {
    pbVar2 = &msn_filename;
    p_Var6 = p_Var9;
    do {
      bVar1 = *pbVar2;
      bVar10 = bVar1 < (byte)p_Var6->cMissionName[0];
      if (bVar1 != p_Var6->cMissionName[0]) {
LAB_00570bd5:
        iVar3 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
        goto LAB_00570bda;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar2[1];
      bVar10 = bVar1 < (byte)p_Var6->cMissionName[1];
      if (bVar1 != p_Var6->cMissionName[1]) goto LAB_00570bd5;
      pbVar2 = pbVar2 + 2;
      p_Var6 = (_TrainingMission *)(p_Var6->cMissionName + 2);
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_00570bda:
    if (iVar3 == 0) {
      return 3;
    }
    p_Var9 = p_Var9 + 1;
    if (0x63b3ef < (int)p_Var9) {
      return 0;
    }
  } while( true );
}
