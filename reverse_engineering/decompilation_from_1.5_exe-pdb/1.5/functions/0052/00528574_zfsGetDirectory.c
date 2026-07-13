/*
 * Entry: 00528574
 * Name: zfsGetDirectory
 * Namespace: Global
 * Signature: int zfsGetDirectory(ZFS_COOKIE * param_1, ZFS_RENTRY * * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl zfsGetDirectory(ZFS_COOKIE *param_1,ZFS_RENTRY **param_2,int *param_3)

{
  *param_3 = param_1->num_rentries;
  *param_2 = param_1->entry_table;
  return 1;
}
