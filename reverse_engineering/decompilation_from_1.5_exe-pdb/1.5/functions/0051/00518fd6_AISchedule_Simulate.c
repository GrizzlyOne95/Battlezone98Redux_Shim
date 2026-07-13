/*
 * Entry: 00518fd6
 * Name: AISchedule_Simulate
 * Namespace: Global
 * Signature: void AISchedule_Simulate(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AISchedule_Simulate(void)

{
  Producer *this;
  bool bVar1;
  char cVar2;
  int iVar3;
  tagUNIT *ptVar4;
  tagBUILDING *ptVar5;
  int *piVar6;
  float fVar7;
  tagITERATOR local_54;
  
  fVar7 = TimeStep();
  accumulator = fVar7 + accumulator;
  if (0.016666 <= accumulator) {
    accumulator = 0.0;
    iVar3 = Net_IsNetGame();
    if ((iVar3 == 0) || (iVar3 = Net_IsHosting(), iVar3 != 0)) {
      local_54.junk[2] = -1;
      local_54.junk[0] = 0;
      local_54.junk[1] = 0;
      ptVar4 = Iterate_UnitNext(&local_54);
      while (ptVar4 != (tagUNIT *)0x0) {
        this = (Producer *)ptVar4->id;
        if (ptVar4->special == '\0') {
LAB_0051905f:
          if (0 < this->_padding_) {
            ptVar4->special = '\x01';
            AI_UnitRemove(ptVar4);
          }
        }
        else if (this->_padding_ == 0) {
          ptVar4->special = '\0';
          AI_UnitAppeared(ptVar4);
        }
        else if (ptVar4->special == '\0') goto LAB_0051905f;
        iVar3 = (**(code **)this->_padding_)();
        if ((*(int *)(iVar3 + 0x20) == 0x434e5354) && ((ptVar4->ai).cc_construct_type != 0)) {
          bVar1 = Producer::IsBusy(this);
          if (bVar1) {
            cVar2 = (**(code **)(this->_padding_ + 100))();
            if (cVar2 != '\0') {
              (ptVar4->ai).cc_constructing = 1;
            }
          }
          else {
            if ((ptVar4->ai).cc_constructing == 0) {
              AI_BuildingStalled(ptVar4);
            }
            else {
              AIBuild_UnassignedCCAdd(AI_map->team[ptVar4->team],ptVar4);
            }
            (ptVar4->ai).cc_construct_type = 0;
            (ptVar4->ai).cc_construct_cost = 0;
            (ptVar4->ai).cc_constructing = 0;
          }
        }
        ptVar4 = Iterate_UnitNext(&local_54);
      }
      local_54.junk[2] = -1;
      local_54.junk[0] = 0;
      local_54.junk[1] = 1;
      do {
        ptVar5 = Iterate_BuildNext(&local_54);
      } while (ptVar5 != (tagBUILDING *)0x0);
      iVar3 = 4;
      do {
        piVar6 = (int *)((int)AI_map->team + iVar3);
        if (*piVar6 != 0) {
          AIBuild_LocateBase((tag_team *)*piVar6);
        }
        iVar3 = iVar3 + 4;
      } while (iVar3 < 0x40);
      AI_Process();
      unitcycles = unitcycles + 1;
    }
  }
  return;
}
