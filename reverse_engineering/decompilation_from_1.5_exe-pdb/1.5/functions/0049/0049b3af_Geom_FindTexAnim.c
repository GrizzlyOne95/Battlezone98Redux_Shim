/*
 * Entry: 0049b3af
 * Name: Geom_FindTexAnim
 * Namespace: Global
 * Signature: char * Geom_FindTexAnim(_OBJ76 * param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl Geom_FindTexAnim(_OBJ76 *param_1,ulong param_2)

{
  int iVar1;
  FACE *pFVar2;
  
  GeoCache_SelectLOD(param_1,param_2);
  if (param_1->geom != (_GEOMETRY *)0x0) {
    for (pFVar2 = param_1->geom->faces; pFVar2 != (FACE *)0x0; pFVar2 = pFVar2->front_facet) {
      if (pFVar2->texture_name[0] != '\0') {
        iVar1 = IS_TEXTABLE(pFVar2->texture_name);
        if (iVar1 != 0) {
          return pFVar2->texture_name;
        }
      }
    }
  }
  return (char *)0x0;
}
