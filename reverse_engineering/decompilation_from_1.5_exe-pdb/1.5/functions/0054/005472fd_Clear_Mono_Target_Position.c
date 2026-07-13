/*
 * Entry: 005472fd
 * Name: Clear_Mono_Target_Position
 * Namespace: Global
 * Signature: void Clear_Mono_Target_Position(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Clear_Mono_Target_Position(void)

{
  int iVar1;
  
  Mono_Clear(Mono_Handle);
  iVar1 = Mono_IsActive(Mono_Handle);
  if (iVar1 != 0) {
    Mono_Line(Mono_Handle,1,0xf,7,"Camera Target Position (meters)");
    Mono_Line(Mono_Handle,1,0x10,7,"  x         y        z");
  }
  return;
}
