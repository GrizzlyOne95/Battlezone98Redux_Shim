/*
 * Entry: 0047f377
 * Name: ArtifactClass::~ArtifactClass
 * Namespace: ArtifactClass
 * Signature: void ~ArtifactClass(ArtifactClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArtifactClass::~ArtifactClass(ArtifactClass *this)

{
  *(undefined ***)this = &_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  return;
}
