/*
 * Entry: 004ebef6
 * Name: FreeObjectiveText
 * Namespace: Global
 * Signature: void FreeObjectiveText(char * * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FreeObjectiveText(char **param_1,long param_2)

{
  int in_EAX;
  undefined4 *in_ECX;
  
  if ((in_ECX != (undefined4 *)0x0) && (0 < in_EAX)) {
    do {
      if ((void *)*in_ECX != (void *)0x0) {
        if (hDefaultHeap != (void *)0x0) {
          free((void *)*in_ECX);
        }
        *in_ECX = 0;
      }
      in_ECX = in_ECX + 1;
      in_EAX = in_EAX + -1;
    } while (in_EAX != 0);
  }
  return;
}
