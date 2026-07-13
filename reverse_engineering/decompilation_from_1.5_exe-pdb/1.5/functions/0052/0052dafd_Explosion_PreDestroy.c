/*
 * Entry: 0052dafd
 * Name: Explosion::PreDestroy
 * Namespace: Explosion
 * Signature: void PreDestroy(Explosion * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Explosion::PreDestroy(Explosion *this)

{
  if (this->owner != (_OBJ76 *)0x0) {
    release_obj(this->owner,".\\fun3d\\Explosion.cpp");
    this->owner = (_OBJ76 *)0x0;
  }
  return;
}
