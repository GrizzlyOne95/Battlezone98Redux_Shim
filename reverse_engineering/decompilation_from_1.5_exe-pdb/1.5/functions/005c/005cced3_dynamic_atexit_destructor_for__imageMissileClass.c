/*
 * Entry: 005cced3
 * Name: `dynamic_atexit_destructor_for_'imageMissileClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'imageMissileClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__imageMissileClass__(void)

{
  imageMissileClass._0_4_ = &ImageMissileClass::_vftable_;
  MissileClass::~MissileClass((MissileClass *)&imageMissileClass);
  return;
}
