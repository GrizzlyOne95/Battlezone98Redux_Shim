/*
 * Entry: 0053d56e
 * Name: Torpedo::Explode
 * Namespace: Torpedo
 * Signature: void Explode(Torpedo * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Torpedo::Explode(Torpedo *this)

{
  uint *puVar1;
  int iVar2;
  GameObject *pGVar3;
  _OBJ76 *p_Var4;
  int iVar5;
  float *pfVar6;
  MAT_3D *pMVar7;
  float fVar8;
  MAT_3D local_48;
  ExplosionClass *local_8;
  
  puVar1 = (uint *)(this->_padding_ + 0x14);
  *puVar1 = *puVar1 | 0x200;
  local_8 = *(ExplosionClass **)(this->_padding_ + 0x198);
  iVar2 = this->_padding_;
  pfVar6 = (float *)(this->_padding_ + 0x20);
  pMVar7 = &local_48;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    pMVar7->right_x = *pfVar6;
    pfVar6 = pfVar6 + 1;
    pMVar7 = (MAT_3D *)&pMVar7->right_y;
  }
  pGVar3 = GameObject::GetObj(iVar2);
  if (pGVar3 == (GameObject *)0x0) {
    p_Var4 = (_OBJ76 *)0x0;
  }
  else {
    p_Var4 = (_OBJ76 *)(**(code **)(pGVar3->_padding_ + 0x30))();
  }
  ExplosionClass::Build(local_8,&local_48,p_Var4);
  fVar8 = Terrain_FindFloor(local_48.posit_x,local_48.posit_z);
  if ((float)local_48.posit_y < fVar8 + 5.0) {
    MakeCrater((float)local_48.posit_x,(float)local_48.posit_z,5.0);
  }
  (**(code **)(this->_padding_ + 0x10))();
  return;
}
