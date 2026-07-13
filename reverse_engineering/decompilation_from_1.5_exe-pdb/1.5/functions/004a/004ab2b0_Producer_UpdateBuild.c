/*
 * Entry: 004ab2b0
 * Name: Producer::UpdateBuild
 * Namespace: Producer
 * Signature: void UpdateBuild(Producer * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Producer::UpdateBuild(Producer *this,float param_1)

{
  int iVar1;
  SPHERE *pSVar2;
  float fVar3;
  MAT_3D local_54;
  SPHERE local_14;
  
  fVar3 = this->buildDoneTime - param_1;
  this->buildDoneTime = fVar3;
  if (0.0 <= fVar3) {
    iVar1 = ModeList::FindMode((ModeList *)&this->_padding_,(int)this->buildClass);
    this->_padding_ = iVar1;
    (**(code **)(this->_padding_ + 0xa8))(&local_54);
    pSVar2 = GameObjectClass::GetBoundingSphere(this->buildClass);
    local_14.origin.x = (pSVar2->origin).x;
    local_14.origin.y = (pSVar2->origin).y;
    local_14.origin.z = (pSVar2->origin).z;
    local_14.radius = pSVar2->radius;
    Vector_Transform(&local_14.origin,&local_14.origin,1,&local_54);
    fVar3 = Min(this->buildDoneTime / this->buildClass->buildTime,1.0);
    ConstructionBlob::AddBlob(&constructionBlob,&local_14,fVar3);
  }
  else {
    (**(code **)(this->_padding_ + 0xa4))();
  }
  return;
}
