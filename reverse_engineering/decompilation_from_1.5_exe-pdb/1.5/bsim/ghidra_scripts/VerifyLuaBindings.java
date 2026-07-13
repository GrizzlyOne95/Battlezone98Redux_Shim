// Read-only verification of the applied Lua bindings: counts functions carrying a
// "LuaAPI" plate comment, samples a few, and probes specific addresses that BSim
// previously collapsed onto one target to confirm they are now individually named.
//@category BSim

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;

public class VerifyLuaBindings extends GhidraScript {
	@Override
	protected void run() throws Exception {
		Listing listing = currentProgram.getListing();
		int lua = 0, nonDefault = 0, shown = 0;
		for (Function fn : currentProgram.getFunctionManager().getFunctions(true)) {
			if (fn.getSymbol() != null && fn.getSymbol().getSource() != SourceType.DEFAULT
					&& !fn.getName().startsWith("FUN_")) {
				nonDefault++;
			}
			String c = listing.getComment(CodeUnit.PLATE_COMMENT, fn.getEntryPoint());
			if (c != null && c.startsWith("LuaAPI")) {
				lua++;
				if (shown < 6) {
					println("--- " + fn.getName(true) + "  @ " + fn.getEntryPoint());
					println(c);
					shown++;
				}
			}
		}
		String[] cluster = { "504f10", "504f50", "504130", "500860", "5007e0",
			"500640", "503240", "503080", "505050", "501be0" };
		println("=== formerly-collided cluster (each should now be a distinct name) ===");
		for (String h : cluster) {
			Address a = currentProgram.getAddressFactory().getDefaultAddressSpace()
				.getAddress(Long.parseLong(h, 16));
			Function fn = currentProgram.getFunctionManager().getFunctionAt(a);
			println("  0x" + h + " -> " + (fn != null ? fn.getName(true) : "<none>"));
		}
		println("LUAAPI_TAGGED=" + lua);
		println("NON_DEFAULT_NAMED_TOTAL=" + nonDefault);
	}
}
