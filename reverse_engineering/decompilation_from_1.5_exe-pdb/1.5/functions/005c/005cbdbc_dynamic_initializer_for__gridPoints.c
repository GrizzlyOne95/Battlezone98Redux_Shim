/*
 * Entry: 005cbdbc
 * Name: `dynamic_initializer_for_'gridPoints''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'gridPoints''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__gridPoints__(void)

{
  std::vector<GridPoint,std::allocator<GridPoint>_>::vector<GridPoint,std::allocator<GridPoint>_>
            (&gridPoints);
  atexit(_dynamic_atexit_destructor_for__gridPoints__);
  return;
}
