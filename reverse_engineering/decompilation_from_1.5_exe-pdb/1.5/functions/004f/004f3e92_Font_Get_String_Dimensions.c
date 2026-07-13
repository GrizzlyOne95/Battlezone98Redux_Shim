/*
 * Entry: 004f3e92
 * Name: Font_Get_String_Dimensions
 * Namespace: Global
 * Signature: void Font_Get_String_Dimensions(FONT * param_1, char * param_2, long * param_3, long * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Font_Get_String_Dimensions(FONT *param_1,char *param_2,long *param_3,long *param_4)

{
  byte bVar1;
  bool bVar2;
  ushort uVar3;
  CHARACTER *pCVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int local_14;
  int local_10;
  int local_c;
  
  bVar1 = *param_2;
  iVar6 = 0;
  iVar7 = 0;
  local_10 = 0;
  local_14 = 0;
  local_c = 0;
  bVar2 = false;
  while (uVar3 = (ushort)bVar1, bVar1 != 0) {
    for (; (!bVar2 && (tabdefs[local_c] <= iVar6)); local_c = local_c + 1) {
      if (tabdefs[local_c] == -1) {
        bVar2 = true;
      }
    }
    if (uVar3 == 9) {
      if (bVar2) {
        iVar6 = iVar6 + 0x20;
      }
      else {
        iVar6 = tabdefs[local_c];
      }
    }
    else if (uVar3 == 10) {
      iVar6 = 0;
      iVar7 = iVar7 + 2 + param_1->char_height;
    }
    else {
      pCVar4 = GetCharacterAddress(param_1,uVar3);
      iVar6 = iVar6 + pCVar4->Width;
      if (local_10 < iVar6) {
        local_10 = iVar6;
      }
      iVar5 = param_1->char_height + iVar7;
      if (local_14 < iVar5) {
        local_14 = iVar5;
      }
    }
    IncString(&param_2);
    bVar1 = *param_2;
  }
  if (param_3 != (int *)0x0) {
    *param_3 = local_10;
  }
  if (param_4 != (int *)0x0) {
    *param_4 = local_14;
  }
  return;
}
