/*
 * Entry: 004eabdc
 * Name: Render_Entity_Cockpit
 * Namespace: Global
 * Signature: void Render_Entity_Cockpit(CAMERA * param_1, tagENTITY * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Render_Entity_Cockpit(CAMERA *param_1,tagENTITY *param_2)

{
  _OBJ76 *p_Var1;
  SORTING_LIST_ENTITY local_38;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  p_Var1 = param_2->obj76;
  if ((p_Var1 != (_OBJ76 *)0x0) &&
     (((UserProfilePtr->graphicDetail).cockpit != '\0' || (p_Var1->class_id == CLASS_ID_PERSON)))) {
    param_2->mergeNext = (tagENTITY *)0x0;
    param_2->mergePoly = (void *)0x0;
    param_2->mergeCount = 0;
    Get_Visible_Lights(param_1);
    local_10 = 0;
    local_c = 0;
    local_8 = 0;
    local_38.Camera_bSphere.radius = (param_2->bSphere).radius;
    local_38.Clip_Children = 0;
    local_38.Project_Polygons_Flag = 0;
    local_38.LOD = 0;
    local_38.Entity = param_2;
    local_38.lodFlags = 0x81 - (1 < (UserProfilePtr->graphicDetail).cockpit);
    local_38.Camera_bSphere.origin.x = 0.0;
    local_38.Camera_bSphere.origin.y = 0.0;
    local_38.Camera_bSphere.origin.z = 0.0;
    local_38.Obj = p_Var1;
    Render_CachedBSP_Entity(&local_38,param_1);
  }
  return;
}
