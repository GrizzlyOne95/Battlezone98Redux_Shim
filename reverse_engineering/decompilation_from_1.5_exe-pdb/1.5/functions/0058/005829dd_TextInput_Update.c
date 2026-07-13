/*
 * Entry: 005829dd
 * Name: TextInput_Update
 * Namespace: Global
 * Signature: void TextInput_Update(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl TextInput_Update(void)

{
  int *piVar1;
  wrap_struct *pwVar2;
  uint uVar3;
  uint uVar4;
  CHARACTER *pCVar5;
  INPUT_REGION *unaff_EDI;
  char *pcVar6;
  uint local_10;
  char local_5;
  
  pwVar2 = region_list;
  do {
    if (pwVar2 == (wrap_struct *)0x0) {
      return;
    }
    piVar1 = pwVar2->ptr;
    if ((*(byte *)(piVar1 + 0x49) & 1) != 0) {
      uVar3 = (uint)(((Device.Viewport.Pane.x1 - Device.Viewport.Pane.x0) + 1) * *piVar1) / 0x280;
      uVar4 = (uint)(((Device.Viewport.Pane.y1 - Device.Viewport.Pane.y0) + 1) * piVar1[1]) / 0x1e0;
      Graphic_Rect_Filled(&Device.Viewport,uVar3,uVar4,piVar1[2] + -1 + uVar3,piVar1[3] + -1 + uVar4
                          ,0,ONE_THIRD_TRANSLUCENT_PIXELS);
      Font_Set_Foreground(Default_Font,piVar1[0x48]);
      Font_Set_Background(Default_Font,-1);
      local_10 = 0;
      local_5 = '\0';
      for (pcVar6 = (char *)(piVar1[0x45] + 0x10 + (int)piVar1); *pcVar6 != '\0';
          pcVar6 = pcVar6 + 1) {
        pCVar5 = GetCharacterAddress(Default_Font,(short)*pcVar6);
        local_10 = pCVar5->Width + local_10;
        if ((uint)piVar1[2] < local_10) {
          local_5 = *pcVar6;
          *pcVar6 = '\0';
          break;
        }
      }
      Font_Print_String(Default_Font,&Device.Viewport,piVar1[0x46] + uVar3,uVar4,
                        (char *)(piVar1[0x45] + 0x10 + (int)piVar1));
      *pcVar6 = local_5;
      if ((piVar1[0x49] & 0x100U) != 0) {
        draw_cursor(unaff_EDI);
      }
      piVar1[0x49] = piVar1[0x49] & 0xfffffdff;
    }
    pwVar2 = pwVar2->next;
  } while( true );
}
