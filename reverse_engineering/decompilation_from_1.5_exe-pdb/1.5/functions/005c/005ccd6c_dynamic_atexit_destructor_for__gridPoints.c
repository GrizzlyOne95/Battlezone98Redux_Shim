/*
 * Entry: 005ccd6c
 * Name: `dynamic_atexit_destructor_for_'gridPoints''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'gridPoints''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__gridPoints__(void)

{
  std::vector<GridPoint,std::allocator<GridPoint>_>::_Tidy(&gridPoints);
  operator_delete((void *)gridPoints._padding_);
  return;
}
