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

        Set<String> validWords = new TreeSet<>();

        String word;
        while (!(word = getNextWord().toLowerCase()).isEmpty()) {
            if (word.length() == 31) continue;

            if (word.matches("[aeiouаеыиоуіеэ]*")) {
                validWords.add(word);
            }
        }

        for (String item : validWords) {
            System.out.println(item);
        }

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
            while ((ch = bufferedReader.read()) != -1 && !Character.isAlphabetic(ch));
            if (ch == -1) {
                return "";
            }
            word += (char)ch;
            while ((ch = bufferedReader.read()) != -1 && Character.isAlphabetic(ch)) {
                if (word.length() < 31) {
                    word += (char)ch;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            return word;
        }

    }
}
