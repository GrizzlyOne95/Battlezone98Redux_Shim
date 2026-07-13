/*
 * Entry: 004090a7
 * Name: BlockedCellClean
 * Namespace: Global
 * Signature: void BlockedCellClean(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl BlockedCellClean(void)

{
  char **ppcVar1;
  
  operator_delete__(cellType);
  cellType = (uchar *)0x0;
  operator_delete__(cellRegion);
  cellRegion = (uchar *)0x0;
  ppcVar1 = cellTeamRef;
  do {
    operator_delete__(*ppcVar1);
    *ppcVar1 = (char *)0x0;
    ppcVar1 = ppcVar1 + 1;
  } while ((int)ppcVar1 < 0x64d9e0);
  operator_delete__(cellTeam);
  cellTeam = (ushort *)0x0;
  std::
  _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
  ::clear((_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
           *)&buildingArea);
  std::
  _Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
  ::clear((_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
           *)&perimeterArea);
  return;
}
