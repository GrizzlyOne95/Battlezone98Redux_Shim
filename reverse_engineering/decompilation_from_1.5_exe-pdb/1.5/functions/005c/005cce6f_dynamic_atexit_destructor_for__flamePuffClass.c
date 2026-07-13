/*
 * Entry: 005cce6f
 * Name: `dynamic_atexit_destructor_for_'flamePuffClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'flamePuffClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__flamePuffClass__(void)

{
  flamePuffClass._padding_ = (int)&FlamePuffClass::_vftable_;
  BulletClass::~BulletClass((BulletClass *)&flamePuffClass);
  return;
}
