/*
 * Entry: 0049d8c7
 * Name: HoverCraft::UpdateEyepoint
 * Namespace: HoverCraft
 * Signature: void UpdateEyepoint(HoverCraft * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall HoverCraft::UpdateEyepoint(HoverCraft *this,float param_1)

{
  int iVar1;
  float fVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  tagENTITY *ptVar5;
  VECTOR_3D *pVVar6;
  MAT_3D *pMVar7;
  MAT_3D *pMVar8;
  int iVar9;
  SINCOS SVar10;
  MAT_3D local_b0;
  MAT_3D local_70;
  VECTOR_3D local_30;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  MAT_3D *local_14;
  SINCOS local_10;
  VECTOR_3D *local_8;
  
  iVar9 = *(int *)(this->_padding_ + 0xf4);
  ptVar5 = Get_Camera_Owner();
  if (((((tagENTITY *)this->_padding_ == ptVar5) && (View_Record.Intenal_View != 0)) &&
      ((UserProfilePtr->graphicDetail).cockpit != '\0')) && (Cockpit_Visible != 0)) {
    local_10 = SinCos(*(float *)(this->_padding_ + 0xc4) * -0.2);
    SVar10 = SinCos(*(float *)(this->_padding_ + 200) * -0.1);
    fVar2 = local_10.Sin * (float)local_14;
    local_18 = SVar10.Sin;
    iVar1 = this->_padding_;
    local_8 = &this->omegaEye;
    local_14 = (MAT_3D *)SVar10.Cos;
    local_10.Cos = local_10.Cos * (float)local_14;
    _local_18 = CONCAT44((float *)(iVar9 + 0x20),local_18);
    local_24 = (*(float *)(iVar9 + 0x2c) * fVar2 +
               *(float *)(iVar9 + 0x30) * -local_18 + *(float *)(iVar9 + 0x34) * local_10.Cos) *
               25.0 + ((((float)this->_padding_ * *(float *)(iVar1 + 0x38) +
                        (float)this->_padding_ * *(float *)(iVar1 + 0x3c) +
                        (float)this->_padding_ * *(float *)(iVar1 + 0x40)) * 0.1 +
                       -(float)this->_padding_) - local_8->x * 10.0);
    local_20 = (-(float)this->_padding_ - (this->omegaEye).y * 10.0) -
               (*(float *)(iVar9 + 0x28) * local_10.Cos + *(float *)(iVar9 + 0x24) * -local_18 +
               *(float *)(iVar9 + 0x20) * fVar2) * 25.0;
    local_1c = ((-(float)this->_padding_ -
                (*(float *)(iVar1 + 0x20) * (float)this->_padding_ +
                (float)this->_padding_ * *(float *)(iVar1 + 0x24) +
                (float)this->_padding_ * *(float *)(iVar1 + 0x28)) * 0.1) -
               (this->omegaEye).z * 10.0) - *(float *)(iVar9 + 0x2c) * 25.0;
    local_10.Cos = param_1 * 0.5;
    VVar3.y = local_20;
    VVar3.x = local_24;
    VVar3.z = local_1c;
    pVVar6 = AddMultVectors(&local_30,*local_8,param_1 * 0.5,VVar3);
    local_8->x = pVVar6->x;
    local_8->y = pVVar6->y;
    local_8->z = pVVar6->z;
    pMVar7 = Build_Position_Rotation_Matrix
                       (&local_b0,-(local_8->x * param_1),-(param_1 * (this->omegaEye).y),
                        -((this->omegaEye).z * param_1),0.0,0.0,0.0);
    pMVar8 = &local_70;
    for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
      pMVar8->right_x = pMVar7->right_x;
      pMVar7 = (MAT_3D *)&pMVar7->right_y;
      pMVar8 = (MAT_3D *)&pMVar8->right_y;
    }
    pMVar7 = local_14;
    pMVar8 = Matrix_Multiply(&local_b0,&local_70,local_14);
    for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
      pMVar7->right_x = pMVar8->right_x;
      pMVar8 = (MAT_3D *)&pMVar8->right_y;
      pMVar7 = (MAT_3D *)&pMVar7->right_y;
    }
    VVar4.y = local_20;
    VVar4.x = local_24;
    VVar4.z = local_1c;
    pVVar6 = AddMultVectors(&local_30,*local_8,local_10.Cos,VVar4);
    local_8->x = pVVar6->x;
    local_8->y = pVVar6->y;
    local_8->z = pVVar6->z;
  }
  else {
    *(undefined4 *)(iVar9 + 0x20) = 0x3f800000;
    *(undefined4 *)(iVar9 + 0x24) = 0;
    *(undefined4 *)(iVar9 + 0x28) = 0;
    *(undefined4 *)(iVar9 + 0x2c) = 0;
    *(undefined4 *)(iVar9 + 0x34) = 0;
    *(undefined4 *)(iVar9 + 0x38) = 0;
    *(undefined4 *)(iVar9 + 0x3c) = 0;
    *(undefined4 *)(iVar9 + 0x30) = 0x3f800000;
    *(undefined4 *)(iVar9 + 0x40) = 0x3f800000;
    (this->omegaEye).x = 0.0;
    (this->omegaEye).y = 0.0;
    (this->omegaEye).z = 0.0;
  }
  return;
}
