/*
 * Entry: 004e7bbe
 * Name: AnimObj_Init
 * Namespace: Global
 * Signature: long AnimObj_Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl AnimObj_Init(void)

{
  AnimObj_Close();
  AnimHeap = (void *)0x1;
  reg_add_ent_func(AddEntCallback);
  reg_del_ent_func(DelEntCallback);
  return 0;
}
