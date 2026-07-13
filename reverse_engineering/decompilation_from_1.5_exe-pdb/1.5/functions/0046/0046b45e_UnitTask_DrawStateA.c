/*
 * Entry: 0046b45e
 * Name: UnitTask::DrawStateA
 * Namespace: UnitTask
 * Signature: void DrawStateA(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall UnitTask::DrawStateA(UnitTask *this)

{
  double dVar1;
  Craft *pCVar2;
  _OBJ76 *p_Var3;
  VECTOR_2D *pVVar4;
  VECTOR_3D VVar5;
  VECTOR_3D VVar6;
  VECTOR_3D VVar7;
  VECTOR_3D VVar8;
  WorldInterface *pWVar9;
  int iVar10;
  VECTOR_3D *pVVar11;
  float *pfVar12;
  VECTOR_3D *pVVar13;
  GameObject *pGVar14;
  float *pfVar15;
  MAT_3D *pMVar16;
  AiPath *pAVar17;
  long lVar18;
  float fVar19;
  VECTOR_3D local_100;
  VECTOR_3D local_f4;
  VECTOR_3D local_e8;
  VECTOR_3D local_dc;
  VECTOR_3D local_d0;
  VECTOR_3D local_c4;
  VECTOR_3D local_b8;
  VECTOR_3D local_ac;
  float local_a0;
  float local_9c;
  GameObject *local_98;
  float local_94;
  WorldInterface *local_90;
  VECTOR_3D local_8c;
  VECTOR_3D local_80;
  float local_74;
  float local_70;
  float local_6c;
  VECTOR_3D local_68;
  float local_5c;
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&local_80.y;
  sprintf(local_58," UnitTask: %s",stateText[this->curState]);
  DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  iVar10 = (**(code **)this->me->_padding_)();
  if (*(int *)(iVar10 + 0x20) == 0x54555252) {
    fVar19 = SQRT(this->rangeSq);
    lVar18 = DisplayInterface::colorWhite;
    pVVar11 = (VECTOR_3D *)(**(code **)(this->me->_padding_ + 0xc))();
    WorldCircle(pVVar11,fVar19,lVar18);
  }
  local_90 = WorldInterface::currentDisplay;
  pfVar12 = (float *)(**(code **)(this->me->_padding_ + 0xc))();
  pWVar9 = local_90;
  local_8c.x = *pfVar12;
  local_8c.y = pfVar12[1];
  local_8c.z = pfVar12[2];
  (**(code **)(*(int *)local_90 + 0x20))(local_8c.x,local_8c.z,&local_5c,&local_98);
  pfVar12 = (float *)this->me->_padding_;
  if (pfVar12 != (float *)0x0) {
    (**(code **)(*(int *)pWVar9 + 0x20))(*pfVar12 + local_8c.x,local_8c.z,&local_94,&local_6c);
    Graphic_Circle(DisplayInterface::currentBuffer,(long)local_5c,(long)local_98,
                   (int)local_94 - (int)local_5c,0x18,DisplayInterface::colorGreen,SOLID_PIXELS);
  }
  local_8c.x = (this->gotoForce).x;
  local_8c.y = (this->gotoForce).y;
  local_8c.z = (this->gotoForce).z;
  pfVar12 = (float *)(**(code **)(this->me->_padding_ + 0xc))();
  local_74 = *pfVar12;
  local_70 = pfVar12[1];
  local_6c = pfVar12[2];
  local_a0 = local_8c.x + local_74;
  local_9c = local_8c.y + local_70;
  pVVar11 = &local_68;
  local_98 = (GameObject *)(local_8c.z + local_6c);
  lVar18 = DisplayInterface::colorYellow;
  local_68.x = local_a0;
  local_68.y = local_9c;
  local_68.z = (float)local_98;
  pVVar13 = (VECTOR_3D *)(**(code **)(this->me->_padding_ + 0xc))();
  WorldLine(pVVar13,pVVar11,lVar18);
  pCVar2 = this->me;
  iVar10 = pCVar2->_padding_;
  local_5c = (float)pCVar2->_padding_ + 10.0;
  pVVar11 = (VECTOR_3D *)(**(code **)(pCVar2->_padding_ + 0xc))();
  pVVar13 = AddMultVectors(&local_ac,*pVVar11,local_5c,*(VECTOR_3D *)(iVar10 + 0x38));
  local_80.x = pVVar13->x;
  local_80.y = pVVar13->y;
  pVVar11 = &local_80;
  local_80.z = pVVar13->z;
  lVar18 = DisplayInterface::colorRed;
  pVVar13 = (VECTOR_3D *)(**(code **)(this->me->_padding_ + 0xc))();
  WorldLine(pVVar13,pVVar11,lVar18);
  pVVar11 = (VECTOR_3D *)(**(code **)(this->me->_padding_ + 0xc))();
  pVVar13 = AddMultVectors(&local_ac,*pVVar11,local_5c,this->gotoDir);
  local_80.x = pVVar13->x;
  local_80.y = pVVar13->y;
  pVVar11 = &local_80;
  local_80.z = pVVar13->z;
  lVar18 = DisplayInterface::colorDkRed;
  pVVar13 = (VECTOR_3D *)(**(code **)(this->me->_padding_ + 0xc))();
  WorldLine(pVVar13,pVVar11,lVar18);
  iVar10 = this->curState;
  if (iVar10 == 2) {
    if (this->plan != (AiPath *)0x0) {
      pVVar4 = this->plan->points;
      local_8c.x = pVVar4[this->planPoint].x;
      local_8c.z = pVVar4[this->planPoint].z;
      local_68.y = 0.0;
      local_8c.y = 0.0;
      pVVar11 = &local_8c;
      lVar18 = DisplayInterface::colorWhite;
      local_70 = local_8c.x;
      local_6c = local_8c.z;
      local_68.x = local_8c.x;
      local_68.z = local_8c.z;
      pVVar13 = (VECTOR_3D *)(**(code **)(this->me->_padding_ + 0xc))();
      WorldLine(pVVar13,pVVar11,lVar18);
      pAVar17 = this->plan;
      local_5c = (float)(this->planPoint + 1);
      if ((int)local_5c < pAVar17->pointCount) {
        local_68.y = 0.0;
        local_80.y = 0.0;
        do {
          local_c4.x = pAVar17->points[(int)local_5c].x;
          local_c4.z = pAVar17->points[(int)local_5c].z;
          local_c4.y = local_68.y;
          local_ac.x = pAVar17->points[(int)local_5c + -1].x;
          local_ac.z = pAVar17->points[(int)local_5c + -1].z;
          local_ac.y = local_80.y;
          local_9c = local_ac.x;
          local_98 = (GameObject *)local_ac.z;
          local_80.x = local_ac.x;
          local_80.z = local_ac.z;
          local_70 = local_c4.x;
          local_6c = local_c4.z;
          local_68.x = local_c4.x;
          local_68.z = local_c4.z;
          WorldLine(&local_ac,&local_c4,DisplayInterface::colorWhite);
          pAVar17 = this->plan;
          local_5c = (float)((int)local_5c + 1);
        } while ((int)local_5c < pAVar17->pointCount);
      }
      VVar5.y = local_8c.y;
      VVar5.x = local_8c.x;
      VVar5.z = local_8c.z;
      FindPotentialField((GameObject *)this->me,this->skipObj,DEFAULT_REPULSION_CUTOFF,VVar5,
                         &local_e8,true);
    }
  }
  else if (iVar10 == 3) {
    sprintf(local_58," Stuck State: %s",stuckStateText[this->stuckState]);
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    sprintf(local_58," Next Stuck (%f)",SUB84((double)this->nextStuck,0),
            (int)((ulonglong)(double)this->nextStuck >> 0x20));
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
  }
  else if ((iVar10 == 4) &&
          (pGVar14 = GameObjectHandle::GetObj(this->himHandle), pGVar14 != (GameObject *)0x0)) {
    local_98 = pGVar14;
    pfVar12 = (float *)(**(code **)(this->me->_padding_ + 0xc))();
    local_90 = (WorldInterface *)&pGVar14->_padding_;
    pfVar15 = (float *)(**(code **)(*(int *)local_90 + 0xc))();
    local_94 = *pfVar15 - *pfVar12;
    p_Var3 = pGVar14->obj;
    local_5c = pfVar15[2] - pfVar12[2];
    pMVar16 = &p_Var3->transform;
    local_80.x = (p_Var3->transform).front_x;
    local_80.y = (p_Var3->transform).front_y;
    local_80.z = (p_Var3->transform).front_z;
    VVar7.x = (p_Var3->transform).front_x;
    VVar7.y = (p_Var3->transform).front_y;
    VVar7.z = (p_Var3->transform).front_z;
    local_74 = pMVar16->right_x;
    local_70 = (p_Var3->transform).right_y;
    local_6c = (p_Var3->transform).right_z;
    VVar6.x = pMVar16->right_x;
    VVar6.y = pMVar16->right_y;
    VVar6.z = pMVar16->right_z;
    pVVar11 = CombineVectors(&local_f4,this->followDx,VVar6,this->followDz,VVar7);
    local_80.x = pVVar11->x;
    local_80.y = pVVar11->y;
    local_80.z = pVVar11->z;
    pfVar12 = (float *)(**(code **)(*(int *)local_90 + 0xc))();
    local_74 = *pfVar12;
    local_70 = pfVar12[1];
    local_6c = pfVar12[2];
    local_8c.x = local_80.x + local_74;
    local_8c.y = local_80.y + local_70;
    pVVar11 = &local_8c;
    local_8c.z = local_80.z + local_6c;
    lVar18 = DisplayInterface::colorWhite;
    local_68.x = local_8c.x;
    local_68.y = local_8c.y;
    local_68.z = local_8c.z;
    pVVar13 = (VECTOR_3D *)(**(code **)(this->me->_padding_ + 0xc))();
    WorldLine(pVVar13,pVVar11,lVar18);
    pfVar12 = (float *)(**(code **)(this->me->_padding_ + 0xc))();
    local_80.x = local_8c.x - *pfVar12;
    local_80.y = local_8c.y - pfVar12[1];
    local_80.z = local_8c.z - pfVar12[2];
    local_68.x = local_80.x;
    local_68.y = local_80.y;
    local_68.z = local_80.z;
    pVVar11 = Vector_Unrotate(&local_100,&local_68,(MAT_3D *)(this->me->_padding_ + 0x20));
    local_68.x = pVVar11->x;
    local_68.y = pVVar11->y;
    local_68.z = pVVar11->z;
    Normalize_Vector(&local_d0,&local_68);
    dVar1 = (double)SQRT(local_94 * local_94 + local_5c * local_5c);
    sprintf(local_58," Follow Dist (%.2f)",SUB84(dVar1,0),(int)((ulonglong)dVar1 >> 0x20));
    DisplayInterface::DrawTextA(local_58,DisplayInterface::colorWhite,DisplayInterface::colorBlack);
    pWVar9 = local_90;
    p_Var3 = local_98->obj;
    pVVar11 = (VECTOR_3D *)(**(code **)(*(int *)local_90 + 0xc))();
    VVar8.x = (p_Var3->transform).front_x;
    VVar8.y = (p_Var3->transform).front_y;
    VVar8.z = (p_Var3->transform).front_z;
    pVVar13 = AddMultVectors(&local_dc,*pVVar11,20.0,VVar8);
    local_b8.x = pVVar13->x;
    local_b8.y = pVVar13->y;
    pVVar11 = &local_b8;
    local_b8.z = pVVar13->z;
    lVar18 = DisplayInterface::colorRed;
    pVVar13 = (VECTOR_3D *)(**(code **)(*(int *)pWVar9 + 0xc))();
    WorldLine(pVVar13,pVVar11,lVar18);
  }
  return;
}
