
/* Library Function - Single Match
    public: void __thiscall Concurrency::details::StructuredWorkStealingQueue<class
   Concurrency::details::_UnrealizedChore,class
   Concurrency::details::_CriticalNonReentrantLock>::Reinitialize(void)
   
   Library: Visual Studio */

void __thiscall
Concurrency::details::
StructuredWorkStealingQueue<class_Concurrency::details::_UnrealizedChore,class_Concurrency::details::_CriticalNonReentrantLock>
::Reinitialize(StructuredWorkStealingQueue<class_Concurrency::details::_UnrealizedChore,class_Concurrency::details::_CriticalNonReentrantLock>
               *this)

{
  *(undefined4 *)this = 0;
  *(undefined4 *)(this + 4) = 0;
  return;
}

