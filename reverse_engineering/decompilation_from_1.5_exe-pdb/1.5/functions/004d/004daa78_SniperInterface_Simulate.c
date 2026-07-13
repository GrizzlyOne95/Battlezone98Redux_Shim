/*
 * Entry: 004daa78
 * Name: SniperInterface::Simulate
 * Namespace: SniperInterface
 * Signature: void Simulate(SniperInterface * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SniperInterface::Simulate(SniperInterface *this,float param_1)

{
  int *piVar1;
  GameObject *pGVar2;
  char cVar3;
  int iVar4;
  Weapon *pWVar5;
  MAT_3D *pMVar6;
  MAT_3D *pMVar7;
  Carrier *this_00;
  MAT_3D local_90;
  MAT_3D local_50;
  uint local_10;
  Carrier *local_c;
  int local_8;
  
  pGVar2 = GameObject::userObject;
  if (GameObject::userObject != (GameObject *)0x0) {
    piVar1 = &GameObject::userObject->_padding_;
    iVar4 = (**(code **)*piVar1)();
    if (((*(int *)(iVar4 + 0x28) == 4) &&
        (cVar3 = (**(code **)(pGVar2->_padding_ + 100))(), cVar3 != '\0')) &&
       (this_00 = pGVar2->carrier, this_00 != (Carrier *)0x0)) {
      local_c = this_00;
      iVar4 = (**(code **)*piVar1)();
      local_8 = 0;
      this->soviet = *(char *)(iVar4 + 0xd4) == 's';
      local_10 = this_00->selected;
      do {
        if (((local_10 & 1 << ((byte)local_8 & 0x1f)) != 0) &&
           (pWVar5 = Carrier::GetWeapon(this_00,local_8), pWVar5->weaponClass->sig == 0x534e4950)) {
          pMVar6 = Matrix_Multiply(&local_90,&pWVar5->obj->transform,&pWVar5->M);
          pMVar7 = &local_50;
          for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
            pMVar7->right_x = pMVar6->right_x;
            pMVar6 = (MAT_3D *)&pMVar6->right_y;
            pMVar7 = (MAT_3D *)&pMVar7->right_y;
          }
          Camera_Set_Matrix(&this->camera,&local_50);
          this->enabled = true;
          this_00 = local_c;
        }
        local_8 = local_8 + 1;
      } while (local_8 < 5);
    }
  }
  return;
}
