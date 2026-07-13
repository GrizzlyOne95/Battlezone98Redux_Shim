/*
 * Entry: 00518711
 * Name: Obj2Build
 * Namespace: Global
 * Signature: tagBUILDING * Obj2Build(GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagBUILDING * __cdecl Obj2Build(GameObject *param_1)

{
  float fVar1;
  bool bVar2;
  Attachment **ppAVar3;
  BuildAttachment *pBVar4;
  float *pfVar5;
  int iVar6;
  GameObject *pGVar7;
  int iVar8;
  float fVar9;
  
  ppAVar3 = std::vector<Attachment_*,std::allocator<Attachment_*>_>::operator[]
                      ((vector<Attachment_*,std::allocator<Attachment_*>_> *)&param_1->_padding_,
                       attachIndex);
  pBVar4 = (BuildAttachment *)*ppAVar3;
  if (pBVar4 == (BuildAttachment *)0x0) {
    pBVar4 = operator_new(0x3c);
    if (pBVar4 == (BuildAttachment *)0x0) {
      pBVar4 = (BuildAttachment *)0x0;
    }
    else {
      pBVar4 = BuildAttachment::BuildAttachment(pBVar4,param_1);
    }
    ppAVar3 = std::vector<Attachment_*,std::allocator<Attachment_*>_>::operator[]
                        ((vector<Attachment_*,std::allocator<Attachment_*>_> *)&param_1->_padding_,
                         attachIndex);
    *ppAVar3 = (Attachment *)pBVar4;
  }
  pfVar5 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  fVar1 = pfVar5[2];
  iVar6 = PosX2POS((double)*pfVar5);
  (pBVar4->build).tilex = iVar6;
  iVar6 = PosZ2POS((double)fVar1);
  (pBVar4->build).tiley = iVar6;
  (pBVar4->build).perceived_team = param_1->perceivedTeam;
  iVar6 = (**(code **)param_1->_padding_)();
  bVar2 = BuildingVehicle(*(ulong *)(iVar6 + 0x20));
  if (bVar2) {
    bVar2 = Producer::CanBuild((Producer *)param_1);
    if (bVar2) {
      bVar2 = Producer::IsBusy((Producer *)param_1);
      (pBVar4->build).order = (uint)bVar2 * 2 + 1;
    }
    else {
      (pBVar4->build).order = 0xb;
    }
  }
  else {
    (pBVar4->build).order = 0;
  }
  fVar1 = param_1->enemyShot;
  fVar9 = Get_Time();
  if (fVar9 - fVar1 < 2.0) {
    pGVar7 = GameObjectHandle::GetObj(param_1->who_shot_JR);
    if ((pGVar7 != (GameObject *)0x0) && (pGVar7->aiProcess != (AiProcess *)0x0)) {
      pfVar5 = (float *)(**(code **)(pGVar7->_padding_ + 0xc))();
      fVar1 = *pfVar5;
      iVar6 = PosZ2POS((double)pfVar5[2]);
      iVar8 = PosX2POS((double)fVar1);
      AI_Team_Trigger_Rapid_Base_Defense
                ((pBVar4->build).team,(pBVar4->build).tilex,(pBVar4->build).tiley,1,iVar8,iVar6,
                 pGVar7);
    }
  }
  return &pBVar4->build;
}
