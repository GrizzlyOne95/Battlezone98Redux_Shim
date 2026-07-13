/*
 * Entry: 0040dd02
 * Name: get_ring
 * Namespace: Global
 * Signature: RingState get_ring(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RingState __cdecl get_ring(float param_1)

{
  if (param_1 < 10.0) {
    return RING_0;
  }
  if (param_1 < 25.0) {
    return RING_1;
  }
  if (param_1 < 60.0) {
    return RING_2;
  }
  if (param_1 < 200.0) {
    return RING_3;
  }
  return RING_4;
}
