/*
 * Entry: 005cc85e
 * Name: `dynamic_atexit_destructor_for_'artifactClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'artifactClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__artifactClass__(void)

{
  artifactClass._0_4_ = &ArtifactClass::_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)&artifactClass);
  return;
}
