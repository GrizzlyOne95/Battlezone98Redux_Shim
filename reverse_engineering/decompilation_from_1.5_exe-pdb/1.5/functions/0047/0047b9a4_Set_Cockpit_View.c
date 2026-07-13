/*
 * Entry: 0047b9a4
 * Name: Set_Cockpit_View
 * Namespace: Global
 * Signature: void Set_Cockpit_View(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Set_Cockpit_View(void)

{
  _OBJ76 *p_Var1;
  tagENTITY *ptVar2;
  VEHICLE *pVVar3;
  MAT_3D *pMVar4;
  int iVar5;
  MAT_3D *pMVar6;
  float fVar7;
  MAT_3D local_84;
  MAT_3D local_44;
  
  TimeStepLocal();
  ptVar2 = Get_Camera_Owner();
  if (ptVar2 == (tagENTITY *)0x0) {
    return;
  }
  if (ptVar2->obj76 == (_OBJ76 *)0x0) {
    return;
  }
  if (ptVar2 != prevEntity) {
    prevEntity = ptVar2;
    Apply_Cockpit_View(ptVar2);
  }
  pVVar3 = get_obj_vhcl(ptVar2->obj76);
  if (pVVar3 == (VEHICLE *)0x0) {
    return;
  }
  p_Var1 = pVVar3->eyepoint;
  if (p_Var1 == (_OBJ76 *)0x0) {
    return;
  }
  if ((p_Var1->objHandle).handle == 0) {
    return;
  }
  pMVar4 = obj_rel_parent_matrix(&local_84,p_Var1,(_OBJ76 *)0x0);
  pMVar6 = &local_44;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    pMVar6->right_x = pMVar4->right_x;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
    pMVar6 = (MAT_3D *)&pMVar6->right_y;
  }
  Camera_Set_Matrix(&View_Record.MainCam,&local_44);
  if (eye_controls.zoom_factor_reset == '\0') {
    if (eye_controls.zoom_factor_plus == '\0') {
      if (eye_controls.zoom_factor_minus == '\0') goto LAB_0047bab1;
      fVar7 = TimeStep();
      cockpit_zoom = cockpit_zoom - fVar7 * cockpit_zoom * 0.5;
      fVar7 = 1.0;
      if (1.0 <= cockpit_zoom) goto LAB_0047bab1;
    }
    else {
      fVar7 = TimeStep();
      cockpit_zoom = (fVar7 * 0.5 + 1.0) * cockpit_zoom;
      fVar7 = 10.0;
      if (cockpit_zoom <= 10.0) goto LAB_0047bab1;
    }
  }
  else {
    fVar7 = 1.0;
  }
  cockpit_zoom = fVar7;
LAB_0047bab1:
  if (cockpit_zoom != View_Record.MainCam.Zoom_Factor) {
    Camera_Set_Zoom(&View_Record.MainCam,cockpit_zoom);
  }
  return;
}
