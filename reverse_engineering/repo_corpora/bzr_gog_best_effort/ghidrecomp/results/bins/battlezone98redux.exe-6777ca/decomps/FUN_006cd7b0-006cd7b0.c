
void __thiscall FUN_006cd7b0(int param_1,int param_2)

{
  swap<>(param_1,param_2);
  Concurrency::details::
  List<struct_Concurrency::details::ListEntry,class_Concurrency::details::CollectionTypes::NoCount>
  ::Swap((List<struct_Concurrency::details::ListEntry,class_Concurrency::details::CollectionTypes::NoCount>
          *)(param_1 + 4),
         (List<struct_Concurrency::details::ListEntry,class_Concurrency::details::CollectionTypes::NoCount>
          *)(param_2 + 4));
  return;
}

