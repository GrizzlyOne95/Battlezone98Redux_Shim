/*
 * Entry: 0050c92c
 * Name: AIBuild_BuildListWhatToMakeWith
 * Namespace: Global
 * Signature: int AIBuild_BuildListWhatToMakeWith(tag_team * param_1, int param_2, int param_3, int * param_4, int * param_5, int * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
AIBuild_BuildListWhatToMakeWith
          (tag_team *param_1,int param_2,int param_3,int *param_4,int *param_5,int *param_6)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  tag_team *ptVar4;
  byte bVar5;
  uchar uVar6;
  int *piVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int local_10;
  int local_c;
  
  ptVar4 = param_1;
  local_10 = 0;
  local_c = (param_1->aibuild).build_list.nodes;
  if (local_c != 0) {
    param_1 = (tag_team *)Random_Sync(local_c);
    if ((local_c <= (int)param_1) || ((int)param_1 < 0)) {
      printf("Node %d Count %d\n",param_1,local_c);
    }
    Debug_Assert((uint)(-1 < (int)param_1),0x50a,".\\Schedule\\Aibuild.cpp","node >= 0");
    Debug_Assert((uint)((int)param_1 < local_c),0x50b,".\\Schedule\\Aibuild.cpp","node < count");
    do {
      if (local_10 != 0) {
        return local_10;
      }
      piVar7 = (ptVar4->aibuild).credit + (int)&param_1->my_squads * 5 + -0x20;
      if (0 < *piVar7) {
        iVar2 = (ptVar4->aibuild).build_list.node[(int)param_1].prereq_type;
        if (param_3 == 0) {
          bVar5 = PREREQ_CanThisMakeThat((ushort)param_2,(ushort)iVar2,(char)ptVar4->team_ID);
          uVar8 = (uint)bVar5;
        }
        else {
          uVar8 = AIBuild_CanThisUpgradeToThat(param_2,iVar2);
        }
        if (uVar8 != 0) {
          iVar9 = AIBuild_CostOfObject(iVar2);
          iVar3 = (ptVar4->aibuild).build_list.node[(int)param_1].account;
          if ((iVar9 <= (ptVar4->aibuild).credit[iVar3]) &&
             (((param_3 != 0 || (uVar6 = PREREQ_IsBuilding((ushort)iVar2), uVar6 == '\0')) ||
              (iVar10 = AIBuild_FindFacilityLocation(ptVar4,iVar2,param_5,param_6), iVar10 != 0))))
          {
            AIBuild_ConstructionBegin(ptVar4->team_ID,iVar2);
            AI_SpentCreditSpend(ptVar4->team_ID,iVar3,iVar9);
            *param_4 = iVar3;
            piVar1 = &(ptVar4->aibuild).prespent_credits;
            *piVar1 = *piVar1 + iVar9;
            *piVar7 = *piVar7 + -1;
            iVar3 = (ptVar4->aibuild).build_list.node[(int)param_1].build_type;
            if (iVar3 == 1) {
              piVar7 = (ptVar4->aibuild).build_list.node[(int)param_1].field4_0x10.
                       number_left_to_build;
              *piVar7 = *piVar7 + -1;
            }
            else if (iVar3 == 2) {
              piVar7 = (ptVar4->aibuild).build_list.node[(int)param_1].field4_0x10.
                       number_left_to_build;
              *piVar7 = *piVar7 + 1;
            }
            (ptVar4->aibuild).build_list.update_required = 1;
            local_10 = iVar2;
          }
        }
      }
      local_c = local_c + -1;
      param_1 = (tag_team *)((int)&param_1->team_ID + 1);
      if (param_1 == (tag_team *)(ptVar4->aibuild).build_list.nodes) {
        param_1 = (tag_team *)0x0;
      }
    } while (local_c != 0);
  }
  return local_10;
}
