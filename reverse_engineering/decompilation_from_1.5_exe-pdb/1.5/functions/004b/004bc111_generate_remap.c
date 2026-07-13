/*
 * Entry: 004bc111
 * Name: generate_remap
 * Namespace: Global
 * Signature: void generate_remap(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl generate_remap(void)

{
  int extraout_EAX;
  long *plVar1;
  long *plVar2;
  long *plVar3;
  int local_8;
  
  plVar1 = joystickRemap[0] + 0x7f;
  do {
    local_8 = 0;
    plVar2 = plVar1;
    plVar3 = plVar1;
    do {
      __CIpow();
      _ftol2_sse();
      local_8 = local_8 + 1;
      *plVar3 = -extraout_EAX;
      *plVar2 = extraout_EAX;
      plVar2 = plVar2 + 1;
      plVar3 = plVar3 + -1;
    } while (local_8 < 0x80);
    plVar1 = plVar1 + 0x100;
  } while ((int)plVar1 < 0xb1a6dc);
  return;
}
