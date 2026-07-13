/*
 * Entry: 00411c4a
 * Name: std::_Construct<FollowGroup_*,FollowGroup_*>
 * Namespace: std
 * Signature: void _Construct<FollowGroup_*,FollowGroup_*>(FollowGroup * * param_1, FollowGroup * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Construct<FollowGroup_*,FollowGroup_*>(FollowGroup **param_1,FollowGroup **param_2)

{
  if (param_1 != (FollowGroup **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
