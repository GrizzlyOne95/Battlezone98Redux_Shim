/*
 * Entry: 004ed27f
 * Name: Init_Object_Database
 * Namespace: Global
 * Signature: void Init_Object_Database(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Init_Object_Database(void)

{
  memset(inter_object_table,0xffffffff,0x271c);
  memset(object_table,0xffffffff,0x1c4);
  if (max_io < io_nextfree) {
    max_io = io_nextfree;
  }
  if (max_o < o_nextfree) {
    max_o = o_nextfree;
  }
  io_nextfree = 0;
  o_nextfree = 0;
  return;
}
