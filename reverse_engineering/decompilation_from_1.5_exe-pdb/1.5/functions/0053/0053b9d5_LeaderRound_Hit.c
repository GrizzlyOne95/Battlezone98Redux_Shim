/*
 * Entry: 0053b9d5
 * Name: LeaderRound::Hit
 * Namespace: LeaderRound
 * Signature: void Hit(LeaderRound * this, GameObject * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LeaderRound::Hit(LeaderRound *this,GameObject *param_1,VECTOR_3D *param_2)

{
  uint *puVar1;
  int iVar2;
  MAT_3D *pMVar3;
  int iVar4;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar5;
  MAT_3D local_c4;
  MAT_3D local_84;
  MAT_3D local_44;
  
  Bullet::Hit((Bullet *)this,param_1,param_2);
  if (param_1 != (GameObject *)0x0) {
    puVar1 = (uint *)(this->_padding_ + 0x14);
    *puVar1 = *puVar1 & 0xfffffdff;
    this->_padding_ = *(int *)(this->_padding_ + 0xb0);
    iVar2 = GameObject::GetHandle(param_1);
    this->hitObj = iVar2;
    pMVar3 = Matrix_Inverse(&local_44,unaff_EDI);
    iVar2 = this->_padding_;
    pMVar5 = &local_84;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      pMVar5->right_x = pMVar3->right_x;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
      pMVar5 = (MAT_3D *)&pMVar5->right_y;
    }
    pMVar3 = Matrix_Multiply(&local_c4,(MAT_3D *)(iVar2 + 0x20),&local_84);
    pMVar5 = &local_44;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      pMVar5->right_x = pMVar3->right_x;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
      pMVar5 = (MAT_3D *)&pMVar5->right_y;
    }
    pMVar3 = &local_44;
    pMVar5 = &this->offset;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      pMVar5->right_x = pMVar3->right_x;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
      pMVar5 = (MAT_3D *)&pMVar5->right_y;
    }
  }
  return;
}
