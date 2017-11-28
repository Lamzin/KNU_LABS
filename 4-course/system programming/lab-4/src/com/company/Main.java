package com.company;


import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.TimeUnit;


public class Main {

    public static void pipeStream(InputStream input, OutputStream output) throws IOException {
        byte buffer[] = new byte[1024];
        int numRead = 0;

        do {
            numRead = input.read(buffer);
            output.write(buffer, 0, numRead);
        } while (input.available() > 0);


        output.flush();
    }

    public static void main(String[] argv) {

        InputStream tofInput = null;
        OutputStream tofOutput = null;

        OutputStream fInput = null;
        InputStream fOutput = null;

        InputStream togInput = null;
        OutputStream togOutput = null;

        OutputStream gInput = null;
        InputStream gOutput = null;

        try {

            String x = "8";
            tofInput = new ByteArrayInputStream(x.getBytes(StandardCharsets.UTF_8.name()));
            tofOutput = new ByteArrayOutputStream();

            Process processf = Runtime.getRuntime().exec("java -cp src/f MainF");
            fInput = processf.getOutputStream();
            fOutput = processf.getInputStream();
            pipeStream(tofInput, fInput);


            togInput = new ByteArrayInputStream(x.getBytes(StandardCharsets.UTF_8.name()));
            togOutput = new ByteArrayOutputStream();

            Process processg = Runtime.getRuntime().exec("java -cp src/g MainG");
            gInput = processg.getOutputStream();
            gOutput = processg.getInputStream();
            pipeStream(togInput, gInput);


            TimeUnit.SECONDS.sleep(5);
            pipeStream(fOutput, tofOutput);
            pipeStream(gOutput, togOutput);


            int f = Integer.parseInt(tofOutput.toString().trim());
            int g = Integer.parseInt(togOutput.toString().trim());

            System.out.println(f);
            System.out.println(g);
            System.out.println(f * g);

        } catch (Exception e) {
            System.out.println(e.toString());
        }
    }
}