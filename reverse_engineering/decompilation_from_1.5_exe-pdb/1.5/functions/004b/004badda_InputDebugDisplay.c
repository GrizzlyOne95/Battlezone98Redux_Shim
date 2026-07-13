/*
 * Entry: 004badda
 * Name: InputDebugDisplay
 * Namespace: Global
 * Signature: void InputDebugDisplay(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InputDebugDisplay(void)

{
  int iVar1;
  
  iVar1 = Mono_IsActive(hInpDbg);
  if (iVar1 != 0) {
    Mono_Line(hInpDbg,0,5,7,"      throttle = %09ld         ");
    Mono_Line(hInpDbg,0,6,7,"   throttle up = %04d          ");
    Mono_Line(hInpDbg,0,7,7,"   throttle dn = %04d          ");
    Mono_Line(hInpDbg,0,8,7,"      steering = %09ld         ");
    Mono_Line(hInpDbg,0,9,7,"   steering lt = %04d          ");
    Mono_Line(hInpDbg,0,10,7,"   steering rt = %04d          ");
    Mono_Line(hInpDbg,0x28,1,7,"     track yaw = %09ld         ");
    Mono_Line(hInpDbg,0x28,2,7,"  track yaw up = %04d          ");
    Mono_Line(hInpDbg,0x28,3,7,"  track yaw dn = %04d          ");
    Mono_Line(hInpDbg,0x28,4,7,"   track pitch = %09ld         ");
    Mono_Line(hInpDbg,0x28,5,7,"track pitch up = %04d          ");
    Mono_Line(hInpDbg,0x28,6,7,"track pitch dn = %04d          ");
    Mono_Line(hInpDbg,0x28,7,7,"    track dist = %09ld         ");
    Mono_Line(hInpDbg,0x28,8,7," track dist up = %04d          ");
    Mono_Line(hInpDbg,0x28,9,7," track dist dn = %04d          ");
  }
  return;
}
