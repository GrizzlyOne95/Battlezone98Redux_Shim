/*
 * Entry: 004860cd
 * Name: Craft::UpdateTemperature
 * Namespace: Craft
 * Signature: void UpdateTemperature(Craft * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Craft::UpdateTemperature(Craft *this,float param_1)

{
  _OBJ76 *p_Var1;
  Craft *pCVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  VECTOR_3D *pVVar7;
  int unaff_EDI;
  float fVar8;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 local_2c;
  float local_28;
  float local_24;
  double local_20;
  Craft *local_18;
  undefined1 local_14 [8];
  float fStack_c;
  float local_8;
  
  if ((UserProfilePtr->playOption & 1) == 0) {
    local_18 = this;
    iVar4 = GetLavaMat();
    Set_Rounding(unaff_EDI);
    local_20 = (double)((float)this->_padding_ * Terrain.Grid_Scale + (float)Float2Int);
    unique0x0000aa00 = (double)(Terrain.Grid_Scale * (float)this->_padding_ + (float)Float2Int);
    Set_Rounding(unaff_EDI);
    uVar3 = local_14._4_4_;
    iVar6 = local_20._0_4_;
    iVar5 = GetTerMat(local_20._0_4_,local_14._4_4_);
    if (iVar5 == iVar4) {
      iVar6 = GetTerMat(iVar6 + -1,uVar3 + -1);
      iVar5 = GetTerMat(local_20._0_4_ + 1,uVar3 + -1);
      local_8 = (float)((2 - (uint)(iVar6 != iVar4)) - (uint)(iVar5 != iVar4));
      iVar6 = local_20._0_4_;
      fStack_c = (float)(local_20._0_4_ + -1);
      iVar5 = GetTerMat(local_20._0_4_ + -1,uVar3 + 1);
      local_8 = (float)((uint)(iVar5 == iVar4) + (int)local_8);
      iVar5 = GetTerMat(iVar6 + 1,uVar3 + 1);
      local_8 = (float)((uint)(iVar5 == iVar4) + (int)local_8);
      iVar5 = GetTerMat(local_20._0_4_,uVar3 + -1);
      local_8 = (float)((uint)(iVar5 == iVar4) + (int)local_8);
      iVar5 = GetTerMat(local_20._0_4_,uVar3 + 1);
      local_8 = (float)((uint)(iVar5 == iVar4) + (int)local_8);
      iVar5 = GetTerMat((long)fStack_c,uVar3);
      fStack_c = (float)((uint)(iVar5 == iVar4) + (int)local_8);
      iVar6 = GetTerMat(iVar6 + 1,uVar3);
      pCVar2 = local_18;
      p_Var1 = (_OBJ76 *)local_18->_padding_;
      fStack_c = (float)((int)((uint)(iVar6 == iVar4) + (int)fStack_c) / 2);
      fVar8 = Terrain_FindFloor((p_Var1->transform).posit_x,(p_Var1->transform).posit_z);
      fVar8 = (float)(p_Var1->transform).posit_y - fVar8;
      if (fVar8 <= 1.0) {
        if (fVar8 <= 0.0) {
          fVar8 = 2.0;
        }
        else {
          fVar8 = 2.0 - fVar8;
        }
      }
      else {
        fVar8 = 1.25 - fVar8 * 0.25;
      }
      local_8 = (float)(int)fStack_c;
      local_28 = fVar8 * local_8 * param_1 * 40.0;
      if (0.0 < local_28) {
        local_34 = 0;
        uStack_30 = 0;
        local_2c = 4;
        pVVar7 = Terrain_GetNormal((VECTOR_3D *)local_14,
                                   (double)CONCAT44(SUB84((double)(float)pCVar2->_padding_,0),
                                                    (int)((ulonglong)
                                                          (double)((VECTOR_3D *)&pCVar2->_padding_)
                                                                  ->x >> 0x20)),
                                   (double)CONCAT44(unaff_EDI,
                                                    (int)((ulonglong)
                                                          (double)(float)pCVar2->_padding_ >> 0x20))
                                  );
        local_24 = pVVar7->x;
        local_20._0_4_ = (int)pVVar7->y;
        local_20._4_4_ = pVVar7->z;
        (**(code **)(pCVar2->_padding_ + 0x38))(&local_34,&local_24);
        if (pCVar2 == (Craft *)GameObject::userObject) {
          ColorFade::SetFade(&colorFade,local_8 * 0.01,5.0,0xff,0x40,0);
        }
      }
    }
  }
  return;
}
