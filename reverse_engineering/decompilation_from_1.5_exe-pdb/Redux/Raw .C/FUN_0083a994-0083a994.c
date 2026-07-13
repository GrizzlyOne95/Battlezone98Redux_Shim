
void FUN_0083a994(int param_1,int param_2)

{
  FUN_0083b5a6(param_1,param_2,0);
  if (0x7ffffffd < *(int *)(param_2 + 0x20)) {
    FUN_0083a089(*(undefined4 *)(param_1 + 0x30),0x7ffffffd,"items in a constructor");
  }
  *(int *)(param_2 + 0x20) = *(int *)(param_2 + 0x20) + 1;
  *(int *)(param_2 + 0x24) = *(int *)(param_2 + 0x24) + 1;
  return;
}

