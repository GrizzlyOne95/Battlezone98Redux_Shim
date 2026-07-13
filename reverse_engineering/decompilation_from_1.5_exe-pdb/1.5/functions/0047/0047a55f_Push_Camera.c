/*
 * Entry: 0047a55f
 * Name: Push_Camera
 * Namespace: Global
 * Signature: int Push_Camera(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Push_Camera(void)

{
  int iVar1;
  PRESET_VIEW *pPVar2;
  PRESET_VIEW *pPVar3;
  
  if (Camera_Stack_Index < 1) {
    return 0;
  }
  Camera_Stack_Index = Camera_Stack_Index + -1;
  pPVar2 = &View_Record;
  pPVar3 = Camera_Stack + Camera_Stack_Index;
  for (iVar1 = 0x8e; iVar1 != 0; iVar1 = iVar1 + -1) {
    pPVar3->Update_Camera = pPVar2->Update_Camera;
    pPVar2 = (PRESET_VIEW *)&pPVar2->Intenal_View;
    pPVar3 = (PRESET_VIEW *)&pPVar3->Intenal_View;
  }
  return 1;
}
