/*
 * Entry: 004aacce
 * Name: KickEnemys
 * Namespace: Global
 * Signature: void KickEnemys(Craft * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl KickEnemys(Craft *param_1)

{
  int *this;
  bool bVar1;
  int iVar2;
  GameObject *pGVar3;
  int iVar4;
  float *pfVar5;
  VECTOR_3D *pVVar6;
  uint uVar7;
  float *pfVar8;
  Range_Search_Results local_6c;
  VECTOR_3D local_40;
  VECTOR_3D local_34;
  VECTOR_3D local_28;
  VECTOR_3D local_1c;
  GameObject *local_10;
  int *local_c;
  MAT_3D *local_8;
  
  iVar2 = (**(code **)(param_1->_padding_ + 0x2c))();
  Range::Search(GameObject::objectRange,(double)*(float *)(iVar2 + 0x44),
                (double)*(float *)(iVar2 + 0x4c),(double)*(float *)(iVar2 + 0x50),
                (double)*(float *)(iVar2 + 0x58),&local_6c);
  if (local_6c.empty == false) {
    iVar2 = (**(code **)param_1->_padding_)();
    pfVar8 = (float *)(iVar2 + 0x114);
    local_8 = (MAT_3D *)(param_1->_padding_ + 0x20);
    while (bVar1 = Range_Search_Results::Get_Next_Object(&local_6c,&local_c), bVar1) {
      pGVar3 = GameObjectHandle::GetObj(*local_c);
      local_10 = pGVar3;
      if ((pGVar3 != (GameObject *)0x0) &&
         (bVar1 = GameObject::FriendP((GameObject *)param_1,pGVar3), !bVar1)) {
        this = &pGVar3->_padding_;
        iVar4 = (**(code **)*this)();
        if (((*(int *)(iVar4 + 0x28) == 1) ||
            ((iVar4 = (**(code **)*this)(), *(int *)(iVar4 + 0x28) == 6 ||
             (iVar4 = (**(code **)*this)(), *(int *)(iVar4 + 0x28) == 4)))) &&
           (((pGVar3->euler).v.y <= 10.0 &&
            (bVar1 = DistributedObject::IsRemote((DistributedObject *)this), !bVar1)))) {
          pfVar5 = (float *)(**(code **)(*this + 0xc))();
          local_1c.x = *pfVar5;
          local_1c.y = pfVar5[1];
          local_1c.z = pfVar5[2];
          pVVar6 = Vector_Untransform(&local_34,&local_1c,local_8);
          local_1c.x = pVVar6->x;
          local_1c.y = pVVar6->y;
          local_1c.z = pVVar6->z;
          if ((((*pfVar8 <= local_1c.x) && (local_1c.x <= *(float *)(iVar2 + 0x120))) &&
              (*(float *)(iVar2 + 0x118) <= local_1c.y)) &&
             (((local_1c.y <= *(float *)(iVar2 + 0x124) && (*(float *)(iVar2 + 0x11c) <= local_1c.z)
               ) && (local_1c.z <= *(float *)(iVar2 + 0x128))))) {
            uVar7 = (Rand_Counter + 1U & 0xff) + 1;
            Rand_Counter = uVar7 & 0xff;
            local_28.x = (((local_1c.x * 2.0 - *(float *)(iVar2 + 0x120)) - *pfVar8) * 15.0) /
                         (*(float *)(iVar2 + 0x120) - *pfVar8) +
                         *(float *)(&DAT_00c9021c + uVar7 * 4) * 5.0;
            local_28.y = 15.0;
            local_28.z = Pseudo_Rand_Number[Rand_Counter] * 5.0 +
                         (((local_1c.z * 2.0 - *(float *)(iVar2 + 0x128)) -
                          *(float *)(iVar2 + 0x11c)) * 15.0) /
                         (*(float *)(iVar2 + 0x128) - *(float *)(iVar2 + 0x11c));
            pVVar6 = Vector_Rotate(&local_40,&local_28,local_8);
            local_28.x = pVVar6->x;
            local_28.y = pVVar6->y;
            local_28.z = pVVar6->z;
            GameObject::SetVelocity(local_10,&local_28);
          }
        }
      }
    }
  }
  return;
}
