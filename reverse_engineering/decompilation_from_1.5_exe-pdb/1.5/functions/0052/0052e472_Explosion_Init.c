/*
 * Entry: 0052e472
 * Name: Explosion::Init
 * Namespace: Explosion
 * Signature: void Init(Explosion * this, MAT_3D * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall Explosion::Init(Explosion *this,MAT_3D *param_1,_OBJ76 *param_2)

{
  undefined1 *puVar1;
  float fVar2;
  ExplosionClass *pEVar3;
  _OBJ76 *p_Var4;
  bool bVar5;
  ushort uVar6;
  GameObject *pGVar7;
  float *pfVar8;
  int iVar9;
  MAT_3D *pMVar10;
  GAS_PREP_INFO local_a0;
  float local_84;
  float fStack_80;
  float fStack_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  VECTOR_3D local_60;
  float local_54;
  int *local_50;
  float local_4c;
  float local_48;
  float local_44;
  _Const_iterator<1> local_40;
  _OBJ76 *local_38;
  Range_Search_Results local_34;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&local_74;
  local_38 = param_2;
  if (param_2 == (_OBJ76 *)0x0) {
    this->obj->flags = 0;
  }
  else {
    this->obj->flags = param_2->flags & 0xf0000;
  }
  pMVar10 = &this->obj->transform;
  for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
    pMVar10->right_x = param_1->right_x;
    param_1 = (MAT_3D *)&param_1->right_y;
    pMVar10 = (MAT_3D *)&pMVar10->right_y;
  }
  (this->obj->bSphere).origin.x = 0.0;
  (this->obj->bSphere).origin.y = 0.0;
  (this->obj->bSphere).origin.z = 0.0;
  (this->obj->bSphere).radius = this->explosionClass->explRadius;
  pEVar3 = this->explosionClass;
  iVar9 = pEVar3->frameIndex;
  this->frameIndex = (float)iVar9;
  this->frameLimit = ((float)iVar9 + (float)pEVar3->frameCount) - 1.0;
  if (pEVar3->explSound[0] != '\0') {
    InitGASCtrl((GAS_CTRL *)&local_34);
    local_34.z0 = 0x1800;
    InitGASPrep(&local_a0);
    local_a0.pri = 0x32;
    StartGASEvent(this->explosionClass->explSound,this->obj,(GAS_CTRL *)&local_34,&local_a0);
  }
  this->owner = local_38;
  (this->damage).damager = (_OBJ76 *)0x0;
  (this->damage).dmg_source = (_OBJ76 *)0x0;
  *(undefined4 *)&(this->damage).field_0x8 = 0;
  (this->damage).dmg_value = 0.0;
  p_Var4 = this->obj;
  (this->damage).dmg_source = p_Var4;
  (this->damage).damager = local_38;
  uVar6 = (*(short *)((int)&p_Var4->flags + 2) << 6 ^ *(ushort *)&(this->damage).field_0x8) & 0x3c0
          ^ *(ushort *)&(this->damage).field_0x8;
  *(ushort *)&(this->damage).field_0x8 = uVar6;
  if (local_38 != (_OBJ76 *)0x0) {
    *(ushort *)&(this->damage).field_0x8 =
         ((ushort)((local_38->flags & 0x30) != 0) << 4 ^ uVar6) & 0x10 ^ uVar6;
    if (local_38->gameObj != (void *)0x0) {
      bVar5 = DistributedObject::IsRemote((DistributedObject *)((int)local_38->gameObj + 0x20));
      *(ushort *)&(this->damage).field_0x8 =
           (ushort)bVar5 << 5 | *(ushort *)&(this->damage).field_0x8 & 0xffdf;
    }
  }
  pEVar3 = this->explosionClass;
  puVar1 = &(this->damage).field_0x8;
  *(ushort *)puVar1 =
       *(ushort *)puVar1 ^ (pEVar3->damageTypes ^ *(ushort *)&(this->damage).field_0x8) & 0xf;
  (this->damage).dmg_value = pEVar3->damageValue;
  fVar2 = pEVar3->omegaShake;
  this->omegaShake = fVar2;
  this->deltaShake = (fVar2 * pEVar3->frameRate) / (float)pEVar3->frameCount;
  i_got_dibs_on_obj(local_38,".\\fun3d\\Explosion.cpp");
  pEVar3 = this->explosionClass;
  if (0.0 < pEVar3->damageRadius) {
    p_Var4 = this->obj;
    local_38 = (_OBJ76 *)(pEVar3->damageRadius * pEVar3->damageRadius);
    local_60.x = (p_Var4->bSphere).origin.x;
    local_60.y = (p_Var4->bSphere).origin.y;
    local_54 = pEVar3->explRadius * pEVar3->explRadius;
    local_60.z = (p_Var4->bSphere).origin.z;
    Vector_Transform(&local_60,&local_60,1,&p_Var4->transform);
    Range::Search(GameObject::objectRange,(double)local_60.x,(double)local_60.z,
                  (double)this->explosionClass->damageRadius,&local_34);
    while (bVar5 = Range_Search_Results::Get_Next_Object(&local_34,(int **)&local_40._Ptr), bVar5) {
      pGVar7 = GameObject::GetObj((int)(local_40._Ptr)->_Next);
      if (pGVar7 != (GameObject *)0x0) {
        local_78 = local_60.x;
        local_74 = local_60.y;
        local_50 = &pGVar7->_padding_;
        local_70 = local_60.z;
        pfVar8 = (float *)(**(code **)(*local_50 + 0xc))();
        local_6c = *pfVar8;
        local_68 = pfVar8[1];
        local_64 = pfVar8[2];
        local_84 = local_6c - local_78;
        fStack_80 = local_68 - local_74;
        fStack_7c = local_64 - local_70;
        fVar2 = local_84 * local_84 + fStack_7c * fStack_7c + fStack_80 * fStack_80;
        local_4c = local_84;
        local_48 = fStack_80;
        local_44 = fStack_7c;
        if (local_54 <= fVar2) {
          if (fVar2 < (float)local_38) {
            local_a0.loopMode = (long)(this->damage).damager;
            local_a0.volume = (long)(this->damage).dmg_source;
            local_a0.random = *(long *)&(this->damage).field_0x8;
            local_a0.sampleRate =
                 (long)((((float)local_38 - fVar2) / ((float)local_38 - local_54)) *
                       (this->damage).dmg_value);
            (**(code **)(*local_50 + 0x38))();
          }
        }
        else {
          (**(code **)(*local_50 + 0x38))();
        }
      }
    }
  }
  local_40._Ptr = (_Node *)this;
  std::list<Explosion_*,std::allocator<Explosion_*>_>::push_front
            (&explosionList,(Explosion **)&local_40._Ptr);
  std::list<Explosion_*,std::allocator<Explosion_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_40,(explosionList._Myhead)->_Next,&explosionList);
  *(int *)&this->me = local_40._padding_;
  *(_Node **)&(this->me).field_0x4 = local_40._Ptr;
  return;
}
