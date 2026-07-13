/*
 * Entry: 00410179
 * Name: Collision_Create_Range_Search_Structure
 * Namespace: Global
 * Signature: void Collision_Create_Range_Search_Structure(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Collision_Create_Range_Search_Structure(void)

{
  Range *this;
  
  this = operator_new(0x40);
  if (this != (Range *)0x0) {
    collision_range_search =
         Range::Range(this,(double)GRID_X_SIZE,(double)GRID_Z_SIZE,(double)grid_rect.top,
                      (double)grid_rect.bottom,(double)grid_rect.left,(double)grid_rect.right,0x300)
    ;
    return;
  }
  collision_range_search = (Range *)0x0;
  return;
}
