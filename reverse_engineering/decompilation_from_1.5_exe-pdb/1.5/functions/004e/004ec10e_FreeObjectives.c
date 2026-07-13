/*
 * Entry: 004ec10e
 * Name: FreeObjectives
 * Namespace: Global
 * Signature: void FreeObjectives(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FreeObjectives(void)

{
  char **unaff_retaddr;
  long in_stack_00000004;
  
  if (0 < od.NumObjs) {
    FreeObjectiveText(unaff_retaddr,in_stack_00000004);
    FreeObjectiveText(unaff_retaddr,in_stack_00000004);
    memset(&od,0,0x7c);
  }
  return;
}
