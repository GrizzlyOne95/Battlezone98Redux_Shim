/*
 * Entry: 00570bf8
 * Name: CheckMissionIndex
 * Namespace: Global
 * Signature: int CheckMissionIndex(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CheckMissionIndex(void)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  _USAMission *p_Var5;
  _USSRMission *p_Var6;
  _TrainingMission *p_Var7;
  _USAMission *p_Var8;
  _USSRMission *p_Var9;
  _TrainingMission *p_Var10;
  bool bVar11;
  
  iVar2 = 0;
  p_Var8 = USAMissionList;
  do {
    pbVar3 = &msn_filename;
    p_Var5 = p_Var8;
    do {
      bVar1 = *pbVar3;
      bVar11 = bVar1 < (byte)p_Var5->cMissionName[0];
      if (bVar1 != p_Var5->cMissionName[0]) {
LAB_00570c29:
        iVar4 = (1 - (uint)bVar11) - (uint)(bVar11 != 0);
        goto LAB_00570c2e;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar11 = bVar1 < (byte)p_Var5->cMissionName[1];
      if (bVar1 != p_Var5->cMissionName[1]) goto LAB_00570c29;
      pbVar3 = pbVar3 + 2;
      p_Var5 = (_USAMission *)(p_Var5->cMissionName + 2);
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_00570c2e:
    if (iVar4 == 0) {
      return iVar2;
    }
    p_Var8 = p_Var8 + 1;
    iVar2 = iVar2 + 1;
  } while ((int)p_Var8 < 0x6383cc);
  iVar2 = 0;
  p_Var9 = USSRMissionList;
  do {
    pbVar3 = &msn_filename;
    p_Var6 = p_Var9;
    do {
      bVar1 = *pbVar3;
      bVar11 = bVar1 < (byte)p_Var6->cMissionName[0];
      if (bVar1 != p_Var6->cMissionName[0]) {
LAB_00570c6e:
        iVar4 = (1 - (uint)bVar11) - (uint)(bVar11 != 0);
        goto LAB_00570c73;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar11 = bVar1 < (byte)p_Var6->cMissionName[1];
      if (bVar1 != p_Var6->cMissionName[1]) goto LAB_00570c6e;
      pbVar3 = pbVar3 + 2;
      p_Var6 = (_USSRMission *)(p_Var6->cMissionName + 2);
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_00570c73:
    if (iVar4 == 0) {
      return iVar2;
    }
    p_Var9 = p_Var9 + 1;
    iVar2 = iVar2 + 1;
  } while ((int)p_Var9 < 0x63a3f0);
  iVar2 = 0;
  p_Var10 = TrnMissionList;
  do {
    pbVar3 = &msn_filename;
    p_Var7 = p_Var10;
    do {
      bVar1 = *pbVar3;
      bVar11 = bVar1 < (byte)p_Var7->cMissionName[0];
      if (bVar1 != p_Var7->cMissionName[0]) {
LAB_00570caf:
        iVar4 = (1 - (uint)bVar11) - (uint)(bVar11 != 0);
        goto LAB_00570cb4;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar11 = bVar1 < (byte)p_Var7->cMissionName[1];
      if (bVar1 != p_Var7->cMissionName[1]) goto LAB_00570caf;
      pbVar3 = pbVar3 + 2;
      p_Var7 = (_TrainingMission *)(p_Var7->cMissionName + 2);
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_00570cb4:
    if (iVar4 == 0) {
      return iVar2;
    }
    p_Var10 = p_Var10 + 1;
    iVar2 = iVar2 + 1;
    if (0x63b3ef < (int)p_Var10) {
      return -1;
    }
  } while( true );
}
