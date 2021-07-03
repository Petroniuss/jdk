import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;

public class FixCompileCommands {
    public static void main(String[] args) throws IOException {
        if (args.length < 1) {
            System.err.println("Pass absolute path to compile_commands.json file as argument");
            System.exit(1);
        }
        final File file = new File(args[0]);
        final Path filePath = file.toPath();
        final File backupFile = new File(file.getParentFile(), file.getName() + ".old");
        Files.copy(filePath, backupFile.toPath(), StandardCopyOption.REPLACE_EXISTING);
        final String data = Files.readString(filePath);
        final String fixed = fixCompDBJsonText(data);
        Files.writeString(filePath, fixed, StandardOpenOption.WRITE);
    }

    private static String fixCompDBJsonText(String data) throws IOException {
        final String[] lines = data.split("\\r?\\n");
        if (lines.length == 1) throw new IllegalArgumentException("Multiline json file expected");
        final ArrayList<String> fixedLines = new ArrayList<>();
        for (String line : lines) {
            fixedLines.add(processLine(line));
        }
        return String.join(NEW_LINE, fixedLines);
    }

    private static String processLine(String line) throws IOException {
        final String ENTRY_LINE_PREFIX = "{ \"directory\":";
        if (!line.startsWith(ENTRY_LINE_PREFIX)) return line;
        final String FILE_PREFIX = "\"file\": \"";
        final String COMMAND_PREFIX = "\", \"command\": \"";
        final String ENTRY_LINE_SUFFIX = "\" }";
        final String prefix = substringBefore(line, FILE_PREFIX) + FILE_PREFIX;
        final String filePath = substringBefore(substringAfter(line, FILE_PREFIX), COMMAND_PREFIX);
        final String fixedFilePath = new File(filePath).getCanonicalPath();
        final String commandStr = substringBefore(substringAfter(line, COMMAND_PREFIX), ENTRY_LINE_SUFFIX);
        final String fixedCommand = fixFullCommandString(commandStr);
        final String escaped = fixedCommand.replace("\\", "\\\\").replace("\"", "\\\"");
        //fix 'file:' and compiler target paths to speedup clion import (this allow to use internal cache)
        return prefix + fixedFilePath.replace("\\", "\\\\") + COMMAND_PREFIX + escaped + ENTRY_LINE_SUFFIX + ",";
    }


    private static String fixFullCommandString(String commandString) throws IOException {
        final String[] parts = commandString.split(" ");
        ArrayList<String> fixedParts = new ArrayList<>();
        for (int i = 0; i < parts.length; i++) {
            fixedParts.add(fixPart(parts[i], i == 0));
        }
        return String.join(" ", fixedParts);
    }

    /**
     * cygpath -awl <path>
     */
    private static String fixPart(String part, boolean first) throws IOException {
        final String PATH_START = "c:/";
        if (!part.contains(PATH_START)) return part;
        String prefix = substringBefore(part, PATH_START);
        final String path = part.substring(prefix.length());
        String fixedPath = new File(path).getCanonicalPath();
        if (first) {
            // path to compiler
            if (!fixedPath.endsWith(".exe")) {
                fixedPath += ".exe";
            }
        }
        final String GCC_FO_PREFIX = "-Fo";
        final String MSVC_FO_PREFIX = "/Fo";
        //speedup clion import (this allow to use internal cache)
        if (prefix.startsWith(GCC_FO_PREFIX)) {
            prefix = MSVC_FO_PREFIX + prefix.substring(GCC_FO_PREFIX.length());
        }
        return prefix + "\"" + fixedPath + "\"";
    }

    private static String substringAfter(String string, String delimiter) {
        int index = string.indexOf(delimiter);
        if (index == -1) return string;
        return string.substring(index + delimiter.length());
    }

    private static String substringBefore(String string, String delimiter) {
        int index = string.indexOf(delimiter);
        if (index == -1) return string;
        return string.substring(0, index);
    }

    private static String NEW_LINE = System.getProperty("line.separator");
}