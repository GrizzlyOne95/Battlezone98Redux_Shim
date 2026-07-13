/*
 * Entry: 0050cbca
 * Name: AIBuild_ProcessFacilityConstruction
 * Namespace: Global
 * Signature: void AIBuild_ProcessFacilityConstruction(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_ProcessFacilityConstruction(tag_team *param_1)

{
  tagUNIT *ptVar1;
  int iVar2;
  int iVar3;
  tagBUILDINGTYPE *ptVar4;
  int iVar5;
  int iVar6;
  int local_10;
  int local_c;
  int local_8;
  
  while( true ) {
    ptVar1 = AIBuild_UnassignedCCGet(param_1);
    if (ptVar1 == (tagUNIT *)0x0) {
      return;
    }
    iVar2 = AIBuild_BuildListWhatToMakeWith
                      (param_1,(uint)(ptVar1->type->prereq).prereqtype,0,&local_10,&local_c,&local_8
                      );
    if (iVar2 == 0) break;
    iVar5 = local_c;
    iVar6 = local_8;
    iVar3 = PREREQ_MapPrereqIdToBuildingId(iVar2);
    Units_SOrderConstruct(ptVar1,iVar3,iVar5,iVar6);
    ptVar4 = PREREQ_BuildingTypePtr((ushort)iVar2);
    iVar5 = AIBuild_ReservedAreaAdd
                      (param_1->team_ID,local_c + -1,local_8 + -1,
                       (*(uint *)&ptVar4->field_0x24 >> 0x12 & 0xf) + 2,
                       (*(uint *)&ptVar4->field_0x24 >> 0x16 & 0xf) + 2);
    (ptVar1->ai).cc_reserved_area = iVar5;
    AIBuild_UnassignedCCRemove(param_1,ptVar1);
    iVar5 = AIBuild_CostOfObject(iVar2);
    (ptVar1->ai).cc_construct_cost = iVar5;
    (ptVar1->ai).cc_construct_type = iVar2;
    (ptVar1->ai).cc_account = local_10;
    (param_1->aibuild).build_list.update_required = 1;
  }
  return;
}
