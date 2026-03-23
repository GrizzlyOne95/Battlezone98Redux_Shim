
/* Library Function - Single Match
    public: virtual __thiscall CXMLParser::~CXMLParser(void)
   
   Library: Visual Studio 2010 Debug */

void __thiscall CXMLParser::~CXMLParser(CXMLParser *this)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00850648;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined ***)this =
       boost::asio::detail::
       timer_queue<struct_boost::asio::time_traits<class_boost::posix_time::ptime>_>::vftable;
  local_8 = 0;
  CTraceSnapshot::~CTraceSnapshot((CTraceSnapshot *)(this + 8));
  local_8 = 0xffffffff;
  ATL::CXMLNode<struct_IXMLDOMNode>::~CXMLNode<struct_IXMLDOMNode>
            ((CXMLNode<struct_IXMLDOMNode> *)this);
  ExceptionList = local_10;
  return;
}

