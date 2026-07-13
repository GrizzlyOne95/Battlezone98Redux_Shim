/*
 * Entry: 00537191
 * Name: QuakeBlast::Init
 * Namespace: QuakeBlast
 * Signature: void Init(QuakeBlast * this, MAT_3D * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall QuakeBlast::Init(QuakeBlast *this,MAT_3D *param_1,_OBJ76 *param_2)

{
  MAT_3D *pMVar1;
  Ordnance *pOVar2;
  MAT_3D *pMVar3;
  int iVar4;
  MAT_3D *pMVar5;
  MAT_3D local_c8;
  MAT_3D local_88;
  MAT_3D local_48;
  OrdnanceClass *local_8;
  
  Explosion::Init((Explosion *)this,param_1,param_2);
  pMVar3 = *(MAT_3D **)(this->_padding_ + 0x68);
  local_8 = *(OrdnanceClass **)(this->_padding_ + 0x6c);
  pMVar1 = &local_48;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar1->right_x = param_1->right_x;
    param_1 = (MAT_3D *)&param_1->right_y;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
  }
  pMVar1 = Build_Yaw_Matrix(&local_c8,6.2831855 / (float)(int)pMVar3);
  pMVar5 = &local_88;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar5->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
  }
  param_1 = pMVar3;
  if (0 < (int)pMVar3) {
    do {
      pOVar2 = OrdnanceClass::Build(local_8,&local_48,param_2);
      pOVar2->bSend = 0;
      pMVar3 = Matrix_Multiply(&local_c8,&local_88,&local_48);
      param_1 = (MAT_3D *)((int)&param_1[-1].posit_z + 7);
      pMVar1 = &local_48;
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        pMVar1->right_x = pMVar3->right_x;
        pMVar3 = (MAT_3D *)&pMVar3->right_y;
        pMVar1 = (MAT_3D *)&pMVar1->right_y;
      }
    } while (param_1 != (MAT_3D *)0x0);
  }
  this->magnitude = 5.0;
  this->dropoff =
       (*(float *)(this->_padding_ + 0x38) * 5.0) / (float)*(int *)(this->_padding_ + 0x34);
  EarthQuake::StartQuake(&earthQuake,5.0);
  return;
}
