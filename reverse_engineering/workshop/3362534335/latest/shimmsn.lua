debugprint = print;
require("_requirefix").addmod("3362534335");
local bzcp = require("_bzcp");

function Start()
	if (bzcp.install()) then
		SucceedMission(1, "shimmsn_s.des");
	else
		FailMission(1, "shimmsn_f.des");
	end
end
function Update(timestep)

end