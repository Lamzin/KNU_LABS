package com.labs;

import java.io.*;
import java.util.Set;
import java.util.TreeSet;

public class Main {

    static final String inputFileName = "input.txt";
    static final String outputFileName = "output.txt";
    static BufferedReader bufferedReader;

    static FileInputStream input;

    public static void main(String[] args) {
        if (!openFile()) {
            return;
        }

        if (!initBuffer()) {
            return;
        }

        Set<String> searchedWords = new TreeSet<>();
        int maxLength = 0;

        String word;
        while (!(word = getNextWord().toLowerCase()).isEmpty()) {
            int length = lengthOfMaxSequenceOfConsonantsLetter(word);
            if (length > maxLength) {
                maxLength = length;
                searchedWords.clear();
                searchedWords.add(word);
            } else if (length == maxLength) {
                searchedWords.add(word);
            }
        }

        System.out.println(maxLength);
        for (String item : searchedWords) {
            System.out.println(item);
        }

    }

    private static int lengthOfMaxSequenceOfConsonantsLetter(String word) {
        int result = 0, current = 0;
        for (char ch : word.toCharArray()) {
            if (isVowelCharacter(ch)) {
                if (current > result) {
                    result = current;
                }
                current = 0;
            } else {
                current++;
            }
        }
        if (current > result) {
            result = current;
        }
        return result;
    }

    private static boolean isVowelCharacter(char ch) {
        return "aeiouаеыиоуіеэ".indexOf(ch) >= 0;
    }

    private static boolean openFile() {
        try {
             input = new FileInputStream(inputFileName);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return false;
        }
        return true;
    }

    private static boolean initBuffer() {
        try {
            bufferedReader = new BufferedReader(new InputStreamReader(input, "utf8"), 8024);
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
            return false;
        }
        return true;
    }

    private static String getNextWord() {
        String word = "";
        int ch;
        try {
            boolean nextIteration = true;
            while (nextIteration) {
                while ((ch = bufferedReader.read()) != -1 && !Character.isAlphabetic(ch));
                if (ch == -1) {
                    return "";
                }
                word += (char) ch;
                while ((ch = bufferedReader.read()) != -1 && Character.isAlphabetic(ch)) {
                    if (word.length() < 31) {
                        word += (char) ch;
                    }
                }
                nextIteration = word.length() >= 31;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return word;
    }
}
