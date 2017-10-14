import java.util.Set;
import java.util.TreeSet;

public class Main {

    public static void main(String[] args) {
        FiniteAutomaton automaton = new FiniteAutomaton();
        if (!automaton.readFromFile("input.txt")) {
            System.out.print("Wrong input");
            return;
        }

        String[] tests = {"ab", "e", "de", "b", "bd", "bdd", "bddddddddddddddddd"};
        for (String test: tests) {
            Set<String> states = new TreeSet<>();
            states.add(automaton.getStartState());
            boolean reachable = automaton.isReachableStates(automaton.getNextStates(test, states));
            System.out.printf("%s: %b\n", test, reachable);
        }
    }
}
