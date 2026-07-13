/*
 * Entry: 005cbcd8
 * Name: `dynamic_initializer_for_'targeting''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'targeting''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__targeting__(void)

{
  Targeting::Targeting(&targeting);
  atexit(_dynamic_atexit_destructor_for__targeting__);
  return;
}
