/*
 * Entry: 0052a60c
 * Name: Beam::Simulate
 * Namespace: Beam
 * Signature: void Simulate(Beam * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall Beam::Simulate(Beam *this,float param_1)

{
  uint *puVar1;
  float fVar2;
  VECTOR_3D_LONG VVar3;
  VECTOR_3D VVar4;
  undefined6 uVar5;
  ushort uVar6;
  ushort uVar7;
  int iVar8;
  Weapon *pWVar9;
  MAT_3D *pMVar10;
  VECTOR_3D *pVVar11;
  _OBJ76 *p_Var12;
  int iVar13;
  float *pfVar14;
  float *pfVar15;
  undefined1 *puVar16;
  uint uVar17;
  MAT_3D local_c4;
  float local_84 [16];
  VECTOR_3D_LONG local_44;
  VECTOR_3D local_2c;
  double local_20;
  undefined1 local_18 [6];
  undefined2 uStack_12;
  double local_10;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar13 = this->_padding_;
  if ((*(uint *)(iVar13 + 0x14) & 0x200) == 0) {
    this->_padding_ = (int)(*(float *)(this->_padding_ + 0x54) * param_1);
    param_1 = *(float *)(this->_padding_ + 0x4c);
    if (-1 < this->hardpoint) {
      if (this->_padding_ == 0) {
        iVar8 = 0;
      }
      else {
        iVar8 = *(int *)(this->_padding_ + 0xb4);
      }
      if (((iVar8 != 0) && (*(Carrier **)(iVar8 + 0x198) != (Carrier *)0x0)) &&
         (pWVar9 = Carrier::GetWeapon(*(Carrier **)(iVar8 + 0x198),this->hardpoint),
         pWVar9 != (Weapon *)0x0)) {
        pMVar10 = Matrix_Multiply(&local_c4,&pWVar9->obj->transform,&pWVar9->M);
        pfVar14 = local_84;
        for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
          *pfVar14 = pMVar10->right_x;
          pMVar10 = (MAT_3D *)&pMVar10->right_y;
          pfVar14 = pfVar14 + 1;
        }
        pfVar14 = local_84;
        pfVar15 = (float *)(this->_padding_ + 0x20);
        for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
          *pfVar15 = *pfVar14;
          pfVar14 = pfVar14 + 1;
          pfVar15 = pfVar15 + 1;
        }
        iVar13 = this->_padding_;
        local_2c.x = ((VECTOR_3D *)(iVar13 + 0x38))->x;
        local_2c.y = *(float *)(iVar13 + 0x3c);
        local_2c.z = *(float *)(iVar13 + 0x40);
        pVVar11 = ScaleVector((VECTOR_3D *)(local_18 + 4),*(float *)(this->_padding_ + 0x50),
                              *(VECTOR_3D *)(iVar13 + 0x38));
        local_2c.x = pVVar11->x;
        local_2c.y = pVVar11->y;
        uVar5 = *(undefined6 *)pVVar11;
        local_2c.z = pVVar11->z;
        this->_padding_ = (int)local_2c.x;
        this->_padding_ = (int)local_2c.y;
        this->_padding_ = (int)local_2c.z;
        fVar2 = *(float *)(this->_padding_ + 0x50);
        this->_padding_ = (int)fVar2;
        if (fVar2 <= 0.0) {
          fVar2 = 1e+30;
        }
        else {
          fVar2 = 1.0 / fVar2;
        }
        iVar13 = this->_padding_;
        this->_padding_ = (int)fVar2;
        (this->origin).x = *(double *)(iVar13 + 0x48);
        (this->origin).y = *(double *)(iVar13 + 0x50);
        (this->origin).z = *(double *)(iVar13 + 0x58);
        local_20 = *(double *)*(undefined1 (*) [20])(iVar13 + 0x48);
        _local_18 = *(double *)(iVar13 + 0x50);
        local_10 = *(double *)(iVar13 + 0x58);
        VVar3.z._4_4_ = (int)((ulonglong)local_10 >> 0x20);
        VVar3._0_20_ = *(undefined1 (*) [20])(iVar13 + 0x48);
        VVar4.y._2_2_ = (short)((uint)local_2c.y >> 0x10);
        VVar4._0_6_ = uVar5;
        VVar4.z = local_2c.z;
        iVar13 = Terrain_GetIntersection(VVar3,VVar4,&param_1,(VECTOR_3D *)0x0);
        local_44.x = (double)((float)this->_padding_ * param_1 + (float)local_20);
        local_44.y = (double)((float)this->_padding_ * param_1 + (float)_local_18);
        local_44.z = (double)((float)this->_padding_ * param_1 + (float)local_10);
        p_Var12 = Bullet::Collision((Bullet *)this,&param_1,&local_44,&local_2c);
        *(double *)(this->_padding_ + 0x48) = local_44.x;
        *(double *)(this->_padding_ + 0x50) = local_44.y;
        *(double *)(this->_padding_ + 0x58) = local_44.z;
        if (p_Var12 == (_OBJ76 *)0x0) {
          if (iVar13 != 0) {
            (**(code **)(this->_padding_ + 0x14))(0,&local_2c);
          }
        }
        else {
          (**(code **)(this->_padding_ + 0x14))(p_Var12->gameObj,&local_2c);
        }
        puVar1 = (uint *)(this->_padding_ + 0x14);
        *puVar1 = *puVar1 & 0xfffffdff;
        return;
      }
    }
    puVar1 = (uint *)(iVar13 + 0x14);
    *puVar1 = *puVar1 | 0x200;
    iVar13 = Net_IsNetGame();
    if (iVar13 != 0) {
      uVar7 = (ushort)this->_padding_;
      uVar6 = Net_GetMyPlayerID();
      if (uVar7 == uVar6) {
        uVar17 = 6;
        puVar16 = local_18;
        iVar13 = 1;
        uVar6 = 0;
        _local_18 = (double)CONCAT44(CONCAT22(uStack_12,*(undefined2 *)((int)&this->_padding_ + 2)),
                                     CONCAT22(uVar7,0x6f69));
        uVar7 = Net_GetMyPlayerID();
        Net::Send(Net::dp,uVar7,uVar6,iVar13,puVar16,uVar17);
      }
    }
  }
  return;
}
