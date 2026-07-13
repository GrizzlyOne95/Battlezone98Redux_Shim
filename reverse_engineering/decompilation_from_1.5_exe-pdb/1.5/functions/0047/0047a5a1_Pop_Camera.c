/*
 * Entry: 0047a5a1
 * Name: Pop_Camera
 * Namespace: Global
 * Signature: int Pop_Camera(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Pop_Camera(void)

{
  int iVar1;
  PRESET_VIEW *pPVar2;
  PRESET_VIEW *pPVar3;
  
  iVar1 = 0;
  if (Camera_Stack_Index < 8) {
    pPVar2 = Camera_Stack + Camera_Stack_Index;
    Camera_Stack_Index = Camera_Stack_Index + 1;
    pPVar3 = &View_Record;
    for (iVar1 = 0x8e; iVar1 != 0; iVar1 = iVar1 + -1) {
      pPVar3->Update_Camera = pPVar2->Update_Camera;
      pPVar2 = (PRESET_VIEW *)&pPVar2->Intenal_View;
      pPVar3 = (PRESET_VIEW *)&pPVar3->Intenal_View;
    }
    iVar1 = 1;
  }
  return iVar1;
}
