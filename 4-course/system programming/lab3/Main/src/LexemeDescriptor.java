public class LexemeDescriptor {

    private String regex, type;

    public LexemeDescriptor(String regex, String type) {
        this.regex = regex;
        this.type = type;
    }

    public String regex() {
        return this.regex;
    }

    public String type() {
        return this.type;
    }

}
