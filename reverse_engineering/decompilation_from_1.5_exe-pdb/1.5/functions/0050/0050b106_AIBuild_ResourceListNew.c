/*
 * Entry: 0050b106
 * Name: AIBuild_ResourceListNew
 * Namespace: Global
 * Signature: void AIBuild_ResourceListNew(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_ResourceListNew(void)

{
  resource_list[0] = C_Linked_List_New();
  resource_list[1] = C_Linked_List_New();
  Mapgrid_IterateOverlaysInPixelRect
            (AIBuild_ResourceListOverlayIteration,(void *)0x0,0,0,mapsizex * 0x18 + -1,
             mapsizey * 0x18 + -1);
  return;
}
