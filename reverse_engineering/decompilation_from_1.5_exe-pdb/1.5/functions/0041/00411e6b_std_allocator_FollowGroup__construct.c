/*
 * Entry: 00411e6b
 * Name: std::allocator<FollowGroup_*>::construct
 * Namespace: std::allocator<FollowGroup_*>
 * Signature: void construct(allocator<FollowGroup_*> * this, FollowGroup * * param_1, FollowGroup * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<FollowGroup_*>::construct
          (allocator<FollowGroup_*> *this,FollowGroup **param_1,FollowGroup **param_2)

{
  if (param_1 != (FollowGroup **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
