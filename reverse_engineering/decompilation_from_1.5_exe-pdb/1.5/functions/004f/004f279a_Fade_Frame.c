/*
 * Entry: 004f279a
 * Name: Fade_Frame
 * Namespace: Global
 * Signature: void Fade_Frame(int param_1, float param_2, long param_3, long param_4, long param_5, long param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Fade_Frame(int param_1,float param_2,long param_3,long param_4,long param_5,long param_6)

{
  byte bVar1;
  byte bVar2;
  char extraout_AL;
  char extraout_AL_00;
  char extraout_AL_01;
  int extraout_EAX;
  DWORD DVar3;
  int iVar4;
  RGB *pRVar5;
  RGB *pRVar6;
  RGB local_324 [256];
  int local_24;
  double local_20;
  uint local_18;
  int local_14;
  double local_10;
  int local_8;
  
  if (useD3D == 0) {
    local_10 = 0.0;
    local_20 = 1.0 / (double)param_3;
    if (param_1 == 0) {
      local_10 = 1.0;
      local_20 = -local_20;
    }
    if (0 < param_3) {
      _ftol2();
      local_14 = param_3;
      local_24 = extraout_EAX;
      do {
        DVar3 = Get_TimeNow();
        local_18 = DVar3 - local_24;
        iVar4 = 0;
        do {
          bVar1 = (&Device.Palette[0].r)[iVar4];
          local_8 = param_4 - (uint)bVar1;
          _ftol2();
          bVar2 = (&Device.Palette[0].g)[iVar4];
          (&local_324[0].r)[iVar4] = extraout_AL + bVar1;
          local_8 = param_5 - (uint)bVar2;
          _ftol2();
          bVar1 = (&Device.Palette[0].b)[iVar4];
          (&local_324[0].g)[iVar4] = extraout_AL_00 + bVar2;
          local_8 = param_6 - (uint)bVar1;
          _ftol2();
          (&local_324[0].b)[iVar4] = extraout_AL_01 + bVar1;
          iVar4 = iVar4 + 3;
        } while (iVar4 < 0x300);
        ApplyGammaToPalette(local_324,0,0x100,0);
        (*Device.VideoMode.OverlayPalette)(&Device,local_324);
        (*Device.Refresh.Blit)(&Device);
        do {
          DVar3 = Get_TimeNow();
        } while (DVar3 < local_18);
        local_14 = local_14 + -1;
        local_10 = local_20 + local_10;
      } while (local_14 != 0);
    }
    if (param_1 == 0) {
      pRVar5 = Device.Palette;
      pRVar6 = local_324;
      for (iVar4 = 0xc0; iVar4 != 0; iVar4 = iVar4 + -1) {
        *(undefined4 *)pRVar6 = *(undefined4 *)pRVar5;
        pRVar5 = (RGB *)&pRVar5[1].g;
        pRVar6 = (RGB *)&pRVar6[1].g;
      }
      ApplyGammaToPalette(local_324,0,0x100,0);
    }
    Fade_First_Frame_Cueing_Flag = 0;
  }
  else {
    (*Device.Refresh.BlitFill)(&Device,0);
    (*Device.Refresh.Blit)(&Device);
  }
  return;
}
