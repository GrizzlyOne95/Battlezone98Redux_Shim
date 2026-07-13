/*
 * Entry: 004af8dd
 * Name: ScrapDropoff_Put
 * Namespace: Global
 * Signature: int ScrapDropoff_Put(VECTOR_3D * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ScrapDropoff_Put(VECTOR_3D *param_1,int param_2)

{
  GameObjectClass *this;
  ScrapDropoff *pSVar1;
  uint uVar2;
  int iVar3;
  DropoffInfo *pDVar4;
  MAT_3D *pMVar5;
  MAT_3D *pMVar6;
  float fVar7;
  MAT_3D local_44;
  
  this = GameObjectClass::Find(0x66666f706f7264);
  pMVar5 = &Identity_Matrix;
  pMVar6 = &local_44;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    pMVar6->right_x = pMVar5->right_x;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
    pMVar6 = (MAT_3D *)&pMVar6->right_y;
  }
  local_44.posit_x = (double)param_1->x;
  local_44.posit_z = (double)param_1->z;
  fVar7 = Terrain_FindFloor(local_44.posit_x,(double)param_1->z);
  local_44.posit_y = (double)fVar7;
  pSVar1 = (ScrapDropoff *)GameObjectClass::Build(this,&local_44,param_2,0,-1,(char *)0x0);
  iVar3 = Net_IsNetGame();
  if (iVar3 != 0) {
    DistributedObject::SetLocal((DistributedObject *)&pSVar1->field_0x20);
  }
  uVar2 = 0;
  pDVar4 = dropoffList;
  do {
    if (pDVar4->dropObj == pSVar1) {
      pDVar4->refCount = pDVar4->refCount + 1;
      return uVar2;
    }
    uVar2 = uVar2 + 1;
    pDVar4 = pDVar4 + 1;
  } while (uVar2 < 0x14);
  if (pSVar1 != (ScrapDropoff *)0x0) {
    (*(code *)**(undefined4 **)&pSVar1->field_0x0)();
  }
  return -1;
}
