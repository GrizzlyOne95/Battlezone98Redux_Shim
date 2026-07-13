/*
 * Entry: 0040e36d
 * Name: std::allocator<AttackerInfo>::construct
 * Namespace: std::allocator<AttackerInfo>
 * Signature: void construct(allocator<AttackerInfo> * this, AttackerInfo * param_1, AttackerInfo * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<AttackerInfo>::construct
          (allocator<AttackerInfo> *this,AttackerInfo *param_1,AttackerInfo *param_2)

{
  _Construct<AttackerInfo,AttackerInfo>(param_1,param_2);
  return;
}
