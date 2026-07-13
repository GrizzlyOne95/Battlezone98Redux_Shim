/*
 * Entry: 004db7e6
 * Name: TargetCam::Render
 * Namespace: TargetCam
 * Signature: void Render(TargetCam * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TargetCam::Render(TargetCam *this)

{
  CAMERA *pCVar1;
  int *piVar2;
  char *pcVar3;
  float fVar4;
  bool bVar5;
  uchar uVar6;
  GameObject *pGVar7;
  _OBJ76 *p_Var8;
  float *pfVar9;
  SPHERE *pSVar10;
  MAT_3D *pMVar11;
  tagENTITY *ptVar12;
  VECTOR_3D *pVVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  ulong uVar17;
  long lVar18;
  OBJECT_CLASS_T OVar19;
  MAT_3D local_ec;
  VECTOR_3D local_ac;
  ulong local_a0;
  ulong local_9c;
  ulong local_98;
  ulong local_94;
  undefined1 local_90 [28];
  float local_74;
  float local_70;
  double local_68;
  double local_60;
  double local_58;
  VECTOR_3D local_50;
  float local_44;
  float local_40;
  float local_3c;
  VECTOR_3D local_38;
  int local_2c;
  float local_28;
  long local_24;
  int local_20;
  GameObject *local_1c;
  ulong local_18;
  int local_10;
  int local_c;
  int local_8;
  
  if (this->enabled != false) {
    this->enabled = false;
    local_1c = GameObject::userObject;
    if (GameObject::userObject != (GameObject *)0x0) {
      piVar2 = &GameObject::userObject->targetHandle;
      pGVar7 = GameObject::GetObj(*piVar2);
      if (this->targetObj != pGVar7) {
        pGVar7 = GameObject::GetObj(*piVar2);
        this->targetObj = pGVar7;
        if (pGVar7 == (GameObject *)0x0) {
          p_Var8 = (_OBJ76 *)0x0;
        }
        else {
          OVar19 = CLASS_ID_EYEPOINT;
          p_Var8 = (_OBJ76 *)(**(code **)(pGVar7->_padding_ + 0x30))();
          p_Var8 = obj_find_class(p_Var8,OVar19);
        }
        this->targetEye = p_Var8;
      }
      if (this->targetObj != (GameObject *)0x0) {
        iVar16 = (int)(Device.Viewport.Width * 3 + (Device.Viewport.Width * 3 >> 0x1f & 3U)) >> 2;
        uVar17 = iVar16 - 10;
        iVar14 = (int)(Device.Viewport.Height + (Device.Viewport.Height >> 0x1f & 3U)) >> 2;
        local_10 = Device.Viewport.Width + -0xb;
        iVar15 = iVar14 + 10;
        local_18 = uVar17;
        local_c = iVar15;
        if (((((float)(int)uVar17 != (this->camera).Left) || ((this->camera).Bottom != 10.0)) ||
            (local_8 = Device.Viewport.Width + -10, (float)local_8 != (this->camera).Right)) ||
           (local_20 = iVar14 + 0xb, (float)local_20 != (this->camera).Top)) {
          local_20 = iVar14 + 0xb;
          local_8 = Device.Viewport.Width + -10;
          Camera_Set_Window(&this->camera,uVar17,10,local_8,local_20);
        }
        local_28 = spriteZ;
        local_2c = local_10 + 2;
        spriteZ = 249.0;
        local_24 = iVar16 + -0xc;
        Clipped_Rect_Filled(DisplayInterface::currentBuffer,local_24,8,local_2c,9,
                            DisplayInterface::colorBlack,SOLID_PIXELS);
        Clipped_Rect_Filled(DisplayInterface::currentBuffer,local_24,10,iVar16 + -0xb,iVar15,
                            DisplayInterface::colorBlack,SOLID_PIXELS);
        Clipped_Rect_Filled(DisplayInterface::currentBuffer,local_8,10,local_2c,iVar15,
                            DisplayInterface::colorBlack,SOLID_PIXELS);
        local_8 = iVar14 + 0xc;
        Clipped_Rect_Filled(DisplayInterface::currentBuffer,local_24,local_20,local_2c,local_8,
                            DisplayInterface::colorBlack,SOLID_PIXELS);
        if (useD3D != 0) {
          D3DAppGetViewport(&local_9c,&local_94,&local_98,&local_a0);
          D3DAppSetViewport(uVar17,10,(local_10 - uVar17) + 1,iVar14 + 1);
        }
        cameraView = 1;
        pfVar9 = (float *)(**(code **)(this->targetObj->_padding_ + 0xc))();
        local_44 = *pfVar9;
        local_40 = pfVar9[1];
        local_3c = pfVar9[2];
        Update_Rotator_Matrix(&this->camera);
        pGVar7 = local_1c;
        bVar5 = GameObject::FriendP(local_1c,this->targetObj);
        if ((bVar5) && (bVar5 = GameObject::FriendP(this->targetObj,pGVar7), bVar5)) {
          if (this->targetEye == (_OBJ76 *)0x0) {
            pGVar7 = this->targetObj;
            pMVar11 = &pGVar7->obj->transform;
            pfVar9 = (float *)local_90;
            for (iVar14 = 0x10; iVar14 != 0; iVar14 = iVar14 + -1) {
              *pfVar9 = pMVar11->right_x;
              pMVar11 = (MAT_3D *)&pMVar11->right_y;
              pfVar9 = pfVar9 + 1;
            }
            pSVar10 = GameObject::GetSphere(pGVar7);
            local_68 = (double)((pSVar10->origin).x * (float)local_90._0_4_ +
                                (pSVar10->origin).y * (float)local_90._12_4_ +
                                (pSVar10->origin).z * (float)local_90._24_4_ + (float)local_68);
            local_60 = (double)((pSVar10->origin).x * (float)local_90._4_4_ +
                                (pSVar10->origin).y * (float)local_90._16_4_ +
                                (pSVar10->origin).z * local_74 + (float)local_60);
            local_58 = (double)((pSVar10->origin).x * (float)local_90._8_4_ +
                                (pSVar10->origin).y * (float)local_90._20_4_ +
                                (pSVar10->origin).z * local_70 + (float)local_58);
            Camera_Set_Matrix(&this->camera,(MAT_3D *)local_90);
          }
          else {
            pMVar11 = obj_rel_parent_matrix(&local_ec,this->targetEye,(_OBJ76 *)0x0);
            pfVar9 = (float *)local_90;
            for (iVar14 = 0x10; iVar14 != 0; iVar14 = iVar14 + -1) {
              *pfVar9 = pMVar11->right_x;
              pMVar11 = (MAT_3D *)&pMVar11->right_y;
              pfVar9 = pfVar9 + 1;
            }
            Camera_Set_Matrix(&this->camera,(MAT_3D *)local_90);
          }
          SortZmin = 0.0;
          pCVar1 = &this->camera;
          SortZmax = 250.0;
          EnableSkipLines(pCVar1,1,0);
          spriteZ = 248.0;
          uVar6 = UserPref_lineskip();
          if (uVar6 == '\0') {
            lVar18 = 10;
            iVar14 = local_c;
          }
          else {
            lVar18 = 5;
            iVar14 = local_c / 2;
          }
          Clipped_Rect_Filled((this->camera).Buffer,local_18,lVar18,local_10,iVar14,0xdf,
                              SOLID_PIXELS);
          Submit_Terrain_Mesh(pCVar1);
          ptVar12 = (tagENTITY *)(**(code **)(this->targetObj->_padding_ + 0x2c))();
          Submit_Rear_View_Entities(pCVar1,ptVar12);
          Ordnance_SubmitAll(pCVar1);
          GameFeature_SubmitAll(pCVar1);
          ZSORTDraw(pCVar1,1);
          EnableSkipLines(pCVar1,0,0);
        }
        else {
          local_1c = (GameObject *)&pGVar7->_padding_;
          pfVar9 = (float *)(**(code **)(*(int *)local_1c + 0xc))();
          local_50.x = *pfVar9;
          local_50.y = pfVar9[1];
          local_50.z = pfVar9[2];
          iVar14 = (**(code **)(local_1c->_padding_ + 0x30))();
          local_ac.x = *(float *)(iVar14 + 0x2c);
          local_ac.y = *(float *)(iVar14 + 0x30);
          local_ac.z = *(float *)(iVar14 + 0x34);
          local_50.x = local_44 - local_50.x;
          local_50.y = local_40 - local_50.y;
          local_50.z = local_3c - local_50.z;
          local_38.x = local_50.x;
          local_38.y = local_50.y;
          local_38.z = local_50.z;
          pVVar13 = Normalize_Vector(&local_38,&local_50);
          local_90._24_4_ = pVVar13->x;
          local_74 = pVVar13->y;
          local_70 = pVVar13->z;
          pVVar13 = Cross_Product(&local_50,&local_ac,(VECTOR_3D *)(local_90 + 0x18));
          local_90._0_4_ = pVVar13->x;
          local_90._4_4_ = pVVar13->y;
          local_90._8_4_ = pVVar13->z;
          pVVar13 = Normalize_Vector(&local_ac,(VECTOR_3D *)local_90);
          local_90._0_4_ = pVVar13->x;
          local_90._4_4_ = pVVar13->y;
          local_90._8_4_ = pVVar13->z;
          pVVar13 = Cross_Product(&local_ac,(VECTOR_3D *)(local_90 + 0x18),(VECTOR_3D *)local_90);
          local_90._12_4_ = pVVar13->x;
          local_90._16_4_ = pVVar13->y;
          local_90._20_4_ = pVVar13->z;
          pSVar10 = GameObject::GetSphere(this->targetObj);
          pCVar1 = &this->camera;
          fVar4 = pSVar10->radius + pSVar10->radius;
          local_68 = (double)(local_44 - (float)local_90._24_4_ * fVar4);
          local_60 = (double)(local_40 - local_74 * fVar4);
          local_58 = (double)(local_3c - fVar4 * local_70);
          Camera_Set_Matrix(pCVar1,(MAT_3D *)local_90);
          SortZmin = 0.0;
          SortZmax = 250.0;
          EnableSkipLines(pCVar1,1,0);
          spriteZ = 248.0;
          uVar6 = UserPref_lineskip();
          if (uVar6 == '\0') {
            lVar18 = 10;
            iVar14 = local_c;
          }
          else {
            lVar18 = 5;
            iVar14 = local_c / 2;
          }
          Clipped_Rect_Filled((this->camera).Buffer,local_18,lVar18,local_10,iVar14,0xdf,
                              SOLID_PIXELS);
          ptVar12 = (tagENTITY *)(**(code **)(this->targetObj->_padding_ + 0x2c))();
          Submit_Single_Entity(pCVar1,ptVar12);
          SmokeEffect::Submit(&smokeEffect,pCVar1);
          ZSORTDraw(pCVar1,1);
          EnableSkipLines(pCVar1,0,0);
        }
        pGVar7 = this->targetObj;
        iVar14 = pGVar7->nameIndex;
        if (iVar14 == 0) {
          pcVar3 = pGVar7->name;
          if (pcVar3 != (char *)0x0) {
            lVar18 = GameObject::GetColor(pGVar7);
            Font_Set_Foreground(Default_Font,lVar18);
            Font_Print_String(Default_Font,DisplayInterface::currentBuffer,local_18 + 2,0xb,pcVar3);
          }
        }
        else {
          spriteZ = local_28;
          Foreground_Color = GameObject::GetColor(this->targetObj);
          DrawSprite(DisplayInterface::currentBuffer,iVar14,local_18 + 2,0xb,5);
        }
        if (useD3D != 0) {
          D3DAppSetViewport(local_9c,local_94,local_98,local_a0);
          spriteZ = local_28 + 0.01;
          D3D_Color_Rectangle(0x100ff00,local_24,8,local_2c,local_8,1);
        }
        cameraView = 0;
        spriteZ = local_28;
      }
    }
  }
  return;
}
