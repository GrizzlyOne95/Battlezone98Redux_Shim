/*
 * Entry: 0053a779
 * Name: SprayBuilding::Simulate
 * Namespace: SprayBuilding
 * Signature: void Simulate(SprayBuilding * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall SprayBuilding::Simulate(SprayBuilding *this,float param_1)

{
  uint *puVar1;
  int *piVar2;
  float fVar3;
  _OBJ76 *p_Var4;
  VECTOR_3D VVar5;
  VECTOR_3D VVar6;
  OrdnanceClass *pOVar7;
  MAT_3D *pMVar8;
  _gas_object *p_Var9;
  Ordnance *pOVar10;
  ushort uVar11;
  int iVar12;
  int iVar13;
  float *pfVar14;
  MAT_3D *pMVar15;
  ushort uVar16;
  float fVar17;
  MAT_3D local_e8;
  GAS_PREP_INFO local_a8;
  MAT_3D local_8c;
  OrdnanceClass *local_4c;
  undefined1 local_48 [36];
  undefined4 local_24;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&local_8c.up_z;
  piVar2 = &this->_padding_;
  *piVar2 = (int)((*(float *)(this->_padding_ + 0x180) - (float)*piVar2) * param_1 + (float)*piVar2)
  ;
  VVar5.x = (float)this->_padding_;
  VVar5.y = (float)this->_padding_;
  VVar5.z = (float)this->_padding_;
  pMVar8 = Spinner(&local_e8,(MAT_3D *)(this->_padding_ + 0x20),VVar5,param_1);
  pMVar15 = &local_8c;
  for (iVar12 = 0x10; iVar12 != 0; iVar12 = iVar12 + -1) {
    pMVar15->right_x = pMVar8->right_x;
    pMVar8 = (MAT_3D *)&pMVar8->right_y;
    pMVar15 = (MAT_3D *)&pMVar15->right_y;
  }
  pMVar8 = &local_8c;
  pfVar14 = (float *)(this->_padding_ + 0x20);
  for (iVar12 = 0x10; iVar12 != 0; iVar12 = iVar12 + -1) {
    *pfVar14 = pMVar8->right_x;
    pMVar8 = (MAT_3D *)&pMVar8->right_y;
    pfVar14 = pfVar14 + 1;
  }
  fVar17 = Terrain_FindFloor(*(double *)(this->_padding_ + 0x48),*(double *)(this->_padding_ + 0x58)
                            );
  iVar12 = this->_padding_;
  *(double *)(iVar12 + 0x50) =
       (double)((param_1 + param_1) *
                ((fVar17 + *(float *)(this->_padding_ + 0x17c)) - (float)*(double *)(iVar12 + 0x50))
               + (float)*(double *)(iVar12 + 0x50));
  local_4c = *(OrdnanceClass **)(this->_padding_ + 0x160);
  fVar17 = param_1 + this->shotTimer;
  this->shotTimer = fVar17;
  uVar16 = (ushort)(0.0 < fVar17) << 8 | (ushort)(fVar17 == 0.0) << 0xe;
  while( true ) {
    if ((POPCOUNT((char)(uVar16 >> 8)) & 1U) == 0) {
      return;
    }
    if ((int)(this->_padding_ ^ 0x33333333U) < local_4c->ammoCost) break;
    if ((*(char *)(this->_padding_ + 0x164) != '\0') && (this->go == (_gas_object *)0x0)) {
      InitGASCtrl((GAS_CTRL *)(local_48 + 0x14));
      local_24 = 0x801;
      InitGASPrep(&local_a8);
      local_a8.loopMode = 1;
      p_Var9 = StartGASEvent((char *)(this->_padding_ + 0x164),(_OBJ76 *)this->_padding_,
                             (GAS_CTRL *)(local_48 + 0x14),&local_a8);
      this->go = p_Var9;
    }
    VVar6.x = (float)this->_padding_;
    VVar6.y = (float)this->_padding_;
    VVar6.z = (float)this->_padding_;
    pMVar8 = Spinner((MAT_3D *)local_48,(MAT_3D *)(this->_padding_ + 0x20),VVar6,-this->shotTimer);
    fVar17 = (float)this->_padding_;
    iVar12 = this->_padding_;
    fVar3 = this->shotTimer;
    pMVar15 = &local_8c;
    for (iVar13 = 0x10; iVar13 != 0; iVar13 = iVar13 + -1) {
      pMVar15->right_x = pMVar8->right_x;
      pMVar8 = (MAT_3D *)&pMVar8->right_y;
      pMVar15 = (MAT_3D *)&pMVar15->right_y;
    }
    local_8c.posit_x = (double)((float)local_8c.posit_x - fVar17 * fVar3);
    local_8c.posit_y = (double)((float)local_8c.posit_y - (float)this->_padding_ * this->shotTimer);
    local_8c.posit_z = (double)((float)local_8c.posit_z - (float)this->_padding_ * this->shotTimer);
    Rand_Counter = Rand_Counter + 1U & 0xff;
    pMVar8 = Build_Pitch_Matrix((MAT_3D *)local_48,
                                *(float *)(iVar12 + 0x184) * Pseudo_Rand_Number[Rand_Counter]);
    pMVar15 = &local_e8;
    for (iVar12 = 0x10; iVar12 != 0; iVar12 = iVar12 + -1) {
      pMVar15->right_x = pMVar8->right_x;
      pMVar8 = (MAT_3D *)&pMVar8->right_y;
      pMVar15 = (MAT_3D *)&pMVar15->right_y;
    }
    pMVar8 = Matrix_Multiply((MAT_3D *)local_48,&local_e8,&local_8c);
    p_Var4 = (_OBJ76 *)this->_padding_;
    pMVar15 = &local_8c;
    for (iVar12 = 0x10; pOVar7 = local_4c, iVar12 != 0; iVar12 = iVar12 + -1) {
      pMVar15->right_x = pMVar8->right_x;
      pMVar8 = (MAT_3D *)&pMVar8->right_y;
      pMVar15 = (MAT_3D *)&pMVar15->right_y;
    }
    pOVar10 = OrdnanceClass::Build(local_4c,&local_8c,p_Var4);
    pOVar10->bSend = 0;
    uVar16 = *(ushort *)&(pOVar10->damage).field_0x8;
    uVar11 = (ushort)(this->dmg_player & 1) << 4;
    *(ushort *)&(pOVar10->damage).field_0x8 = uVar11 | uVar16 & 0xffef;
    uVar16 = (ushort)(this->dmg_remote & 1) << 5 | uVar11 | uVar16 & 0xffcf;
    *(ushort *)&(pOVar10->damage).field_0x8 = uVar16;
    *(ushort *)&(pOVar10->damage).field_0x8 =
         (*(short *)(this->_padding_ + 0x16) << 6 ^ uVar16) & 0x3c0 ^ uVar16;
    pOVar10->dt = this->shotTimer - param_1;
    this->shotTimer = this->shotTimer - *(float *)(this->_padding_ + 0x178);
    (**(code **)(this->_padding_ + 0x18))(-pOVar7->ammoCost);
    uVar16 = (ushort)(0.0 < this->shotTimer) << 8 | (ushort)(this->shotTimer == 0.0) << 0xe;
  }
  puVar1 = (uint *)(this->_padding_ + 0x14);
  *puVar1 = *puVar1 | 0x200;
  (**(code **)(this->_padding_ + 0x14))();
  return;
}
