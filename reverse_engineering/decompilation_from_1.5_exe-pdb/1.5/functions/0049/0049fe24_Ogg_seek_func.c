/*
 * Entry: 0049fe24
 * Name: Ogg_seek_func
 * Namespace: Global
 * Signature: int Ogg_seek_func(void * param_1, long64 param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Ogg_seek_func(void *param_1,long64 param_2,int param_3)

{
  int in_stack_00000008;
  
  if (param_2._4_4_ == 0) {
    *(int *)((int)param_1 + 0x2f0) = in_stack_00000008;
  }
  else if (param_2._4_4_ == 1) {
    *(int *)((int)param_1 + 0x2f0) = *(int *)((int)param_1 + 0x2f0) + in_stack_00000008;
  }
  else {
    if (param_2._4_4_ != 2) {
      Trace("Ogg_seek_func has invalid whence %d");
      return -1;
    }
    *(undefined4 *)((int)param_1 + 0x2f0) = *(undefined4 *)((int)param_1 + 0x14);
  }
  return 0;
}
