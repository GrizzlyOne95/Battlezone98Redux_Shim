/*
 * Entry: 0053bc14
 * Name: TeamSwitcher::Simulate
 * Namespace: TeamSwitcher
 * Signature: void Simulate(TeamSwitcher * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TeamSwitcher::Simulate(TeamSwitcher *this,float param_1)

{
  uint *puVar1;
  float fVar2;
  int *piVar3;
  GameObject *pGVar4;
  int iVar5;
  MAT_3D *pMVar6;
  long lVar7;
  float *pfVar8;
  float *pfVar9;
  MAT_3D local_88;
  float local_48 [16];
  int *local_8;
  
  if (this->hitObj == 0) {
    Rocket::Simulate((Rocket *)this,param_1);
  }
  else {
    pGVar4 = GameObject::GetObj(this->hitObj);
    if (pGVar4 != (GameObject *)0x0) {
      local_8 = &pGVar4->_padding_;
      iVar5 = (**(code **)(*local_8 + 4))();
      if ((-1 < iVar5) && ((pGVar4->obj->flags & 0x200) == 0)) {
        pMVar6 = Matrix_Multiply(&local_88,&this->offset,&pGVar4->obj->transform);
        pfVar8 = local_48;
        for (iVar5 = 0x10; piVar3 = local_8, iVar5 != 0; iVar5 = iVar5 + -1) {
          *pfVar8 = pMVar6->right_x;
          pMVar6 = (MAT_3D *)&pMVar6->right_y;
          pfVar8 = pfVar8 + 1;
        }
        pfVar8 = local_48;
        pfVar9 = (float *)(this->_padding_ + 0x20);
        for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
          *pfVar9 = *pfVar8;
          pfVar8 = pfVar8 + 1;
          pfVar9 = pfVar9 + 1;
        }
        iVar5 = (**(code **)(*local_8 + 4))();
        if (iVar5 != this->myTeam) {
          lVar7 = (**(code **)(*piVar3 + 4))();
          this->savedTeam = lVar7;
          (**(code **)(*piVar3 + 8))(this->myTeam);
        }
        fVar2 = (float)this->_padding_ - param_1;
        this->_padding_ = (int)fVar2;
        if (0.0 < fVar2) {
          puVar1 = (uint *)(this->_padding_ + 0x14);
          *puVar1 = *puVar1 & 0xfffffdff;
          return;
        }
        (**(code **)(*piVar3 + 8))(this->savedTeam);
      }
    }
    puVar1 = (uint *)(this->_padding_ + 0x14);
    *puVar1 = *puVar1 | 0x200;
  }
  return;
}
