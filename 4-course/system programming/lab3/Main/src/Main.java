import java.io.BufferedWriter;
import java.io.FileWriter;
import java.lang.reflect.Array;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.cert.TrustAnchor;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {

    private static String sourceFile = "source.go";
    private static String htmlTemplateFile = "index_template.html";
    private static String htmlFile = "index.html";

    public static void main(String []args) {
        String source = getFileContent(sourceFile);
        if (source == null) {
            return;
        }

        LexemeDescriptor[] lexemeDescriptors = initLexemeDescriptions();
        Lexeme[] lexemes = retrieveLexemes(source, lexemeDescriptors);
        for (Lexeme lexeme : lexemes) {
            System.out.printf("%s: (%d, %d)\n", lexeme.type(), lexeme.start(), lexeme.end());
        }

        if (!fillHtmlTemplate(source, lexemes)) {
            System.out.println("Can't create template.");
        }
    }

    private static String getFileContent(String fileName) {
        try {
            return new String(Files.readAllBytes(Paths.get(fileName)));
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    private static LexemeDescriptor[] initLexemeDescriptions() {
        return new LexemeDescriptor[]{
                new LexemeDescriptor("/\\*(.|\n|\r)*?\\*/", "comment_multiline"),
                new LexemeDescriptor("//.*(\n|$)", "comment"),
        };
    }

    private static Lexeme[] retrieveLexemes(String source, LexemeDescriptor[] lexemeDescriptors) {
        ArrayList<Lexeme> lexemes = new ArrayList<>();
        for (LexemeDescriptor descriptor : lexemeDescriptors) {
            Matcher m = Pattern.compile(descriptor.regex()).matcher(source);
            while (m.find()) {
                if (m.start() == m.end()) continue;
                if (!haveIntersectionWithLexemeSegments(lexemes, m.start(), m.end())) {
                    if (m.end() == source.length()) {
                        lexemes.add(new Lexeme(m.start(), source.length() - 1, descriptor.type()));
                    } else {
                        lexemes.add(new Lexeme(m.start(), m.end(), descriptor.type()));
                    }
                }
            }
        }

        Lexeme[] lexemes_array = lexemes.toArray(new Lexeme[lexemes.size()]);
        Arrays.sort(lexemes_array);

        if (lexemes_array.length == 0) return lexemes_array;
        if (lexemes_array[0].start() > 0) {
            lexemes.add(new Lexeme(0, lexemes_array[0].start() - 1, "undefined"));
        }
        for (int i = 1; i < lexemes_array.length; i++) {
            if (lexemes_array[i - 1].end() + 1 != lexemes_array[i].start()) {
                lexemes.add(new Lexeme(
                        lexemes_array[i - 1].end() + 1,
                        lexemes_array[i].start() - 1,
                        "undefined"));
            }
        }
        if (lexemes_array[lexemes_array.length - 1].end() + 1 != source.length()) {
            lexemes.add(new Lexeme(
                    lexemes_array[lexemes_array.length - 1].end() + 1,
                    source.length() - 1,
                    "undefined"));
        }
        lexemes_array = lexemes.toArray(new Lexeme[lexemes.size()]);
        Arrays.sort(lexemes_array);
        return lexemes_array;
    }

    private static boolean haveIntersectionWithLexemeSegments(ArrayList<Lexeme> lexemes, int start, int end) {
        for (Lexeme lexeme : lexemes) {
            if (lexeme.start() <= end && lexeme.end() >= start) {
                return true;
            }
        }
        return false;
    }

    private static boolean fillHtmlTemplate(String source, Lexeme[] lexemes) {
        if (lexemes.length == 0) {
            return false;
        }

        String template = getFileContent(htmlTemplateFile);
        if (template == null) {
            return false;
        }

        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < lexemes.length; i++) {
            builder.append(String.format(
                    "<span class='%s'>%s</span>",
                    lexemes[i].type(),
                    source.substring(lexemes[i].start(), lexemes[i].end() + 1)));
        }
        return writeToFile(String.format(template, builder.toString()), htmlFile);
    }

    private static boolean writeToFile(String content, String fileName) {
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(fileName));
            writer.write(content);
            writer.close();
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

}
