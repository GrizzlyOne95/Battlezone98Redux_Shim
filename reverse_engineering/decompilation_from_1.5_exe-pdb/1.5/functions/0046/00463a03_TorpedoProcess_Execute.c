/*
 * Entry: 00463a03
 * Name: TorpedoProcess::Execute
 * Namespace: TorpedoProcess
 * Signature: void Execute(TorpedoProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TorpedoProcess::Execute(TorpedoProcess *this)

{
  int *piVar1;
  int iVar2;
  float fVar3;
  VECTOR_3D VVar4;
  TorpedoProcess *pTVar5;
  bool bVar6;
  float *pfVar7;
  GameObject *pGVar8;
  int iVar9;
  VECTOR_3D *pVVar10;
  float fVar11;
  double dVar12;
  Range_Search_Results local_58;
  float local_2c;
  float fStack_28;
  float local_24;
  float local_20;
  float fStack_1c;
  float local_18;
  GameObject *local_14;
  int *local_10;
  float *local_c;
  TorpedoProcess *local_8;
  
  local_8 = this;
  pfVar7 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0xc + 0x20) + 0xc))();
  local_20 = *pfVar7;
  fStack_1c = pfVar7[1];
  local_18 = pfVar7[2];
  if ((((100.0 < *(float *)(*(int *)&this->field_0xc + 0x110)) || (local_20 - TerMinX < 20.0)) ||
      (TerMaxX - local_20 < 20.0)) || ((local_18 - TerMinZ < 20.0 || (TerMaxZ - local_18 < 20.0))))
  {
    iVar9 = (**(code **)(*(int *)(*(int *)&this->field_0xc + 0x20) + 0x30))();
    *(uint *)(iVar9 + 0x14) = *(uint *)(iVar9 + 0x14) | 0x200;
  }
  else {
    local_10 = *(int **)&this->field_0xc;
    iVar9 = local_10[0x88];
    iVar2 = local_10[0x3a];
    local_c = (float *)(iVar9 + 0xc4);
    local_14 = GameObject::GetObj(local_10[0x85]);
    if (local_14 == (GameObject *)0x0) {
      local_14 = (GameObject *)0x0;
      *(float *)(iVar9 + 0xc4) = 0.0;
      local_c = (float *)(dist * dist);
      Range::Search(collision_range_search,(double)local_20,(double)local_18,(double)dist,&local_58)
      ;
      while (bVar6 = Range_Search_Results::Get_Next_Object(&local_58,&local_10), bVar6) {
        pGVar8 = GameObjectHandle::GetObj(*local_10);
        if ((pGVar8 != (GameObject *)0x0) && ((pGVar8->obj->flags & 1) == 0)) {
          piVar1 = &pGVar8->_padding_;
          iVar9 = (**(code **)(*piVar1 + 4))();
          if (iVar9 != 0) {
            iVar9 = (**(code **)(*piVar1 + 4))();
            pTVar5 = local_8;
            bVar6 = GameObject::FriendP(*(GameObject **)&local_8->field_0xc,iVar9);
            if ((!bVar6) &&
               (bVar6 = GameObject::FriendP(*(GameObject **)&pTVar5->field_0xc,pGVar8->perceivedTeam
                                           ), !bVar6)) {
              pVVar10 = (VECTOR_3D *)(**(code **)(*piVar1 + 0xc))();
              VVar4.y = fStack_1c;
              VVar4.x = local_20;
              VVar4.z = local_18;
              fVar11 = Dist3D_Squared(*pVVar10,VVar4);
              if (fVar11 < (float)local_c) {
                local_14 = pGVar8;
                local_c = (float *)fVar11;
              }
            }
          }
        }
      }
      GameObject::SetTarget(*(GameObject **)&local_8->field_0xc,local_14);
    }
    else {
      pfVar7 = (float *)(**(code **)(*(int *)(*(int *)&local_8->field_0xc + 0x20) + 0xc))();
      local_2c = *pfVar7;
      fStack_28 = pfVar7[1];
      local_24 = pfVar7[2];
      pfVar7 = (float *)(**(code **)(local_14->_padding_ + 0xc))();
      local_20 = *pfVar7;
      fStack_1c = pfVar7[1];
      local_18 = pfVar7[2];
      fVar11 = local_20 - local_2c;
      fVar3 = local_18 - local_24;
      local_14 = (GameObject *)
                 (fVar11 * *(float *)(iVar2 + 0x20) + *(float *)(iVar2 + 0x28) * fVar3);
      dVar12 = rsqrt((double)(fVar3 * fVar3 + fVar11 * fVar11 + 0.0001));
      fVar11 = Clamp((float)dVar12 * (float)local_14 * -5.0 - (float)local_10[0x4c],-1.0,1.0);
      *local_c = fVar11;
    }
  }
  return;
}
