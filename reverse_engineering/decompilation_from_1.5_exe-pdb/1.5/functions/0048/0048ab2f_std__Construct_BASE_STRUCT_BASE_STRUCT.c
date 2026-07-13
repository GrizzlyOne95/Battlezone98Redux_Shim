/*
 * Entry: 0048ab2f
 * Name: std::_Construct<BASE_STRUCT,BASE_STRUCT>
 * Namespace: std
 * Signature: void _Construct<BASE_STRUCT,BASE_STRUCT>(BASE_STRUCT * param_1, BASE_STRUCT * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Construct<BASE_STRUCT,BASE_STRUCT>(BASE_STRUCT *param_1,BASE_STRUCT *param_2)

{
  if (param_1 != (BASE_STRUCT *)0x0) {
    *(undefined4 *)param_1 = *(undefined4 *)param_2;
    *(undefined2 *)((int)&param_1->dwLocalID + 2) = *(undefined2 *)((int)&param_2->dwLocalID + 2);
  }
  return;
}
