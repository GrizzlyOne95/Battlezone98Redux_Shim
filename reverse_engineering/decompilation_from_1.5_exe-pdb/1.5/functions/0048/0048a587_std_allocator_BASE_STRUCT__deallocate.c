/*
 * Entry: 0048a587
 * Name: std::allocator<BASE_STRUCT_*>::deallocate
 * Namespace: std::allocator<BASE_STRUCT_*>
 * Signature: void deallocate(allocator<BASE_STRUCT_*> * this, BASE_STRUCT * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<BASE_STRUCT_*>::deallocate
          (allocator<BASE_STRUCT_*> *this,BASE_STRUCT **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
