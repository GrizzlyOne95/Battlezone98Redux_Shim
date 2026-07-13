/*
 * Entry: 004ebf27
 * Name: DrawNotepadContents
 * Namespace: Global
 * Signature: void DrawNotepadContents(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DrawNotepadContents(void)

{
  HGDIOBJ h;
  long lVar1;
  int iVar2;
  int iVar3;
  tagRECT local_18;
  HGDIOBJ local_8;
  
  Graphic_Buffer_Clear(&np.TextGB,0xff);
  h = GetStockObject(2);
  SelectObject((HDC)np.DC,h);
  local_8 = SelectObject((HDC)np.DC,np.TextBitmap);
  RealizePalette((HDC)np.DC);
  SetTextColor((HDC)np.DC,0x2101010);
  SetBkColor((HDC)np.DC,0x2f0f0f0);
  SetBkMode((HDC)np.DC,1);
  SelectObject((HDC)np.DC,np.Font);
  local_18.left = np.TextBox.left;
  local_18.top = np.TextBox.top;
  local_18.right = np.TextBox.right;
  local_18.bottom = np.TextBox.bottom;
  iVar2 = (-(uint)((UserProfilePtr->graphicDetail).resolution < 6) & 2) + 0xe;
  if ((0 < od.NumObjs) && (iVar3 = 0, 0 < od.NumObjs)) {
    do {
      if ((od.ObjState[iVar3] & 1U) == 0) {
        lVar1 = DrawWrappedText(np.DC,&local_18,od.ObjText[iVar3],iVar2,10,
                                (_GRAPHIC_BUFFER *)
                                (-(uint)((od.ObjState[iVar3] & 2U) != 0) & 0xd3ff78));
        local_18.top = local_18.top + lVar1 + iVar2;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < od.NumObjs);
  }
  GdiFlush();
  SelectObject((HDC)np.DC,local_8);
  return;
}
