/*
 * Entry: 0047a5d6
 * Name: Switch_View_Camera_Owner
 * Namespace: Global
 * Signature: void Switch_View_Camera_Owner(tagENTITY * param_1, tagENTITY * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Switch_View_Camera_Owner(tagENTITY *param_1,tagENTITY *param_2)

{
  tagENTITY **pptVar1;
  
  if (View_Record.Camera_Owner == param_1) {
    View_Record.Camera_Owner = param_2;
  }
  if (Camera_Stack_Index < 8) {
    pptVar1 = &Camera_Stack[Camera_Stack_Index].Camera_Owner;
    do {
      if (*pptVar1 == param_1) {
        *pptVar1 = param_2;
      }
      pptVar1 = pptVar1 + 0x8e;
    } while ((int)pptVar1 < 0xd424e8);
  }
  return;
}
