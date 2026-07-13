/*
 * Entry: 0051794b
 * Name: Build_ConstructUnit
 * Namespace: Global
 * Signature: int Build_ConstructUnit(tagBUILDING * param_1, tagUNITTYPE * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Build_ConstructUnit(tagBUILDING *param_1,tagUNITTYPE *param_2)

{
  Producer *this;
  GameObjectClass *pGVar1;
  bool bVar2;
  char cVar3;
  uint uVar4;
  ObjectClassInfo **ppOVar5;
  long lVar6;
  
  this = (Producer *)param_1->id;
  param_1->order = 3;
  cVar3 = (**(code **)(this->_padding_ + 100))();
  if (cVar3 == '\0') {
    AI_SpentCreditRefund(param_1->team,param_1,(tagUNIT *)0x0);
    AIBuild_ConstructionEnd(param_1->team,(uint)(param_2->prereq).prereqtype);
    param_1->order = 1;
    uVar4 = 0;
  }
  else {
    ppOVar5 = std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator[]
                        (&vehicleClassList,param_2->unittypeid);
    pGVar1 = (*ppOVar5)->objClass;
    lVar6 = Team::GetScrap((Team *)this->_padding_);
    bVar2 = pGVar1->scrapCost <= lVar6;
    if (bVar2) {
      tlog_wbp("\nBuild_ConstructUnit %s");
      Producer::StartBuild(this,pGVar1);
      Team_ChangeCredits(param_1->team,-(uint)param_2->buildcost);
      AI_SpentCreditRemove(param_1->team,param_1,(uint)param_2->buildcost);
      tlog_wbp("\nteam credits: %d");
    }
    else {
      AI_SpentCreditRefund(param_1->team,param_1,(tagUNIT *)0x0);
      AIBuild_ConstructionEnd(param_1->team,(uint)(param_2->prereq).prereqtype);
      param_1->order = 1;
    }
    uVar4 = (uint)bVar2;
  }
  return uVar4;
}
