/*
 * Entry: 0053e68f
 * Name: Weapon::Weapon
 * Namespace: Weapon
 * Signature: Weapon * Weapon(Weapon * this, _OBJ76 * param_1, WeaponClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall Weapon::Weapon(Weapon *this,_OBJ76 *param_1,WeaponClass *param_2)

{
  WeaponClass *pWVar1;
  _OBJ76 *p_Var2;
  MAT_3D *pMVar3;
  int iVar4;
  float *pfVar5;
  MAT_3D *unaff_EDI;
  MAT_3D local_84;
  float local_44 [16];
  
  pWVar1 = param_2;
  p_Var2 = param_1;
  this->_padding_ = (int)&_vftable_;
  this->weaponClass = param_2;
  this->obj = param_1;
  param_1 = (_OBJ76 *)this;
  std::list<Weapon_*,std::allocator<Weapon_*>_>::push_back(&weaponList,(Weapon **)&param_1);
  this->ordnanceClass = pWVar1->ordnanceClass;
  p_Var2 = obj_get_parent(p_Var2);
  this->hard = p_Var2;
  p_Var2 = obj_get_root(p_Var2);
  this->owner = p_Var2;
  pMVar3 = obj_rel_parent_matrix(&local_84,this->hard,(_OBJ76 *)0x0);
  pfVar5 = local_44;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar5 = pMVar3->right_x;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
    pfVar5 = pfVar5 + 1;
  }
  pfVar5 = local_44;
  pMVar3 = &this->M;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar3->right_x = *pfVar5;
    pfVar5 = pfVar5 + 1;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  pMVar3 = Matrix_Inverse(&local_84,unaff_EDI);
  pfVar5 = local_44;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar5 = pMVar3->right_x;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
    pfVar5 = pfVar5 + 1;
  }
  pfVar5 = local_44;
  pMVar3 = &this->I;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar3->right_x = *pfVar5;
    pfVar5 = pfVar5 + 1;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  this->wpnReticle = param_2->wpnReticle;
  this->fLastTriggered = -1e+30;
  return this;
}
