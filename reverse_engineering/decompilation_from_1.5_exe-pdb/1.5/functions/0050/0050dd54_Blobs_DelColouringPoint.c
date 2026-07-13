/*
 * Entry: 0050dd54
 * Name: Blobs_DelColouringPoint
 * Namespace: Global
 * Signature: void Blobs_DelColouringPoint(_coloring_point * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Blobs_DelColouringPoint(_coloring_point *param_1)

{
  _coloring_point *in_EAX;
  
  in_EAX->next = point_head;
  point_head = in_EAX;
  return;
}
