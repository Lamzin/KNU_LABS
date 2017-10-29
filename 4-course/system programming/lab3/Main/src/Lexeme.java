public class Lexeme implements Comparable<Lexeme>{

    private int start, end;
    private String type;

    public Lexeme(int start, int end, String type) {
        this.start = start;
        this.end = end;
        this.type = type;
    }

    public int start() {
        return this.start;
    }

    public int end() {
        return this.end;
    }

    public String type() {
        return this.type;
    }

    public int compareTo(Lexeme other) {
        return this.start - other.start;
    }
}
