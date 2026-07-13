/*
 * Entry: 00411c5b
 * Name: std::_Construct<FollowerInfo,FollowerInfo>
 * Namespace: std
 * Signature: void _Construct<FollowerInfo,FollowerInfo>(FollowerInfo * param_1, FollowerInfo * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Construct<FollowerInfo,FollowerInfo>(FollowerInfo *param_1,FollowerInfo *param_2)

{
  undefined3 uVar1;
  
  if (param_1 != (FollowerInfo *)0x0) {
    param_1->follower = param_2->follower;
    uVar1 = *(undefined3 *)&param_2->field_0x5;
    param_1->needsReset = param_2->needsReset;
    *(undefined3 *)&param_1->field_0x5 = uVar1;
  }
  return;
}
