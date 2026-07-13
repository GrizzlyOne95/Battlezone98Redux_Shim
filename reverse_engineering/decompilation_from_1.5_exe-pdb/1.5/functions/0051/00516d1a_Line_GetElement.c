/*
 * Entry: 00516d1a
 * Name: Line_GetElement
 * Namespace: Global
 * Signature: tagMAP_ELEMENT * Line_GetElement(int param_1, int param_2, char * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagMAP_ELEMENT * __cdecl Line_GetElement(int param_1,int param_2,char *param_3,int param_4)

{
  int iVar1;
  int iVar2;
  uchar uVar3;
  byte bVar4;
  int iVar5;
  
  iVar1 = aiGridX0 + param_1;
  iVar2 = aiGridZ0 + param_2;
  iVar5 = GetTerY(iVar1,iVar2);
  element.altitude = (int)(iVar5 + (iVar5 >> 0x1f & 0xfU)) >> 4;
  uVar3 = CellRegion(iVar1,iVar2);
  if (uVar3 == '\0') {
    element.effects = 3;
  }
  else {
    bVar4 = CellType(iVar1,iVar2);
    element.effects = (uint)bVar4;
  }
  return &element;
}
