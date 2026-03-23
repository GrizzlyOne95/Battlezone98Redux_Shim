
void __fastcall FUN_00592410(undefined4 *param_1)

{
  *param_1 = Heap_Class<struct_Strip*,float>::vftable;
  if (*(char *)(param_1 + 3) == '\x01') {
    operator_delete__((void *)param_1[4]);
  }
  return;
}

