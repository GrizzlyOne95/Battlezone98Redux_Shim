/*
 * Entry: 0049989a
 * Name: stdext::unchecked_uninitialized_fill_n<GameObjectClass_*_*,unsigned_int,GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Namespace: stdext
 * Signature: void unchecked_uninitialized_fill_n<GameObjectClass_*_*,unsigned_int,GameObjectClass_*,std::allocator<GameObjectClass_*>_>(GameObjectClass * * param_1, uint param_2, GameObjectClass * * param_3, allocator<GameObjectClass_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::
unchecked_uninitialized_fill_n<GameObjectClass_*_*,unsigned_int,GameObjectClass_*,std::allocator<GameObjectClass_*>_>
          (GameObjectClass **param_1,uint param_2,GameObjectClass **param_3,
          allocator<GameObjectClass_*> *param_4)

{
  unchecked_fill_n<GameObjectClass_*_*,unsigned_int,GameObjectClass_*>(param_1,param_2,param_3);
  return;
}
