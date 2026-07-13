/*
 * Entry: 00482670
 * Name: Barracks::Simulate
 * Namespace: Barracks
 * Signature: void Simulate(Barracks * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Barracks::Simulate(Barracks *this,float param_1)

{
  int *piVar1;
  bool bVar2;
  float *pfVar3;
  GameObject *pGVar4;
  _OBJ76 *p_Var5;
  int iVar6;
  int iVar7;
  long lVar8;
  float fVar9;
  Range_Search_Results local_5c;
  float local_30;
  float fStack_2c;
  float local_28;
  float local_24;
  float fStack_20;
  float local_1c;
  _OBJ76 *local_18;
  int *local_14;
  int local_10;
  int local_c;
  Barracks *local_8;
  
  local_8 = this;
  bVar2 = DistributedObject::IsRemote((DistributedObject *)&this->_padding_);
  if ((!bVar2) && (fVar9 = Get_TimeLocal(), this->nextEmptyCheck < fVar9)) {
    fVar9 = Get_TimeLocal();
    this->nextEmptyCheck = fVar9 + 5.0;
    pfVar3 = (float *)(**(code **)(this->_padding_ + 0xc))();
    local_24 = *pfVar3;
    fStack_20 = pfVar3[1];
    local_1c = pfVar3[2];
    Range::Search(collision_range_search,(double)local_24,(double)local_1c,100.0,&local_5c);
    local_c = 0;
    local_10 = 0;
    bVar2 = Range_Search_Results::Get_Next_Object(&local_5c,&local_14);
    if (bVar2) {
      do {
        pGVar4 = GameObjectHandle::GetObj(*local_14);
        if (pGVar4 != (GameObject *)0x0) {
          piVar1 = &pGVar4->_padding_;
          p_Var5 = (_OBJ76 *)(**(code **)(*piVar1 + 0x30))();
          local_18 = p_Var5;
          iVar6 = IsCraft(p_Var5);
          if ((iVar6 != 0) || (p_Var5->class_id == CLASS_ID_PERSON)) {
            if (p_Var5->class_id == CLASS_ID_PERSON) {
              iVar6 = (**(code **)(*piVar1 + 4))();
              iVar7 = (**(code **)(local_8->_padding_ + 4))();
              if (iVar6 != iVar7) goto LAB_004827d5;
            }
            pfVar3 = (float *)(**(code **)(*piVar1 + 0xc))();
            local_30 = *pfVar3;
            fStack_2c = pfVar3[1];
            local_28 = pfVar3[2];
            if ((local_28 - local_1c) * (local_28 - local_1c) +
                (local_30 - local_24) * (local_30 - local_24) <= 10000.0) {
              if ((pGVar4->aiProcess == (AiProcess *)0x0) &&
                 (pGVar4->curPilot == (GameObjectClass *)0x0)) {
                bVar2 = TeamHasFreeSlot((Team *)local_8->_padding_,pGVar4);
                if (bVar2) {
                  local_10 = local_10 + 1;
                }
              }
              else if (local_18->class_id == CLASS_ID_PERSON) {
                local_c = local_c + 1;
              }
            }
          }
        }
LAB_004827d5:
        bVar2 = Range_Search_Results::Get_Next_Object(&local_5c,&local_14);
      } while (bVar2);
      this = local_8;
      if ((local_c < local_10) &&
         (lVar8 = Team::GetPilot((Team *)local_8->_padding_), this = local_8, 0 < lVar8)) {
        BuildPilot(local_8);
        this = local_8;
      }
    }
  }
  Building::Simulate((Building *)this,param_1);
  return;
}
