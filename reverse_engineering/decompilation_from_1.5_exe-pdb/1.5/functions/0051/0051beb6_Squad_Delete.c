/*
 * Entry: 0051beb6
 * Name: Squad_Delete
 * Namespace: Global
 * Signature: void Squad_Delete(tag_squad * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Squad_Delete(tag_squad *param_1)

{
  if (param_1 == (tag_squad *)0x0) {
    _tlog_filename = ".\\Schedule\\Squad.cpp";
    _tlog_line = 0xeb;
    tlog(2,"AI  Squad_Delete tried to free a NULL squad");
    return;
  }
  tlog_gdm("Freeing Squad #%d  @%d\n");
  C_Linked_List_Empty(&param_1->my_units);
  Squad_Detach_Goal(param_1);
  free(param_1);
  tlog_gdm("Freed Squad \n");
  return;
}
