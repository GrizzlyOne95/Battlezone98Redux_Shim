/*
 * Entry: 0048566d
 * Name: ConstructionRig::UpdateUnbuild
 * Namespace: ConstructionRig
 * Signature: void UpdateUnbuild(ConstructionRig * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ConstructionRig::UpdateUnbuild(ConstructionRig *this,float param_1)

{
  float fVar1;
  SPHERE *pSVar2;
  SPHERE local_18;
  GameObject *local_8;
  
  local_8 = GameObjectHandle::GetObj(this->unbuildHandle);
  if (local_8 == (GameObject *)0x0) {
    Producer::CancelBuild((Producer *)this);
  }
  else {
    fVar1 = (float)this->_padding_ - param_1;
    this->_padding_ = (int)fVar1;
    if (0.0 <= fVar1) {
      pSVar2 = GameObject::GetSphere(local_8);
      local_18.origin.x = (pSVar2->origin).x;
      local_18.origin.y = (pSVar2->origin).y;
      local_18.origin.z = (pSVar2->origin).z;
      local_18.radius = pSVar2->radius;
      Vector_Transform(&local_18.origin,&local_18.origin,1,&local_8->obj->transform);
      ConstructionBlob::AddBlob
                (&constructionBlob,&local_18,(float)this->_padding_ / this->dropClass->buildTime);
    }
    else {
      FinishUnbuild(this,local_8);
    }
  }
  return;
}
