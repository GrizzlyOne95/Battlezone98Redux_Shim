/*
 * Entry: 0048a57a
 * Name: std::allocator<BASE_STRUCT>::deallocate
 * Namespace: std::allocator<BASE_STRUCT>
 * Signature: void deallocate(allocator<BASE_STRUCT> * this, BASE_STRUCT * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<BASE_STRUCT>::deallocate
          (allocator<BASE_STRUCT> *this,BASE_STRUCT *param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
