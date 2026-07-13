/*
 * Entry: 004e72fd
 * Name: AddEntCallback
 * Namespace: Global
 * Signature: void AddEntCallback(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AddEntCallback(tagENTITY *param_1)

{
  if (0 < AnimCount) {
    if (*(_OBJ76 **)((&AnimActiveList[0x1ff].loopsToDo)[AnimCount] + 0x38) == param_1->obj76) {
      *(tagENTITY **)((&AnimActiveList[0x1ff].loopsToDo)[AnimCount] + 0x3c) = param_1;
    }
  }
  return;
}
