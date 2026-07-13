/*
 * Entry: 004101f9
 * Name: Collision_Trash_Range_Search_Structure
 * Namespace: Global
 * Signature: void Collision_Trash_Range_Search_Structure(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Collision_Trash_Range_Search_Structure(void)

{
  Range *pRVar1;
  
  pRVar1 = collision_range_search;
  if (collision_range_search != (Range *)0x0) {
    Range::~Range(collision_range_search);
    operator_delete(pRVar1);
  }
  collision_range_search = (Range *)0x0;
  return;
}
