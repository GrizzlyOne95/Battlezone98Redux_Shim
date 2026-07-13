/*
 * Entry: 004f3a40
 * Name: Font_Get_Character_Width
 * Namespace: Global
 * Signature: long Font_Get_Character_Width(FONT * param_1, ushort param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Font_Get_Character_Width(FONT *param_1,ushort param_2)

{
  CHARACTER *pCVar1;
  
  pCVar1 = GetCharacterAddress(param_1,param_2);
  return pCVar1->Width;
}
