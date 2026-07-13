/*
 * Entry: 00537689
 * Name: RadarLauncher::Simulate
 * Namespace: RadarLauncher
 * Signature: void Simulate(RadarLauncher * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall RadarLauncher::Simulate(RadarLauncher *this,float param_1)

{
  GameObjectClass *pGVar1;
  GameObject *this_00;
  bool bVar2;
  int iVar3;
  MAT_3D *pMVar4;
  AiMission *pAVar5;
  GameObject *pGVar6;
  int iVar7;
  float *pfVar8;
  int iVar9;
  char *pcVar10;
  MAT_3D local_b4;
  GAS_PREP_INFO local_74;
  VECTOR_3D local_58;
  GameObject *local_4c;
  undefined1 local_48 [24];
  float local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  *(float *)&this->field_0xa8 = param_1 + *(float *)&this->field_0xa8;
  if (((*(int *)&this->field_0xcc == 0) || (this->field_0xc8 != '\0')) ||
     (bVar2 = Weapon::PermissionToFire((Weapon *)this), !bVar2)) {
    if (0.0 < *(float *)&this->field_0xa8) {
      *(undefined4 *)&this->field_0xa8 = 0;
    }
  }
  else if (0.0 < *(float *)&this->field_0xa8) {
    pGVar1 = *(GameObjectClass **)&this->field_0xc;
    if (*(int *)(*(int *)&this->field_0x8 + 0x78) <=
        (int)(*(uint *)(*(int *)&this->field_0xc0 + 0x208) ^ 0x33333333)) {
      local_4c = (GameObject *)pGVar1;
      if (*(char *)(*(int *)&this->field_0x8 + 0x58) != '\0') {
        InitGASCtrl((GAS_CTRL *)(local_48 + 0x14));
        local_24 = 0x800;
        InitGASPrep(&local_74);
        StartGASEvent((char *)(*(int *)&this->field_0x8 + 0x58),*(_OBJ76 **)&this->field_0x10,
                      (GAS_CTRL *)(local_48 + 0x14),&local_74);
      }
      (**(code **)(**(int **)&this->field_0xc0 + 0x18))(-pGVar1->maxAmmo);
      iVar3 = Net_IsNetGame();
      if ((iVar3 == 0) ||
         (bVar2 = DistributedObject::IsLocal
                            ((DistributedObject *)(*(int *)&this->field_0xc0 + 0x20)), bVar2)) {
        pMVar4 = Matrix_Multiply(&local_b4,(MAT_3D *)(*(int *)&this->field_0x10 + 0x20),
                                 (MAT_3D *)&this->field_0x20);
        iVar3 = *(int *)&this->field_0xc0;
        pfVar8 = (float *)local_48;
        for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
          *pfVar8 = pMVar4->right_x;
          pMVar4 = (MAT_3D *)&pMVar4->right_y;
          pfVar8 = pfVar8 + 1;
        }
        local_20 = (double)(local_30 + (float)local_20);
        local_18 = (double)(local_30 + (float)local_18);
        pcVar10 = (char *)0x0;
        iVar9 = -1;
        local_10 = (double)(local_30 + (float)local_10);
        iVar7 = 0;
        iVar3 = (**(code **)(*(int *)(iVar3 + 0x20) + 4))();
        local_4c = GameObjectClass::Build
                             ((GameObjectClass *)local_4c,(MAT_3D *)local_48,iVar3,iVar7,iVar9,
                              pcVar10);
        iVar3 = *(int *)&this->field_0xc0;
        local_58.x = local_30 * 20.0 + *(float *)(iVar3 + 0x120);
        local_58.y = local_2c * 20.0 + *(float *)(iVar3 + 0x124);
        local_58.z = local_28 * 20.0 + *(float *)(iVar3 + 0x128);
        GameObject::SetVelocity(local_4c,&local_58);
        pAVar5 = AiMission::GetCurrent();
        this_00 = local_4c;
        (**(code **)(pAVar5->_padding_ + 0x18))(local_4c);
        pGVar6 = GameObject::GetObj(*(int *)&this->field_0xcc);
        GameObject::SetTarget(this_00,pGVar6);
        GameObject::SetOwner(this_00,*(GameObject **)&this->field_0xc0);
        GameObject::SetTarget(*(GameObject **)&this->field_0xc0,this_00);
        iVar3 = Net_IsNetGame();
        if (iVar3 != 0) {
          DistributedObject::SetLocal((DistributedObject *)&this_00->_padding_);
        }
      }
    }
    *(undefined4 *)&this->field_0xcc = 0;
    *(undefined4 *)&this->field_0xac = 0;
    *(undefined4 *)&this->field_0xb8 = 0;
    *(float *)&this->field_0xa8 =
         *(float *)&this->field_0xa8 - *(float *)(*(int *)&this->field_0x8 + 0x80);
  }
  this->field_0xc8 = 0;
  return;
}
