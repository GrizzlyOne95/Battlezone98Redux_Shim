/*
 * Entry: 005154d1
 * Name: PREREQ_MapPrereqIdtoName
 * Namespace: Global
 * Signature: char * PREREQ_MapPrereqIdtoName(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl PREREQ_MapPrereqIdtoName(ushort param_1)

{
  PREREQ_struct *pPVar1;
  undefined2 in_stack_00000006;
  
  pPVar1 = PREREQ_table + param_1;
  if (pPVar1->type == '\0') {
    return (char *)((int)pPVar1->data + 0x34);
  }
  if (pPVar1->type == '\x01') {
    return (char *)((int)pPVar1->data + 0x60);
  }
  return _param_1;
}
