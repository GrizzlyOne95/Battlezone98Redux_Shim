/*
 * Entry: 00539d15
 * Name: SniperShell::Hit
 * Namespace: SniperShell
 * Signature: void Hit(SniperShell * this, GameObject * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SniperShell::Hit(SniperShell *this,GameObject *param_1,VECTOR_3D *param_2)

{
  int *this_00;
  uint *puVar1;
  char cVar2;
  bool bVar3;
  ushort uVar4;
  int iVar5;
  MAT_3D *pMVar6;
  VECTOR_3D *pVVar7;
  _OBJ76 *p_Var8;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar9;
  MAT_3D local_a0;
  MAT_3D local_60;
  VECTOR_3D local_20;
  _OBJ76 *local_14;
  VECTOR_3D local_10;
  
  if ((param_1 != (GameObject *)0x0) &&
     (((iVar5 = Net_IsNetGame(), iVar5 == 0 ||
       (uVar4 = Net_GetMyPlayerID(), *(ushort *)&this->field_0x7c == uVar4)) &&
      (cVar2 = (**(code **)(param_1->_padding_ + 0x14))(), cVar2 != '\0')))) {
    local_14 = *(_OBJ76 **)(param_1[1]._padding_ + 0xf4);
    pMVar6 = Matrix_Inverse(&local_a0,unaff_EDI);
    p_Var8 = local_14;
    pMVar9 = &local_60;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      pMVar9->right_x = pMVar6->right_x;
      pMVar6 = (MAT_3D *)&pMVar6->right_y;
      pMVar9 = (MAT_3D *)&pMVar9->right_y;
    }
    pVVar7 = obj_get_world_position(&local_20,p_Var8);
    local_10.x = pVVar7->x;
    local_10.y = pVVar7->y;
    local_10.z = pVVar7->z;
    Vector_Transform(&local_10,&local_10,1,&local_60);
    if (0.0 < local_10.z) {
      iVar5 = *(int *)&this->field_0x10;
      local_10.x = local_10.x / *(float *)(iVar5 + 0x74);
      local_10.y = local_10.y / *(float *)(iVar5 + 0x74);
      local_10.z = local_10.z / *(float *)(iVar5 + 0x70);
      if (local_10.z * local_10.z + local_10.x * local_10.x + local_10.y * local_10.y < 1.0) {
        (**(code **)(param_1->_padding_ + 0x74))();
        this_00 = &param_1->_padding_;
        bVar3 = DistributedObject::IsRemote((DistributedObject *)this_00);
        if ((bVar3) && (*(int *)&this->field_0xcc != 0)) {
          Net::SendSnipe(*(GameObject **)(*(int *)&this->field_0xcc + 0xb4),param_1);
        }
        bVar3 = DistributedObject::IsLocal((DistributedObject *)this_00);
        if (bVar3) {
          p_Var8 = (_OBJ76 *)(**(code **)(*this_00 + 0x30))();
          iVar5 = dynamic_object(p_Var8);
          if (iVar5 != 0) {
            p_Var8 = (_OBJ76 *)(**(code **)(*this_00 + 0x30))();
            iVar5 = IsCraft(p_Var8);
            if ((iVar5 == 0) || (cVar2 = (**(code **)(param_1->_padding_ + 0x68))(), cVar2 != '\0'))
            {
              puVar1 = (uint *)(*(int *)&this->field_0x18 + 0x14);
              *puVar1 = *puVar1 | 2;
            }
          }
        }
        puVar1 = (uint *)(*(int *)&this->field_0x18 + 0x14);
        *puVar1 = *puVar1 | 0x200;
      }
    }
  }
  Bullet::Hit((Bullet *)this,param_1,param_2);
  return;
}
