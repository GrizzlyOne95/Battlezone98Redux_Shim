/*
 * Entry: 004f1f76
 * Name: Device_Force_Predefine_Ramp
 * Namespace: Global
 * Signature: void Device_Force_Predefine_Ramp(VIDEO_DEVICE * param_1, long param_2, long param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Device_Force_Predefine_Ramp(VIDEO_DEVICE *param_1,long param_2,long param_3,long param_4)

{
  uchar uVar1;
  int iVar2;
  uint uVar3;
  uchar *puVar4;
  uint uVar5;
  
  uVar3 = param_2 & 0xff;
  iVar2 = (param_3 & 0xffU) * 0x10000 + uVar3 * -0x10000;
  uVar5 = param_4 & 0xff;
  param_2 = 0x20;
  puVar4 = Luminance_Table[0] + uVar5;
  param_4 = uVar3 * 0x10000 + 0x8000;
  do {
    *puVar4 = (uchar)((uint)param_4 >> 0x10);
    puVar4 = puVar4 + 0x100;
    param_2 = param_2 + -1;
    param_4 = param_4 + ((int)(iVar2 + (iVar2 >> 0x1f & 0x1fU)) >> 5);
  } while (param_2 != 0);
  uVar1 = Luminance_Table[0x1f][uVar5];
  puVar4 = &DAT_00d20480 + uVar5;
  iVar2 = 0x70;
  do {
    *puVar4 = uVar1;
    puVar4 = puVar4 + 0x100;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  uVar1 = Luminance_Table[0][uVar5];
  puVar4 = &DAT_00d2e380 + uVar5;
  iVar2 = 0x70;
  do {
    *puVar4 = uVar1;
    puVar4 = puVar4 + -0x100;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}
