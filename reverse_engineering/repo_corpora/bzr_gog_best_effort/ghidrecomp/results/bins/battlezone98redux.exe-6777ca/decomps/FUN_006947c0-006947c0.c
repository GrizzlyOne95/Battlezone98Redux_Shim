
void FUN_006947c0(void *param_1)

{
  FUN_006a5fd0("AIP_Delete: Deleting aip\'s construction program\n");
  FUN_00693230(*(undefined4 *)((int)param_1 + 0x8c));
  free(*(void **)((int)param_1 + 0x90));
  free(*(void **)((int)param_1 + 0x94));
  FUN_006a5fd0("    Done\n");
  free(param_1);
  return;
}

