/*
 * Entry: 00487bb2
 * Name: Craft::UpdateWeaponAim
 * Namespace: Craft
 * Signature: void UpdateWeaponAim(Craft * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Craft::UpdateWeaponAim(Craft *this,float param_1)

{
  double dVar1;
  double dVar2;
  double dVar3;
  _OBJ76 *p_Var4;
  Weapon *pWVar5;
  int iVar6;
  int iVar7;
  MAT_3D *pMVar8;
  MAT_3D *pMVar9;
  
  iVar7 = 0;
  do {
    pWVar5 = Carrier::GetWeapon((Carrier *)this->_padding_,iVar7);
    if (pWVar5 != (Weapon *)0x0) {
      p_Var4 = pWVar5->obj;
      dVar1 = (p_Var4->transform).posit_x;
      dVar2 = (p_Var4->transform).posit_y;
      dVar3 = (p_Var4->transform).posit_z;
      pMVar8 = &Identity_Matrix;
      pMVar9 = &p_Var4->transform;
      for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
        pMVar9->right_x = pMVar8->right_x;
        pMVar8 = (MAT_3D *)&pMVar8->right_y;
        pMVar9 = (MAT_3D *)&pMVar9->right_y;
      }
      p_Var4 = pWVar5->obj;
      (p_Var4->transform).posit_x = dVar1;
      (p_Var4->transform).posit_y = dVar2;
      (p_Var4->transform).posit_z = dVar3;
    }
    iVar7 = iVar7 + 1;
  } while (iVar7 < 5);
  return;
}
