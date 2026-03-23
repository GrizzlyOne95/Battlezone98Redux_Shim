
undefined4 FUN_008272d0(void *param_1)

{
  free(*(void **)((int)param_1 + 0x24));
  free(*(void **)((int)param_1 + 0x28));
  free(param_1);
  return 1;
}

