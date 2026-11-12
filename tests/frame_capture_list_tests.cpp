#include "frame_capture_list.h"
#include "test_check.h"
#include <initializer_list>
#include <string>
#include <vector>
int main()
{
    using BZROpenShim::FrameCapture::ParseFrameList;
    using BZROpenShim::FrameCapture::kMaxListedFrames;
    using OpenShimTest::Check;
    std::vector<uint32_t> f;
    Check(ParseFrameList("600,1200",f) && f==std::vector<uint32_t>{600,1200},"plain list");
    Check(ParseFrameList("1200, 600 ,600",f) && f==std::vector<uint32_t>{600,1200},"sorted, deduplicated, spaces allowed");
    Check(ParseFrameList("150-153,10",f) && f==std::vector<uint32_t>{10,150,151,152,153},"inclusive range");
    Check(ParseFrameList("7-7",f) && f==std::vector<uint32_t>{7},"single-frame range");
    Check(ParseFrameList("150-899",f) && f.size()==750 && f.front()==150 && f.back()==899,"long range");
    Check(ParseFrameList("4294967295",f) && f.size()==1,"largest frame number");
    for (const char* bad:{"","  ,",",600x","600;1200","-5","9-3","1-","1--2","abc","1-4000000000","0-4294967295","99999999999"})
        Check(!ParseFrameList(bad,f) && f.empty(),"malformed or oversized lists are rejected whole");
    const std::string atCap="1-"+std::to_string(kMaxListedFrames);
    const std::string overCap="0-"+std::to_string(kMaxListedFrames);
    Check(ParseFrameList(atCap,f) && f.size()==kMaxListedFrames,"expansion at the cap");
    Check(!ParseFrameList(overCap,f),"expansion over the cap");
    return OpenShimTest::ExitCode();
}
