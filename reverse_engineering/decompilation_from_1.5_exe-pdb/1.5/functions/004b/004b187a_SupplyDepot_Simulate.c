/*
 * Entry: 004b187a
 * Name: SupplyDepot::Simulate
 * Namespace: SupplyDepot
 * Signature: void Simulate(SupplyDepot * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SupplyDepot::Simulate(SupplyDepot *this,float param_1)

{
  float *pfVar1;
  VECTOR_3D VVar2;
  bool bVar3;
  long lVar4;
  GameObject *pGVar5;
  VECTOR_3D *pVVar6;
  _OBJ76 *p_Var7;
  float fVar8;
  GAS_CTRL *pGVar9;
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
    fVar8 = get_obj_radius((_OBJ76 *)this->_padding_,*(VECTOR_3D *)(this->_padding_ + 8));
    *(float *)(this->_padding_ + 0x14) = fVar8;
    GameObject::UpdatePosition((GameObject *)this);
  }
  fVar8 = this->supplyTimer + param_1;
  pfVar1 = (float *)(this->_padding_ + 0x164);
  this->supplyTimer = fVar8;
  if (*pfVar1 < fVar8) {
    this->supplyTimer = fVar8 - *pfVar1;
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
           ((int)(pGVar5->curAmmo ^ 0x33333333U) < (int)(pGVar5->maxAmmo ^ 0x33333333U))) {
          pVVar6 = (VECTOR_3D *)(**(code **)(pGVar5->_padding_ + 0xc))();
          VVar2.x = (float)this->_padding_;
          VVar2.y = (float)this->_padding_;
          VVar2.z = (float)this->_padding_;
          fVar8 = Dist3D_Squared(*pVVar6,VVar2);
          if (fVar8 < local_8) {
            local_10 = local_14;
            local_8 = fVar8;
          }
        }
        bVar3 = Range_Search_Results::Get_Next_Object(&local_40,&local_c);
        pGVar5 = local_10;
      } while (bVar3);
      if (local_10 != (GameObject *)0x0) {
        pGVar9 = *(GAS_CTRL **)(this->_padding_ + 0x168);
        (**(code **)(local_10->_padding_ + 0x18))();
        p_Var7 = (_OBJ76 *)(**(code **)(pGVar5->_padding_ + 0x30))(0);
        DoAudioNew((char *)(this->_padding_ + 0x16c),p_Var7,pGVar9);
      }
    }
  }
  Building::Simulate((Building *)this,param_1);
  return;
}
