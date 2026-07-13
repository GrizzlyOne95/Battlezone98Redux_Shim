
void __fastcall FUN_00669ea0(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  Concurrency::details::
  StructuredWorkStealingQueue<class_Concurrency::details::_UnrealizedChore,class_Concurrency::details::_CriticalNonReentrantLock>
  ::Reinitialize((StructuredWorkStealingQueue<class_Concurrency::details::_UnrealizedChore,class_Concurrency::details::_CriticalNonReentrantLock>
                  *)(param_1 + 2));
  return;
}

