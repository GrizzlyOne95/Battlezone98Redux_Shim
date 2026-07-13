/*
 * Entry: 00526338
 * Name: Clear_Road
 * Namespace: Global
 * Signature: void Clear_Road(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Clear_Road(void)

{
  ROAD_INFO *pRVar1;
  ROAD_INFO *_Memory;
  
  pRVar1 = RoadList;
  while (_Memory = pRVar1, _Memory != (ROAD_INFO *)0x0) {
    pRVar1 = _Memory->next;
    if (hDefaultHeap != (void *)0x0) {
      free(_Memory);
    }
  }
  RoadList = (ROAD_INFO *)0x0;
  return;
}
