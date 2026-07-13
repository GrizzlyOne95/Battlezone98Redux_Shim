/*
 * Entry: 0048b33e
 * Name: std::allocator<BASE_STRUCT>::construct
 * Namespace: std::allocator<BASE_STRUCT>
 * Signature: void construct(allocator<BASE_STRUCT> * this, BASE_STRUCT * param_1, BASE_STRUCT * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<BASE_STRUCT>::construct
          (allocator<BASE_STRUCT> *this,BASE_STRUCT *param_1,BASE_STRUCT *param_2)

{
  if (param_1 != (BASE_STRUCT *)0x0) {
    *(undefined4 *)param_1 = *(undefined4 *)param_2;
    *(undefined2 *)((int)&param_1->dwLocalID + 2) = *(undefined2 *)((int)&param_2->dwLocalID + 2);
  }
  return;
}
