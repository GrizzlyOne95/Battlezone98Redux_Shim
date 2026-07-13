/*
 * Entry: 004c79ea
 * Name: DisplayInterface::PrintClear
 * Namespace: DisplayInterface
 * Signature: void PrintClear(DisplayInterface * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DisplayInterface::PrintClear(DisplayInterface *this)

{
  Font_Set_Foreground(Default_Font,colorGrey);
  printLine = 0;
  printHeight = Default_Font->char_height + 4;
  printBuffer = View_Record.MainCam.Buffer;
  return;
}
