/*
 * Entry: 005cc8c5
 * Name: `dynamic_atexit_destructor_for_'cameraPodClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'cameraPodClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__cameraPodClass__(void)

{
  cameraPodClass._padding_ = (int)&CameraPodClass::_vftable_;
  PowerUpClass::~PowerUpClass((PowerUpClass *)&cameraPodClass);
  return;
}
