/*
 * Entry: 00510cd7
 * Name: Grassfire_Trash
 * Namespace: Global
 * Signature: void Grassfire_Trash(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Grassfire_Trash(void)

{
  if (grassfire_initialised == 0) {
    _tlog_filename = ".\\Schedule\\Grasfire.c";
    _tlog_line = 0x11d;
    tlog(1,"Grassfire Closed without matching open.");
    return;
  }
  grassfire_initialised = 0;
  free(default_inbuf);
  free(default_this_one);
  free(default_other);
  NR_Free_Imatrix(default_temp,0,default_rows + -1,0,default_columns + -1);
  return;
}
