/*
 * Entry: 004f4925
 * Name: Graphic_Buffer_Clear
 * Namespace: Global
 * Signature: void Graphic_Buffer_Clear(_GRAPHIC_BUFFER * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Graphic_Buffer_Clear(_GRAPHIC_BUFFER *param_1,long param_2)

{
  uint uVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  
  if (param_1->Status == 1) {
    if ((VIDEO_DEVICE *)param_1 == &Device) {
      if (useD3D != 0) {
        param_2 = (long)D3D_Remap_Palette[param_2 & 0xff];
      }
      (*Device.Refresh.BlitFill)(&Device,param_2);
      return;
    }
    puVar5 = (uint *)param_1->Buffer;
    uVar2 = CONCAT11((undefined1)param_2,(undefined1)param_2);
    uVar3 = (uint)uVar2;
    uVar4 = param_1->Width * param_1->Height;
    if ((uVar4 & 3) == 0) {
      for (uVar4 = uVar4 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar5 = CONCAT22(uVar2,uVar2);
        puVar5 = puVar5 + 1;
      }
    }
    else {
      if (0x3f < (int)uVar4) {
        uVar3 = CONCAT22(uVar2,uVar2);
        uVar1 = uVar4 - 0x40;
        do {
          uVar4 = uVar1;
          *puVar5 = uVar3;
          puVar5[8] = uVar3;
          puVar5[1] = uVar3;
          puVar5[9] = uVar3;
          puVar5[2] = uVar3;
          puVar5[10] = uVar3;
          puVar5[3] = uVar3;
          puVar5[0xb] = uVar3;
          puVar5[4] = uVar3;
          puVar5[0xc] = uVar3;
          puVar5[5] = uVar3;
          puVar5[0xd] = uVar3;
          puVar5[6] = uVar3;
          puVar5[0xe] = uVar3;
          puVar5[7] = uVar3;
          puVar5[0xf] = uVar3;
          puVar5 = puVar5 + 0x10;
          uVar1 = uVar4 - 0x40;
        } while (uVar4 - 0x40 != 0 && 0x3f < (int)uVar4);
        if (uVar4 == 0) {
          return;
        }
      }
      do {
        *(char *)puVar5 = (char)uVar3;
        puVar5 = (uint *)((int)puVar5 + 1);
        uVar4 = uVar4 - 1;
      } while (uVar4 != 0);
    }
  }
  return;
}
