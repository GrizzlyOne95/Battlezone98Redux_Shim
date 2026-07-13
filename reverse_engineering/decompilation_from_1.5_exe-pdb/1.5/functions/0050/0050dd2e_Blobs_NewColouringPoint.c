/*
 * Entry: 0050dd2e
 * Name: Blobs_NewColouringPoint
 * Namespace: Global
 * Signature: _coloring_point * Blobs_NewColouringPoint(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_coloring_point * __cdecl Blobs_NewColouringPoint(void)

{
  _coloring_point *p_Var1;
  
  p_Var1 = point_head;
  if (point_head != (_coloring_point *)0x0) {
    point_head = point_head->next;
    return p_Var1;
  }
  p_Var1 = calloc(1,8);
  point_count = point_count + 1;
  return p_Var1;
}
