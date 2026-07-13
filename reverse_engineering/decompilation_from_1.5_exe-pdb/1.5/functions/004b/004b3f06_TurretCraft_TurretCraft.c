/*
 * Entry: 004b3f06
 * Name: TurretCraft::TurretCraft
 * Namespace: TurretCraft
 * Signature: TurretCraft * TurretCraft(TurretCraft * this, _OBJ76 * param_1, TurretCraftClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TurretCraft * __thiscall
TurretCraft::TurretCraft(TurretCraft *this,_OBJ76 *param_1,TurretCraftClass *param_2)

{
  undefined1 (*pauVar1) [20];
  VECTOR_3D_LONG VVar2;
  undefined8 uVar3;
  MAT_3D *pMVar4;
  int iVar5;
  VECTOR_3D *unaff_ESI;
  float *pfVar6;
  VECTOR_3D *unaff_EDI;
  float *pfVar7;
  MAT_3D local_c0;
  float local_80 [16];
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  VECTOR_3D local_34;
  undefined8 local_28;
  undefined8 local_18;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  Craft::Craft((Craft *)this,param_1,(CraftClass *)param_2);
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  pauVar1 = (undefined1 (*) [20])(this->_padding_ + 0x48);
  local_28 = *(undefined8 *)*pauVar1;
  local_18 = *(undefined8 *)(this->_padding_ + 0x58);
  VVar2.z._4_4_ = (int)((ulonglong)local_18 >> 0x20);
  VVar2._0_20_ = *pauVar1;
  Floor_GetFloor(VVar2,(float *)&param_2,&local_34);
  iVar5 = this->_padding_;
  local_40 = *(undefined4 *)(iVar5 + 0x38);
  uStack_3c = *(undefined4 *)(iVar5 + 0x3c);
  uStack_38 = *(undefined4 *)(iVar5 + 0x40);
  local_10 = local_40;
  local_c = uStack_3c;
  local_8 = uStack_38;
  pMVar4 = Build_Orthogonal_Matrix(&local_c0,unaff_EDI,unaff_ESI);
  uVar3 = local_28;
  pfVar6 = local_80;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *pfVar6 = pMVar4->right_x;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
    pfVar6 = pfVar6 + 1;
  }
  pfVar6 = local_80;
  pfVar7 = (float *)(this->_padding_ + 0x20);
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *pfVar7 = *pfVar6;
    pfVar6 = pfVar6 + 1;
    pfVar7 = pfVar7 + 1;
  }
  *(undefined8 *)(this->_padding_ + 0x48) = uVar3;
  *(double *)(this->_padding_ + 0x50) = (double)(float)param_2;
  *(undefined8 *)(this->_padding_ + 0x58) = local_18;
  this->turretYObj = (_OBJ76 *)0x0;
  this->turretXCount = 0;
  FindTurret(this,(_OBJ76 *)this->_padding_);
  this->prevYaw = 0.0;
  this->powerSource = 0;
  this->_padding_ = 1;
  this->_padding_ = 0xf;
  this->_padding_ = 0;
  this->_padding_ = 0;
  this->_padding_ = 0;
  this->hazardTeam = 0;
  this->_padding_ = 2;
  return this;
}
