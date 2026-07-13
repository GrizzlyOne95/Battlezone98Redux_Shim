/*
 * Entry: 004dab57
 * Name: SniperInterface::Render
 * Namespace: SniperInterface
 * Signature: void Render(SniperInterface * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SniperInterface::Render(SniperInterface *this)

{
  GameObject *pGVar1;
  char cVar2;
  bool bVar3;
  ulong extraout_EAX;
  ulong extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  long lVar4;
  tagENTITY *ptVar5;
  SPHERE *pSVar6;
  float *pfVar7;
  VECTOR_3D *pVVar8;
  int extraout_EAX_03;
  int iVar9;
  int iVar10;
  tagPOINT tVar11;
  Range_Search_Results local_9c;
  VECTOR_3D local_70;
  VECTOR_3D local_64;
  VECTOR_3D local_58;
  GameObject *local_4c;
  float local_48;
  ulong local_44;
  ulong local_40;
  ulong local_3c;
  ulong local_38;
  ulong local_34;
  ulong local_30;
  int local_2c;
  int local_28;
  float local_24;
  GameObject *local_20;
  float local_1c;
  PANE local_18;
  float *local_8;
  
  if (this->enabled != false) {
    bVar3 = this->soviet;
    local_1c = (float)SNIPERCAM_POS[bVar3].x;
    local_8 = (float *)((int)local_1c + -0x140);
    _ftol2_sse();
    local_20 = (GameObject *)SNIPERCAM_POS[bVar3].y;
    local_8 = &local_20[-1].euler.omega.y;
    local_34 = extraout_EAX;
    _ftol2_sse();
    local_8 = (float *)((int)local_1c + -0xc0);
    local_30 = extraout_EAX_00;
    _ftol2_sse();
    local_8 = (float *)(local_20[-1].modeList.modeList + 5);
    iVar10 = extraout_EAX_01 + -1;
    local_2c = iVar10;
    _ftol2_sse();
    local_18.x0 = local_34;
    local_18.y0 = local_30;
    iVar9 = extraout_EAX_02 + -1;
    local_28 = iVar9;
    local_18.x1 = iVar10;
    local_18.y1 = iVar9;
    lVar4 = Clip_Pane(&local_18,&DisplayInterface::currentBuffer->Pane);
    if (-1 < lVar4) {
      if (((((float)local_18.x0 != (this->camera).Left) ||
           ((float)local_18.y0 != (this->camera).Bottom)) ||
          (local_8 = (float *)(local_18.x1 + 1), (float)(int)local_8 != (this->camera).Right)) ||
         (local_8 = (float *)(local_18.y1 + 1), (float)(int)local_8 != (this->camera).Top)) {
        Camera_Set_Window(&this->camera,local_34,local_30,extraout_EAX_01,extraout_EAX_02);
      }
      local_24 = spriteZ;
      cameraView = 1;
      if (useD3D != 0) {
        D3DAppGetViewport(&local_3c,&local_44,&local_38,&local_40);
        D3DAppSetViewport(local_18.x0,local_18.y0,(local_18.x1 - local_18.x0) + 1,
                          (local_18.y1 - local_18.y0) + 1);
      }
      Update_Rotator_Matrix(&this->camera);
      SortZmin = 0.0;
      SortZmax = 500.0;
      spriteZ = 499.0;
      Clipped_Rect_Filled((this->camera).Buffer,local_18.x0,local_18.y0,local_18.x1,local_18.y1,0xdf
                          ,SOLID_PIXELS);
      Submit_Terrain_Mesh(&this->camera);
      ptVar5 = get_user_entity();
      Submit_Rear_View_Entities(&this->camera,ptVar5);
      Ordnance_SubmitAll(&this->camera);
      GameFeature_SubmitAll(&this->camera);
      ZSORTDraw(&this->camera,1);
      local_4c = GameObject::userObject;
      Range::Search(collision_range_search,(this->camera).bSphere_Center.x,
                    (this->camera).bSphere_Center.z,(this->camera).bSphere_Radius,&local_9c);
      while (bVar3 = Range_Search_Results::Get_Next_Object(&local_9c,(int **)&local_8), bVar3) {
        local_20 = GameObject::GetObj((int)*local_8);
        if (((local_20 != (GameObject *)0x0) && (local_20 != local_4c)) &&
           (cVar2 = (**(code **)(local_20->_padding_ + 0x14))(), pGVar1 = local_20, cVar2 != '\0'))
        {
          pSVar6 = GameObject::GetSphere(local_20);
          local_48 = pSVar6->radius;
          pfVar7 = (float *)(**(code **)(pGVar1->_padding_ + 0xc))();
          local_58.x = *pfVar7;
          local_58.y = pfVar7[1];
          local_58.z = pfVar7[2];
          Vector_Transform(&local_58,&local_58,1,&(this->camera).Matrix);
          lVar4 = Camera_Bounding_Sphere_Test(&this->camera,&local_58,local_48);
          iVar9 = local_28;
          iVar10 = local_2c;
          if (lVar4 < 1) {
            pVVar8 = obj_get_world_position(&local_70,*(_OBJ76 **)(local_20[1]._padding_ + 0xf4));
            local_64.x = pVVar8->x;
            local_64.y = pVVar8->y;
            local_64.z = pVVar8->z;
            tVar11 = WorldToScreen(&local_64,&this->camera,&local_1c);
            iVar9 = local_28;
            iVar10 = local_2c;
            if (0.0 < local_1c) {
              _ftol2_sse();
              DrawScaledSprite(&this->camera,this->eyepoint,tVar11.x,tVar11.y,1,extraout_EAX_03,
                               extraout_EAX_03,0x250004);
              iVar9 = local_28;
              iVar10 = local_2c;
            }
          }
        }
      }
      spriteZ = local_24 + 0.015;
      DrawSprite((this->camera).Buffer,this->crosshair,(int)(local_34 + iVar10) / 2,
                 (int)(local_30 + iVar9) / 2,0x250004);
      if (useD3D != 0) {
        D3DAppSetViewport(local_3c,local_44,local_38,local_40);
        spriteZ = local_24 + 0.02;
        D3D_Color_Rectangle(0x100ff00,local_18.x0,local_18.y0,local_18.x1,local_18.y1,1);
      }
      spriteZ = local_24;
    }
    this->enabled = false;
    cameraView = 0;
  }
  return;
}
