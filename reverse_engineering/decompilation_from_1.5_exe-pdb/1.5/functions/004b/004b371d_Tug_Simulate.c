/*
 * Entry: 004b371d
 * Name: Tug::Simulate
 * Namespace: Tug
 * Signature: void Simulate(Tug * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tug::Simulate(Tug *this,float param_1)

{
  _OBJ76 **pp_Var1;
  float fVar2;
  _OBJ76 *p_Var3;
  GameObject *pGVar4;
  long lVar5;
  int *piVar6;
  _OBJ76 *p_Var7;
  MAT_3D *pMVar8;
  int iVar9;
  Tug *unaff_EDI;
  MAT_3D *pMVar10;
  MAT_3D local_cc;
  MAT_3D local_8c;
  MAT_3D local_4c;
  tagANIMOBJ_ACTIVE_LIST *local_c;
  byte local_5;
  
  piVar6 = &this->animHandle;
  if ((-1 < *piVar6) &&
     ((lVar5 = AnimObj_Status(*piVar6,&local_c), lVar5 != 0 || (local_c->status != 1)))) {
    AnimObj_Stop(*piVar6);
    *piVar6 = -1;
  }
  iVar9 = this->_padding_;
  if (iVar9 == 0) {
    piVar6 = (int *)(this->_padding_ + 0xe0);
    if (*piVar6 == 0) goto LAB_004b38d3;
    *piVar6 = 0;
    this->_padding_ = 1;
    DoAudioNew((char *)(this->_padding_ + 0x39c),(_OBJ76 *)this->_padding_,(GAS_CTRL *)0x0);
    AnimObj_Start((void *)this->_padding_,0,&this->animHandle);
    fVar2 = this->timeDeploy;
  }
  else if (iVar9 == 1) {
    fVar2 = this->delayTimer - param_1;
    this->delayTimer = fVar2;
    if (0.0 < fVar2) goto LAB_004b38d3;
    if (this->cargo == (GameObject *)0x0) {
      LoadCargo(this);
    }
    this->_padding_ = 2;
    if (this->cargo != (GameObject *)0x0) goto LAB_004b38d3;
    fVar2 = 1.0;
  }
  else {
    if (iVar9 != 2) {
      if (iVar9 == 3) {
        fVar2 = this->delayTimer - param_1;
        this->delayTimer = fVar2;
        if ((*piVar6 < 0) && (fVar2 <= 0.0)) {
          if (this->cargo != (GameObject *)0x0) {
            DropCargo(unaff_EDI);
          }
          this->_padding_ = 0;
        }
      }
      goto LAB_004b38d3;
    }
    if ((this->cargo == (GameObject *)0x0) &&
       (fVar2 = this->delayTimer - param_1, this->delayTimer = fVar2, fVar2 <= 0.0)) {
      *(undefined4 *)(this->_padding_ + 0xe0) = 1;
    }
    piVar6 = (int *)(this->_padding_ + 0xe0);
    if (*piVar6 == 0) goto LAB_004b38d3;
    *piVar6 = 0;
    this->_padding_ = 3;
    DoAudioNew((char *)(this->_padding_ + 0x3ac),(_OBJ76 *)this->_padding_,(GAS_CTRL *)0x0);
    AnimObj_Start((void *)this->_padding_,1,&this->animHandle);
    fVar2 = this->timeUndeploy;
  }
  this->delayTimer = fVar2;
LAB_004b38d3:
  local_5 = ~(byte)(*(uint *)(this->_padding_ + 0x14) >> 9) & 1;
  HoverCraft::Simulate((HoverCraft *)this,param_1);
  if ((local_5 != 0) && (this->cargo != (GameObject *)0x0)) {
    p_Var7 = (_OBJ76 *)(**(code **)(this->cargo->_padding_ + 0x30))();
    pp_Var1 = &this->hitchTug;
    if (*pp_Var1 == (_OBJ76 *)0x0) {
      *pp_Var1 = (_OBJ76 *)this->_padding_;
    }
    pMVar8 = obj_rel_parent_matrix(&local_8c,*pp_Var1,(_OBJ76 *)0x0);
    p_Var3 = this->hitchCargo;
    pMVar10 = &local_cc;
    for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
      pMVar10->right_x = pMVar8->right_x;
      pMVar8 = (MAT_3D *)&pMVar8->right_y;
      pMVar10 = (MAT_3D *)&pMVar10->right_y;
    }
    if (p_Var3 == (_OBJ76 *)0x0) {
      pMVar8 = &local_cc;
    }
    else {
      pMVar8 = obj_rel_parent_matrix(&local_8c,p_Var3,p_Var7);
      pMVar10 = &local_4c;
      for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
        pMVar10->right_x = pMVar8->right_x;
        pMVar8 = (MAT_3D *)&pMVar8->right_y;
        pMVar10 = (MAT_3D *)&pMVar10->right_y;
      }
      pMVar8 = Matrix_Inverse(&local_8c,(MAT_3D *)unaff_EDI);
      pMVar10 = &local_4c;
      for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
        pMVar10->right_x = pMVar8->right_x;
        pMVar8 = (MAT_3D *)&pMVar8->right_y;
        pMVar10 = (MAT_3D *)&pMVar10->right_y;
      }
      pMVar8 = Matrix_Multiply(&local_8c,&local_4c,&local_cc);
    }
    pMVar10 = &local_4c;
    for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
      pMVar10->right_x = pMVar8->right_x;
      pMVar8 = (MAT_3D *)&pMVar8->right_y;
      pMVar10 = (MAT_3D *)&pMVar10->right_y;
    }
    GameObject::SetTransform(this->cargo,&local_4c);
    pGVar4 = this->cargo;
    (pGVar4->euler).v.x = (float)this->_padding_;
    (pGVar4->euler).v.y = (float)this->_padding_;
    (pGVar4->euler).v.z = (float)this->_padding_;
    (pGVar4->euler).v_mag = (float)this->_padding_;
    (pGVar4->euler).v_mag_inv = (float)this->_padding_;
    (pGVar4->euler).omega.x = (float)this->_padding_;
    (pGVar4->euler).omega.y = (float)this->_padding_;
    (pGVar4->euler).omega.z = (float)this->_padding_;
    (pGVar4->euler).Accel.x = (float)this->_padding_;
    (pGVar4->euler).Accel.y = (float)this->_padding_;
    (pGVar4->euler).Accel.z = (float)this->_padding_;
    (pGVar4->euler).Alpha.x = (float)this->_padding_;
    (pGVar4->euler).Alpha.y = (float)this->_padding_;
    (pGVar4->euler).Alpha.z = (float)this->_padding_;
  }
  return;
}
