/*
 * Entry: 00485a1c
 * Name: ConstructionRig::GetCommand
 * Namespace: ConstructionRig
 * Signature: AiCommand GetCommand(ConstructionRig * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Type propagation algorithm not settling */

AiCommand __thiscall ConstructionRig::GetCommand(ConstructionRig *this,VECTOR_3D *param_1)

{
  int *piVar1;
  ulong uVar2;
  PowerPlant *pPVar3;
  VECTOR_3D VVar4;
  bool bVar5;
  int iVar6;
  BBOX *pBVar7;
  PowerPlant **ppPVar8;
  VECTOR_3D *pVVar9;
  BBOX *pBVar10;
  float fVar11;
  BBOX local_3c;
  float local_24;
  float local_20;
  float local_1c;
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> local_18;
  _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> local_10;
  ConstructionRig *local_8;
  
  local_8 = this;
  iVar6 = GameObject::GetActiveMode((GameObject *)this);
  if ((this->_padding_ == 0) && (iVar6 != 0)) {
    if (iVar6 == 1) {
      return CMD_GO;
    }
    if (0x18 < iVar6) {
      SetConstructionMatrix
                (this,param_1,(VECTOR_3D *)&(GameObject::userObject->obj->transform).front_x);
      pBVar7 = GameObjectClass::GetBoundingBox(this->dropClass);
      pBVar10 = &local_3c;
      for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
        (pBVar10->min).x = (pBVar7->min).x;
        pBVar7 = (BBOX *)&(pBVar7->min).y;
        pBVar10 = (BBOX *)&(pBVar10->min).y;
      }
      local_3c.min.x = local_3c.min.x - 10.0;
      local_3c.min.z = local_3c.min.z - 10.0;
      local_3c.max.x = local_3c.max.x + 10.0;
      local_3c.max.z = local_3c.max.z + 10.0;
      ConstructionDisplay::SetBox(&constructionDisplay,&local_3c,&this->dropMat);
      bVar5 = CanBuildHere(&local_3c,&this->dropMat);
      if (bVar5) {
        uVar2 = this->dropClass->sig;
        if (((uVar2 != 0x434f4d4d) && (uVar2 != 0x54555252)) && (uVar2 != 0x53484c44)) {
LAB_00485be5:
          bVar5 = GameObject::FriendP((GameObject *)this,GameObject::userObject);
          if (bVar5) {
            constructionDisplay.index = constructionDisplay.rectGreen;
          }
          return CMD_DROPOFF;
        }
        std::_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::
        _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>
                  (&local_18,PowerPlant::powerPlantList._Myfirst,
                   (_Container_base_aux *)&PowerPlant::powerPlantList);
        local_10._padding_ = local_18._padding_;
        local_10._Myptr = local_18._Myptr;
        while( true ) {
          std::_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::
          _Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>
                    (&local_18,PowerPlant::powerPlantList._Mylast,
                     (_Container_base_aux *)&PowerPlant::powerPlantList);
          bVar5 = std::_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::
                  operator==(&local_10,&local_18);
          if (bVar5) break;
          ppPVar8 = std::_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::
                    operator*(&local_10);
          pPVar3 = *ppPVar8;
          bVar5 = GameObject::FriendP((GameObject *)this,(GameObject *)pPVar3);
          if (bVar5) {
            local_24 = (float)(this->dropMat).posit_x;
            piVar1 = &pPVar3->_padding_;
            local_20 = (float)(this->dropMat).posit_y;
            local_1c = (float)(this->dropMat).posit_z;
            pVVar9 = (VECTOR_3D *)(**(code **)(*piVar1 + 0xc))();
            VVar4.y = local_20;
            VVar4.x = local_24;
            VVar4.z = local_1c;
            fVar11 = Dist3D_Squared(VVar4,*pVVar9);
            iVar6 = (**(code **)*piVar1)();
            this = local_8;
            if (fVar11 < *(float *)(iVar6 + 0x160) * *(float *)(iVar6 + 0x160)) goto LAB_00485be5;
          }
          std::_Vector_const_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>::operator++
                    (&local_10);
        }
        bVar5 = GameObject::FriendP((GameObject *)this,GameObject::userObject);
        iVar6 = constructionDisplay.rectYellow;
      }
      else {
        bVar5 = GameObject::FriendP((GameObject *)this,GameObject::userObject);
        iVar6 = constructionDisplay.rectRed;
      }
      if (bVar5) {
        constructionDisplay.index = iVar6;
      }
      return CMD_NO_DROPOFF;
    }
  }
  return CMD_NONE;
}
