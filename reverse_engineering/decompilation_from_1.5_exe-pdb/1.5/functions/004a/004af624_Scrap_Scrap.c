/*
 * Entry: 004af624
 * Name: Scrap::Scrap
 * Namespace: Scrap
 * Signature: Scrap * Scrap(Scrap * this, _OBJ76 * param_1, ScrapClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scrap * __thiscall Scrap::Scrap(Scrap *this,_OBJ76 *param_1,ScrapClass *param_2)

{
  int iVar1;
  VECTOR_3D_LONG VVar2;
  MAT_3D *pMVar3;
  int iVar4;
  VECTOR_3D *unaff_ESI;
  VECTOR_3D *unaff_EDI;
  float *pfVar5;
  MAT_3D local_84;
  undefined8 local_44;
  double local_3c;
  undefined8 local_34;
  VECTOR_3D local_2c;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  Scrap *local_8;
  
  local_8 = this;
  Building::Building((Building *)this,param_1,(BuildingClass *)param_2);
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  DeleteCollisionEntity((tagENTITY *)this->_padding_);
  param_2 = (ScrapClass *)this;
  std::vector<Scrap_*,std::allocator<Scrap_*>_>::push_back(&scrapList,(Scrap **)&param_2);
  updateScrap = true;
  iVar1 = this->_padding_;
  local_44 = *(undefined8 *)*(undefined1 (*) [20])(iVar1 + 0x48);
  local_3c = *(double *)(iVar1 + 0x50);
  local_34 = *(undefined8 *)(iVar1 + 0x58);
  VVar2.z._4_4_ = (int)((ulonglong)local_34 >> 0x20);
  VVar2._0_20_ = *(undefined1 (*) [20])(iVar1 + 0x48);
  Floor_GetFloor(VVar2,(float *)&param_1,&local_2c);
  local_3c = (double)(float)param_1;
  local_20 = *(undefined4 *)(iVar1 + 0x38);
  uStack_1c = *(undefined4 *)(iVar1 + 0x3c);
  uStack_18 = *(undefined4 *)(iVar1 + 0x40);
  local_14 = local_20;
  local_10 = uStack_1c;
  local_c = uStack_18;
  pMVar3 = Build_Orthogonal_Matrix(&local_84,unaff_EDI,unaff_ESI);
  pfVar5 = (float *)(iVar1 + 0x20);
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar5 = pMVar3->right_x;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
    pfVar5 = pfVar5 + 1;
  }
  *(undefined8 *)(iVar1 + 0x48) = local_44;
  *(double *)(iVar1 + 0x50) = local_3c;
  *(undefined8 *)(iVar1 + 0x58) = local_34;
  GameObject::UpdatePosition((GameObject *)local_8);
  return local_8;
}
