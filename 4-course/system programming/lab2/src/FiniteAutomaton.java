import java.io.*;
import java.util.*;

public class FiniteAutomaton {

    private Set<String> finalStates = new TreeSet<>();

    private Map<String, Map<Character, Set<String>>> transitionFunction = new TreeMap<>();

    private String startState;

    public boolean readFromFile(String filePath) {
        Queue<String> lines = new LinkedList<>();
        String line;

        try {
            File file = new File(filePath);
            FileReader fileReader = new FileReader(file);
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            while ((line = bufferedReader.readLine()) != null) {
                lines.add(line);
            }
            fileReader.close();
        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }

        if (lines.size() < 4)
            return false;

        lines.poll();
        lines.poll();
        startState = lines.poll();
        String[] finalStatesInfo = lines.poll().split(" ");
        for (int i = 1; i < finalStatesInfo.length; i++) {
            finalStates.add(finalStatesInfo[i]);
        }
        while ((line = lines.poll()) != null) {
            String[] transition = line.split(" ");
            if (!transitionFunction.containsKey(transition[0]))
                transitionFunction.put(transition[0], new TreeMap<>());
            Map<Character, Set<String>> edges = transitionFunction.get(transition[0]);
            if (!edges.containsKey(transition[1].charAt(0)))
                edges.put(transition[1].charAt(0), new TreeSet<>());
            edges.get(transition[1].charAt(0)).add(transition[2]);
        }
        return true;
    }

    private Set<String> getNextStates(Character ch, Set<String> states) {
        Set<String> nextStates = new TreeSet<>();
        for (String state : states) {
            if (!transitionFunction.containsKey(state)) continue;
            Map<Character, Set<String>> edges = transitionFunction.get(state);
            if (!edges.containsKey(ch)) continue;
            nextStates.addAll(edges.get(ch));
        }
        return nextStates;
    }

    public Set<String> getNextStates(String word, Set<String> states) {
        for (char ch : word.toCharArray()) {
            states = getNextStates(ch, states);
        }
        return states;
    }

    private void reachableStatesDfs(String currentState, Set<String> states) {
        if (states.contains(currentState))
            return;
        states.add(currentState);
        for (Map.Entry<Character, Set<String>> keyValue : transitionFunction.get(currentState).entrySet()) {
            for (String state : keyValue.getValue()) {
                reachableStatesDfs(state, states);
            }
        }
    }

    public boolean isReachableStates(Set<String> states) {
        Set<String> reachableStates = new TreeSet<>();
        for (String state : states) {
            reachableStatesDfs(state, reachableStates);
        }
        for (String state : reachableStates) {
            if (finalStates.contains(state)) return true;
        }
        return false;
    }

    public String getStartState() {
        return startState;
    }
}
