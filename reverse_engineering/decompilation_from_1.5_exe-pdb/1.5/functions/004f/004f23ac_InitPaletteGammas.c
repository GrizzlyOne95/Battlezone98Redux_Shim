/*
 * Entry: 004f23ac
 * Name: InitPaletteGammas
 * Namespace: Global
 * Signature: void InitPaletteGammas(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitPaletteGammas(void)

{
  int iVar1;
  undefined1 extraout_AL;
  double *pdVar2;
  undefined1 *puVar3;
  double local_68 [12];
  int local_8;
  
  local_68[0] = 0.7;
  local_68[1] = 0.8;
  puVar3 = &DAT_00d3f27f;
  pdVar2 = local_68;
  local_68[2] = 0.9;
  local_68[3] = 1.0;
  local_68[4] = 1.2;
  local_68[5] = 1.4;
  local_68[6] = 1.6;
  local_68[7] = 1.8;
  local_68[8] = 2.0;
  local_68[9] = 2.2;
  local_68[10] = 2.5;
  do {
    local_8 = 0;
    local_68[0xb] = 1.0 / *pdVar2;
    do {
      __CIpow();
      _ftol2();
      iVar1 = local_8 + 1;
      puVar3[local_8 + -0xff] = extraout_AL;
      local_8 = iVar1;
    } while (iVar1 < 0x100);
    *puVar3 = 0xff;
    puVar3 = puVar3 + 0x100;
    pdVar2 = pdVar2 + 1;
  } while ((int)puVar3 < 0xd3fc80);
  return;
}
