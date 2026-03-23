
/* Library Function - Single Match
    public: void __thiscall Concurrency::details::List<struct Concurrency::details::ListEntry,class
   Concurrency::details::CollectionTypes::NoCount>::Swap(class Concurrency::details::List<struct
   Concurrency::details::ListEntry,class Concurrency::details::CollectionTypes::NoCount> *)
   
   Library: Visual Studio 2012 Debug */

void __thiscall
Concurrency::details::
List<struct_Concurrency::details::ListEntry,class_Concurrency::details::CollectionTypes::NoCount>::
Swap(List<struct_Concurrency::details::ListEntry,class_Concurrency::details::CollectionTypes::NoCount>
     *this,List<struct_Concurrency::details::ListEntry,class_Concurrency::details::CollectionTypes::NoCount>
           *param_1)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)param_1;
  *(undefined4 *)param_1 = *(undefined4 *)this;
  *(undefined4 *)this = uVar1;
  return;
}

