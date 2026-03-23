
undefined4 * __fastcall FUN_005ce870(undefined4 *param_1)

{
  FUN_00586300();
  *param_1 = SeismicWaveClass::vftable;
  param_1[3] = 0x53454953;
  param_1[4] = "seismic";
  param_1[0x16] = 0x43480000;
  *(undefined2 *)(param_1 + 0x17) = 8;
  param_1[0x1e] = 0x42480000;
  param_1[0x1f] = 1.0 / (float)param_1[0x1e];
  param_1[0x20] = (float)param_1[0x1f] * -2.5 * (float)param_1[0x1f];
  param_1[0x21] = 0x41000000;
  param_1[0x22] = 0;
  param_1[0x23] = 0x40a00000;
  param_1[0x24] = 1.0 / (float)param_1[0x23];
  param_1[0x25] = 0x40000000;
  param_1[0x26] = 1.0 / (float)param_1[0x25];
  param_1[0x27] = 0x42c80000;
  param_1[0x28] = 0x42480000;
  param_1[0x29] = 0x40400000;
  param_1[0x2a] = 0x40000000;
  param_1[0x2b] = 0x40a00000;
  param_1[0x2c] = 0x3f800000;
  param_1[0x2d] = 0x3f800000;
  param_1[0x2e] = 0;
  param_1[0x2f] = 0;
  param_1[0x30] = 0x3f800000;
  return param_1;
}

