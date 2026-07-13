/*
 * Entry: 004c3308
 * Name: ColorFade::Render
 * Namespace: ColorFade
 * Signature: void Render(ColorFade * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ColorFade::Render(ColorFade *this)

{
  byte bVar1;
  int iVar2;
  RGB *pRVar3;
  uchar *puVar4;
  int iVar5;
  RGB *pRVar6;
  uchar *puVar7;
  float fVar8;
  int local_18;
  int local_10;
  int local_8;
  
  if ((View_Record.Current_View != TWO_D_VIEW) && (View_Record.Current_View != EDIT_VIEW)) {
    fVar8 = TimeStepLocal();
    iVar2 = 0;
    if (useD3D == 0) {
      pRVar3 = Device.Palette;
      pRVar6 = Pal;
      for (iVar2 = 0xc0; iVar2 != 0; iVar2 = iVar2 + -1) {
        *(undefined4 *)pRVar6 = *(undefined4 *)pRVar3;
        pRVar3 = (RGB *)&pRVar3[1].g;
        pRVar6 = (RGB *)&pRVar6[1].g;
      }
      if (0.0 < this->glare) {
        if (this->glare <= 1.0) {
          local_10 = SUB84((double)(this->glare * 224.0 + (float)Float2Int),0);
        }
        else {
          local_10 = 0xe0;
        }
        puVar4 = &Pal[0].g;
        do {
          bVar1 = *puVar4;
          ((RGB *)(puVar4 + -1))->r =
               (char)((0xff - (uint)((RGB *)(puVar4 + -1))->r) * local_10 >> 8) +
               ((RGB *)(puVar4 + -1))->r;
          *puVar4 = (char)((0xff - (uint)bVar1) * local_10 >> 8) + *puVar4;
          puVar7 = puVar4 + 3;
          puVar4[1] = (char)((0xff - (uint)puVar4[1]) * local_10 >> 8) + puVar4[1];
          puVar4 = puVar7;
        } while ((int)puVar7 < 0xb43049);
        this->glare = 0.0;
      }
      if (0.0 < this->ratio) {
        if (this->ratio <= 1.0) {
          local_10 = SUB84((double)(this->ratio * 224.0 + (float)Float2Int),0);
        }
        else {
          local_10 = 0xe0;
        }
        puVar4 = &Pal[0].g;
        do {
          bVar1 = *puVar4;
          ((RGB *)(puVar4 + -1))->r =
               (char)(((uint)(this->fade).r - (uint)((RGB *)(puVar4 + -1))->r) * local_10 >> 8) +
               ((RGB *)(puVar4 + -1))->r;
          *puVar4 = (char)(((uint)(this->fade).g - (uint)bVar1) * local_10 >> 8) + bVar1;
          puVar4[1] = (char)(((uint)(this->fade).b - (uint)puVar4[1]) * local_10 >> 8) + puVar4[1];
          puVar4 = puVar4 + 3;
        } while ((int)puVar4 < 0xb43049);
        fVar8 = this->ratio - this->rate * this->ratio * fVar8;
        this->ratio = fVar8;
        if (fVar8 < 0.01) {
          this->ratio = 0.0;
        }
      }
      ApplyGammaToPalette(Pal,0,0x100,0);
      (*Device.VideoMode.OverlayPalette)(&Device,Pal);
    }
    else {
      local_8 = 0;
      if (0.0 < this->glare) {
        if (this->glare <= 1.0) {
          local_18 = SUB84((double)(this->glare * 224.0 + (float)Float2Int),0);
        }
        else {
          local_18 = 0xe0;
        }
        this->glare = 0.0;
        local_8 = local_18;
      }
      if (0.0 < this->ratio) {
        if (this->ratio <= 1.0) {
          local_18 = SUB84((double)(this->ratio * 224.0 + (float)Float2Int),0);
        }
        else {
          local_18 = 0xe0;
        }
        fVar8 = this->ratio - this->rate * this->ratio * fVar8;
        this->ratio = fVar8;
        iVar2 = local_18;
        if (fVar8 < 0.01) {
          this->ratio = 0.0;
        }
      }
      fVar8 = spriteZ;
      iVar5 = (local_8 - (local_8 * iVar2) / 0xff) + iVar2;
      spriteZ = fVar8;
      if (0.0 < (float)iVar5) {
        local_8 = (0xff - iVar2) * local_8;
        spriteZ = 0.1;
        D3D_Color_Rectangle((((int)((uint)(this->fade).r * iVar2 + local_8) / iVar5 & 0xffU |
                             iVar5 * 0x100) << 8 |
                            (int)((uint)(this->fade).g * iVar2 + local_8) / iVar5 & 0xffU) << 8 |
                            (int)((uint)(this->fade).b * iVar2 + local_8) / iVar5 & 0xffU,
                            ((View_Record.MainCam.Buffer)->Pane).x0,
                            ((View_Record.MainCam.Buffer)->Pane).y0,
                            ((View_Record.MainCam.Buffer)->Pane).x1,
                            ((View_Record.MainCam.Buffer)->Pane).y1,0);
        spriteZ = fVar8;
      }
    }
  }
  return;
}
