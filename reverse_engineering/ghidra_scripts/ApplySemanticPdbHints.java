// Verify and optionally annotate/rename current Redux functions from a validated semantic-PDB TSV queue.
// @category Battlezone

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Namespace;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.SymbolTable;

import java.io.BufferedWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Pattern;

public class ApplySemanticPdbHints extends GhidraScript {
    private static final Pattern DEFAULT_FUNCTION_NAME = Pattern.compile(
        "(?i)(FUN|LAB|SUB)_[0-9a-f]+|thunk_(FUN|SUB)_[0-9a-f]+"
    );
    private static final Pattern SAFE_NAME = Pattern.compile("[A-Za-z_~][A-Za-z0-9_~]*");
    private static final Pattern SAFE_NAMESPACE = Pattern.compile("[A-Za-z_][A-Za-z0-9_]*");

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 3) {
            printerr("Usage: ApplySemanticPdbHints.java <queue.tsv> <verify|comment|rename> <results.csv>");
            return;
        }

        Path input = Paths.get(args[0]).toAbsolutePath().normalize();
        String mode = args[1].toLowerCase();
        Path output = Paths.get(args[2]).toAbsolutePath().normalize();
        if (!Arrays.asList("verify", "comment", "rename").contains(mode)) {
            throw new IllegalArgumentException("Mode must be verify, comment, or rename");
        }
        if (mode.equals("rename") && !input.getFileName().toString().equalsIgnoreCase("safe_new_apply.tsv")) {
            throw new IllegalArgumentException("Rename mode only accepts the validator's safe_new_apply.tsv queue");
        }

        List<Map<String, String>> rows = readTsv(input);
        List<List<String>> results = new ArrayList<>();
        int transaction = currentProgram.startTransaction("Apply validated semantic PDB hints");
        boolean commit = false;
        try {
            for (Map<String, String> row : rows) {
                if (monitor.isCancelled()) {
                    break;
                }
                results.add(processRow(row, mode));
                monitor.incrementProgress(1);
            }
            commit = true;
        }
        finally {
            currentProgram.endTransaction(transaction, commit);
        }
        writeResults(output, results);
        println("Processed " + results.size() + " rows; results: " + output);
    }

    private List<String> processRow(Map<String, String> row, String mode) {
        String qualifiedName = row.getOrDefault("qualified_name", "");
        String vaText = row.getOrDefault("redux_va", "");
        try {
            long va = parseNumber(vaText);
            Address address = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(va);
            Function function = currentProgram.getFunctionManager().getFunctionAt(address);
            if (function == null) {
                return result(vaText, qualifiedName, "blocked_no_function", "No function starts at the validated VA", "");
            }

            byte[] expected = parseHex(row.getOrDefault("prologue_hex", ""));
            if (expected.length == 0) {
                return result(vaText, qualifiedName, "blocked_no_fingerprint", "Queue has no prologue bytes", function.getName(true));
            }
            byte[] actual = new byte[expected.length];
            currentProgram.getMemory().getBytes(address, actual);
            if (!Arrays.equals(expected, actual)) {
                return result(
                    vaText,
                    qualifiedName,
                    "blocked_byte_mismatch",
                    "expected=" + hex(expected) + " actual=" + hex(actual),
                    function.getName(true)
                );
            }

            String currentName = function.getName(true);
            if (mode.equals("verify")) {
                return result(vaText, qualifiedName, "verified", "Function boundary and bytes agree", currentName);
            }

            appendProvenanceComment(function, row);
            if (mode.equals("comment")) {
                return result(vaText, qualifiedName, "commented", "Semantic identity remains review-only", currentName);
            }

            String namespaceText = row.getOrDefault("apply_namespace", "Global");
            String name = row.getOrDefault("apply_name", "");
            if (!safeQualifiedName(namespaceText, name)) {
                return result(vaText, qualifiedName, "blocked_unsafe_name", "Name is not safe for automatic import", currentName);
            }
            if (function.getName().equals(name) && namespaceMatches(function.getParentNamespace(), namespaceText)) {
                return result(vaText, qualifiedName, "already_named", "Existing name already agrees", currentName);
            }
            if (!DEFAULT_FUNCTION_NAME.matcher(function.getName()).matches()) {
                return result(vaText, qualifiedName, "blocked_existing_name", "Refusing to replace a non-default function name", currentName);
            }

            Namespace namespace = resolveNamespace(namespaceText);
            function.getSymbol().setNameAndNamespace(name, namespace, SourceType.IMPORTED);
            return result(vaText, qualifiedName, "renamed", "Validated queue name imported", currentName);
        }
        catch (Exception exception) {
            return result(vaText, qualifiedName, "error", exception.toString(), "");
        }
    }

    private void appendProvenanceComment(Function function, Map<String, String> row) {
        String marker = "[semantic-pdb] " + row.getOrDefault("qualified_name", "");
        String oldComment = function.getComment();
        if (oldComment != null && oldComment.contains(marker)) {
            return;
        }
        String note = marker
            + " | confidence=" + row.getOrDefault("confidence", "")
            + " score=" + row.getOrDefault("score", "")
            + " | signature=" + row.getOrDefault("pdb_signature", "")
            + " | source=" + row.getOrDefault("pdb_source_files", "")
            + ":" + row.getOrDefault("pdb_source_line_min", "")
            + "-" + row.getOrDefault("pdb_source_line_max", "")
            + " | evidence=" + row.getOrDefault("reasons", "");
        function.setComment(oldComment == null || oldComment.isBlank() ? note : oldComment + "\n" + note);
    }

    private Namespace resolveNamespace(String text) throws Exception {
        Namespace current = currentProgram.getGlobalNamespace();
        if (text.isBlank() || text.equals("Global")) {
            return current;
        }
        SymbolTable symbols = currentProgram.getSymbolTable();
        for (String part : text.split("::")) {
            Namespace found = symbols.getNamespace(part, current);
            current = found != null ? found : symbols.createNameSpace(current, part, SourceType.IMPORTED);
        }
        return current;
    }

    private boolean namespaceMatches(Namespace namespace, String expected) {
        if (expected.equals("Global")) {
            return namespace.isGlobal();
        }
        return namespace.getName(true).equals(expected);
    }

    private boolean safeQualifiedName(String namespace, String name) {
        if (!SAFE_NAME.matcher(name).matches()) {
            return false;
        }
        if (namespace.equals("Global")) {
            return true;
        }
        for (String part : namespace.split("::")) {
            if (!SAFE_NAMESPACE.matcher(part).matches()) {
                return false;
            }
        }
        return true;
    }

    private List<Map<String, String>> readTsv(Path path) throws Exception {
        List<String> lines = Files.readAllLines(path, StandardCharsets.UTF_8);
        List<Map<String, String>> rows = new ArrayList<>();
        if (lines.isEmpty()) {
            return rows;
        }
        String[] headers = lines.get(0).split("\\t", -1);
        for (int lineIndex = 1; lineIndex < lines.size(); lineIndex++) {
            if (lines.get(lineIndex).isBlank()) {
                continue;
            }
            String[] values = lines.get(lineIndex).split("\\t", -1);
            Map<String, String> row = new LinkedHashMap<>();
            for (int index = 0; index < headers.length; index++) {
                row.put(headers[index], index < values.length ? values[index] : "");
            }
            rows.add(row);
        }
        monitor.initialize(rows.size());
        return rows;
    }

    private void writeResults(Path path, List<List<String>> rows) throws Exception {
        if (path.getParent() != null) {
            Files.createDirectories(path.getParent());
        }
        try (BufferedWriter writer = Files.newBufferedWriter(path, StandardCharsets.UTF_8)) {
            writer.write("redux_va,qualified_name,status,detail,previous_name\n");
            for (List<String> row : rows) {
                writer.write(String.join(",", row.stream().map(this::csv).toList()));
                writer.write("\n");
            }
        }
    }

    private List<String> result(String va, String name, String status, String detail, String previousName) {
        return Arrays.asList(va, name, status, detail, previousName);
    }

    private String csv(String value) {
        return "\"" + value.replace("\"", "\"\"") + "\"";
    }

    private long parseNumber(String value) {
        String trimmed = value.trim();
        return trimmed.startsWith("0x") || trimmed.startsWith("0X")
            ? Long.parseUnsignedLong(trimmed.substring(2), 16)
            : Long.parseLong(trimmed);
    }

    private byte[] parseHex(String value) {
        String compact = value.replaceAll("[^0-9A-Fa-f]", "");
        if (compact.length() % 2 != 0) {
            throw new IllegalArgumentException("Odd-length prologue_hex value");
        }
        byte[] bytes = new byte[compact.length() / 2];
        for (int index = 0; index < bytes.length; index++) {
            bytes[index] = (byte) Integer.parseInt(compact.substring(index * 2, index * 2 + 2), 16);
        }
        return bytes;
    }

    private String hex(byte[] bytes) {
        StringBuilder builder = new StringBuilder();
        for (byte value : bytes) {
            if (builder.length() > 0) {
                builder.append(' ');
            }
            builder.append(String.format("%02x", value & 0xff));
        }
        return builder.toString();
    }
}
