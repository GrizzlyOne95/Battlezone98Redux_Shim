/*
 * Entry: 0050552a
 * Name: Restore_Translucency_Key_Color
 * Namespace: Global
 * Signature: void Restore_Translucency_Key_Color(uchar * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Restore_Translucency_Key_Color(uchar *param_1)

{
  uchar *puVar1;
  int in_ECX;
  int iVar2;
  
  iVar2 = 0;
  puVar1 = Translucency_Table[0] + 0xff;
  do {
    *puVar1 = *(uchar *)(iVar2 + in_ECX);
    puVar1 = puVar1 + 0x100;
    iVar2 = iVar2 + 1;
  } while ((int)puVar1 < 0xd1e55f);
  return;
}
