/*
 * Entry: 004acfb0
 * Name: RepairDepot::Simulate
 * Namespace: RepairDepot
 * Signature: void Simulate(RepairDepot * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RepairDepot::Simulate(RepairDepot *this,float param_1)

{
  float *pfVar1;
  VECTOR_3D VVar2;
  bool bVar3;
  long lVar4;
  GameObject *pGVar5;
  VECTOR_3D *pVVar6;
  _OBJ76 *p_Var7;
  int *piVar8;
  float fVar9;
  GAS_CTRL *pGVar10;
  Range_Search_Results local_40;
  GameObject *local_14;
  GameObject *local_10;
  int *local_c;
  float local_8;
  
  if ((-1 < this->animHandle) &&
     ((lVar4 = AnimObj_Status(this->animHandle,(tagANIMOBJ_ACTIVE_LIST **)&local_10), lVar4 != 0 ||
      (local_10->_padding_ != 1)))) {
    AnimObj_Stop(this->animHandle);
    this->animHandle = -1;
    fVar9 = get_obj_radius((_OBJ76 *)this->_padding_,*(VECTOR_3D *)(this->_padding_ + 8));
    *(float *)(this->_padding_ + 0x14) = fVar9;
    GameObject::UpdatePosition((GameObject *)this);
  }
  fVar9 = this->repairTimer + param_1;
  pfVar1 = (float *)(this->_padding_ + 0x164);
  this->repairTimer = fVar9;
  if (*pfVar1 < fVar9) {
    this->repairTimer = fVar9 - *pfVar1;
    local_8 = *(float *)(this->_padding_ + 0x160);
    Range::Search(collision_range_search,(double)(float)this->_padding_,
                  (double)(float)this->_padding_,(double)local_8,&local_40);
    local_10 = (GameObject *)0x0;
    local_8 = local_8 * local_8;
    bVar3 = Range_Search_Results::Get_Next_Object(&local_40,&local_c);
    if (bVar3) {
      do {
        pGVar5 = GameObject::GetObj(*local_c);
        local_14 = pGVar5;
        if (((pGVar5 != (GameObject *)0x0) &&
            (bVar3 = GameObject::EnemyP((GameObject *)this,pGVar5), !bVar3)) &&
           (pGVar5->maxHealth < pGVar5->curHealth == (pGVar5->maxHealth == pGVar5->curHealth))) {
          pVVar6 = (VECTOR_3D *)(**(code **)(pGVar5->_padding_ + 0xc))();
          VVar2.x = (float)this->_padding_;
          VVar2.y = (float)this->_padding_;
          VVar2.z = (float)this->_padding_;
          fVar9 = Dist3D_Squared(*pVVar6,VVar2);
          if (fVar9 < local_8) {
            local_10 = local_14;
            local_8 = fVar9;
          }
        }
        bVar3 = Range_Search_Results::Get_Next_Object(&local_40,&local_c);
      } while (bVar3);
      if (local_10 != (GameObject *)0x0) {
        pGVar10 = *(GAS_CTRL **)(this->_padding_ + 0x168);
        piVar8 = &local_10->_padding_;
        (**(code **)(*piVar8 + 0x28))();
        p_Var7 = (_OBJ76 *)(**(code **)(*piVar8 + 0x30))(0);
        DoAudioNew((char *)(this->_padding_ + 0x16c),p_Var7,pGVar10);
      }
    }
  }
  Building::Simulate((Building *)this,param_1);
  return;
}
