/*
 * Entry: 004bc4c8
 * Name: Joy_Refresh
 * Namespace: Global
 * Signature: void Joy_Refresh(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Joy_Refresh(void)

{
  int iVar1;
  
  Mono_Clear(mHdl);
  iVar1 = Mono_IsActive(mHdl);
  if (iVar1 != 0) {
    Mono_Line(mHdl,0x1e,10,0xf,"Joystick reading information");
    Mono_Line(mHdl,0,0xf,7," Axis    Raw value     GIDDI value    Sim value");
    Mono_Line(mHdl,0,0x10,7,"------------------------------------------------");
  }
  return;
}
