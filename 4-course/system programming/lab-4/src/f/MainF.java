public class MainF {

    public static void main(String[] argv) {
        byte[] arr = new byte[32];
        try {
            int n = System.in.read(arr);
        } catch (Exception e) {
            System.out.print(e.toString());
        }
        try {
            int x = Integer.parseInt(new String(arr).trim());
            System.out.print(x * x);
        } catch (Exception e) {
            System.out.print(e.toString());
        }
    }

}
