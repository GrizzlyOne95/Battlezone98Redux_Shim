/*
 * Entry: 0056d827
 * Name: cameraIsArrived
 * Namespace: Global
 * Signature: int cameraIsArrived(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl cameraIsArrived(void)

{
  int iVar1;
  
  iVar1 = Camera_Record.End_Path;
  Camera_Record.End_Path = 0;
  return iVar1;
}
