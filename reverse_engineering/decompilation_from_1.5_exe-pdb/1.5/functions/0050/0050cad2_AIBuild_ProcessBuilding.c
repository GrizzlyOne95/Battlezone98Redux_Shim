/*
 * Entry: 0050cad2
 * Name: AIBuild_ProcessBuilding
 * Namespace: Global
 * Signature: void AIBuild_ProcessBuilding(tag_team * param_1, tagBUILDING * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_ProcessBuilding(tag_team *param_1,tagBUILDING *param_2)

{
  tagBUILDING *ptVar1;
  uchar uVar2;
  int iVar3;
  tagUNITTYPE *ptVar4;
  tagBUILDINGTYPE *ptVar5;
  ushort uVar6;
  int local_8;
  
  ptVar1 = param_2;
  iVar3 = AIBuild_BuildListWhatToMakeWith
                    (param_1,(uint)param_2->buildingtype->prereqtype,0,(int *)&param_2,&local_8,
                     &local_8);
  uVar6 = (ushort)iVar3;
  if (uVar6 != 0) {
    uVar2 = PREREQ_IsUnit(uVar6);
    if (uVar2 == '\0') {
      ptVar5 = PREREQ_BuildingTypePtr(uVar6);
      Debug_Assert((int)ptVar5,0x773,".\\Schedule\\Aibuild.cpp","build_type_ptr");
      (ptVar1->ai).account = (int)param_2;
      (ptVar1->ai).refundable = ptVar5->cost;
      Build_ConstructBuild(ptVar1,ptVar5);
    }
    else {
      ptVar4 = PREREQ_UnitTypePtr(uVar6);
      Debug_Assert((int)ptVar4,0x76a,".\\Schedule\\Aibuild.cpp","unit_type_ptr");
      (ptVar1->ai).account = (int)param_2;
      (ptVar1->ai).refundable = (uint)ptVar4->buildcost;
      Build_ConstructUnit(ptVar1,ptVar4);
    }
  }
  return;
}
