/*
 * Entry: 0050878a
 * Name: AI_Match_Get_Weapon_Details
 * Namespace: Global
 * Signature: void AI_Match_Get_Weapon_Details(tagUNITTYPE * param_1, int * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Match_Get_Weapon_Details(tagUNITTYPE *param_1,int *param_2,int *param_3)

{
  int *piVar1;
  tagUNITTYPE *ptVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int local_8;
  
  ptVar2 = param_1;
  *param_2 = 0;
  *param_3 = 1;
  Debug_Assert((uint)(0 < (param_1->partinfo).nrparts),0x52,".\\Schedule\\AI_Match.cpp",
               "unit_type->partinfo.nrparts > 0");
  local_8 = 0;
  if (0 < (param_1->partinfo).nrparts) {
    param_1 = (tagUNITTYPE *)&param_1->partinfo;
    do {
      param_1 = (tagUNITTYPE *)&param_1->partinfo;
      piVar5 = (int *)param_1->unittypeid;
      Debug_Assert((int)piVar5,0x5a,".\\Schedule\\AI_Match.cpp","part_type");
      Debug_Assert((uint)(*piVar5 < 5),0x5d,".\\Schedule\\AI_Match.cpp","part_type->nrweapons < 5");
      Debug_Assert((uint)(-1 < *piVar5),0x5e,".\\Schedule\\AI_Match.cpp","part_type->nrweapons >= 0"
                  );
      iVar3 = *piVar5;
      iVar4 = 0;
      if (0 < iVar3) {
        do {
          piVar5 = piVar5 + 1;
          piVar1 = (int *)*piVar5;
          if (piVar1 != (int *)0x0) {
            iVar3 = *piVar1;
            if (iVar3 < 0) {
              iVar3 = -iVar3;
            }
            *param_2 = iVar3;
            *param_3 = piVar1[1];
            return;
          }
          iVar4 = iVar4 + 1;
        } while (iVar4 < iVar3);
      }
      local_8 = local_8 + 1;
    } while (local_8 < (ptVar2->partinfo).nrparts);
  }
  return;
}
