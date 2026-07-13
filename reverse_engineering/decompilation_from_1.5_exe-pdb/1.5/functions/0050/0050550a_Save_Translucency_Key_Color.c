/*
 * Entry: 0050550a
 * Name: Save_Translucency_Key_Color
 * Namespace: Global
 * Signature: void Save_Translucency_Key_Color(uchar * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Save_Translucency_Key_Color(uchar *param_1)

{
  uchar *puVar1;
  int in_ECX;
  int iVar2;
  
  iVar2 = 0;
  puVar1 = Translucency_Table[0] + 0xff;
  do {
    *(uchar *)(iVar2 + in_ECX) = *puVar1;
    *puVar1 = (uchar)iVar2;
    puVar1 = puVar1 + 0x100;
    iVar2 = iVar2 + 1;
  } while ((int)puVar1 < 0xd1e55f);
  return;
}
