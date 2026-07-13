/*
 * Entry: 0049b1ef
 * Name: Geom_Dump
 * Namespace: Global
 * Signature: void Geom_Dump(_GEOMETRY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Geom_Dump(_GEOMETRY *param_1)

{
  FACE *pFVar1;
  int iVar2;
  
  DEBUG_setOutputMethod(4);
  DEBUG_setLogFileName("objtest.txt");
  DEBUG_openLogFile();
  DEBUG_printf("Geometry object at %x:\n\n");
  DEBUG_printf("References:\t\t%d\n");
  DEBUG_printf("Number of vertices:\t%d\n");
  DEBUG_printf("Number of normals:\t%d\n\n");
  DEBUG_printf("Vertex list:\n\n");
  iVar2 = 0;
  if (0 < param_1->vertex_count) {
    do {
      DEBUG_printf("Vertex # %d:\t\t(%f, %f, %f)\n");
      iVar2 = iVar2 + 1;
    } while (iVar2 < param_1->vertex_count);
  }
  DEBUG_printf("\n");
  DEBUG_printf("Normal list:\n\n");
  iVar2 = 0;
  if (0 < param_1->normal_count) {
    do {
      DEBUG_printf("Normal # %d:\t\t(%f, %f, %f)\n");
      iVar2 = iVar2 + 1;
    } while (iVar2 < param_1->normal_count);
  }
  DEBUG_printf("\n");
  for (pFVar1 = param_1->faces; pFVar1 != (FACE *)0x0; pFVar1 = pFVar1->front_facet) {
    DEBUG_printf("Face # %d:\t\tVertices:\t");
    param_1 = (_GEOMETRY *)0x0;
    if (0 < pFVar1->vertex_count) {
      do {
        DEBUG_printf("%3d ");
        param_1 = (_GEOMETRY *)((int)&param_1->cache_info + 1);
      } while ((int)param_1 < pFVar1->vertex_count);
    }
    DEBUG_printf("\n");
  }
  DEBUG_printf("\n");
  return;
}
