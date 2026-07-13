
/* Library Function - Single Match
    public: bool __thiscall
   Concurrency::details::UMSFreeVirtualProcessorRoot::IsSchedulingContext(struct
   Concurrency::IExecutionContext *)const 
   
   Libraries: Visual Studio 2012, Visual Studio 2015, Visual Studio 2017, Visual Studio 2019 */

bool __thiscall
Concurrency::details::UMSFreeVirtualProcessorRoot::IsSchedulingContext
          (UMSFreeVirtualProcessorRoot *this,IExecutionContext *param_1)

{
  return param_1 == *(IExecutionContext **)(this + 0x30);
}

