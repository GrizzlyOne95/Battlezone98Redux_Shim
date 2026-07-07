// Verifies the applied names: counts functions carrying a "BSim<-BZ1.5" plate comment
// and prints a sample with name + comment. Read-only. Run with -process <reduxProgram>.
//@category BSim

import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;

public class VerifyReduxNames extends GhidraScript {
	@Override
	protected void run() throws Exception {
		Listing listing = currentProgram.getListing();
		int tagged = 0, nonDefaultNamed = 0, shown = 0;
		for (Function fn : currentProgram.getFunctionManager().getFunctions(true)) {
			if (fn.getSymbol() != null && fn.getSymbol().getSource() != SourceType.DEFAULT
					&& !fn.getName().startsWith("FUN_")) {
				nonDefaultNamed++;
			}
			String c = listing.getComment(CodeUnit.PLATE_COMMENT, fn.getEntryPoint());
			if (c != null && c.startsWith("BSim<-BZ1.5")) {
				tagged++;
				if (shown < 8) {
					println("--- " + fn.getName(true) + "  @ " + fn.getEntryPoint());
					println(c);
					shown++;
				}
			}
		}
		println("TAGGED_FUNCTIONS=" + tagged);
		println("NON_DEFAULT_NAMED_TOTAL=" + nonDefaultNamed);
	}
}
