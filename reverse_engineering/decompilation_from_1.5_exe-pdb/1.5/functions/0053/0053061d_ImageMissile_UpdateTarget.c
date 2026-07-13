/*
 * Entry: 0053061d
 * Name: ImageMissile::UpdateTarget
 * Namespace: ImageMissile
 * Signature: GameObject * UpdateTarget(ImageMissile * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall ImageMissile::UpdateTarget(ImageMissile *this)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObject::GetObj(*(int *)&this->field_0xe8);
  if (pGVar1 == (GameObject *)0x0) {
    *(undefined4 *)&this->field_0xe8 = 0;
  }
  else if ((pGVar1->obj->flags & 0x400) != 0) {
    *(undefined4 *)&this->field_0xe8 = 0;
    return (GameObject *)0x0;
  }
  return pGVar1;
}
