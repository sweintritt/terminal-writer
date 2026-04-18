import java.util.Map;
import java.util.Random;
import java.util.Scanner;
import java.util.random.RandomGenerator;

public class TerminalWriter {

    public record Mode(String name, String description, int characterWaitMin, int characterWaitMax,
                      int lineWaitMin, int lineWaitMax) {}

    private static void showHelp(final Map<String, Mode> modes) {
            System.out.println("terminal-writer (java)"
                    + " - Reads text from stdin an writes it to stdout like in old movies");
            System.out.println("terminal-writer [MODE]");
            System.out.println("Modes:");
            for (var mode : modes.values()) {
                System.out.printf("  %-11s %s%n", mode.name(), mode.description());
            }
}
    public static void main(final String[] args) {
        var modes = Map.of(
            "human", new Mode(
                    "human",
                        "Writes like a real person.",
                        75,
                        375,
                        15,
                        675),
            "80s", new Mode(
                             "80s",
                        "Prints text like in old movies.",
                        5,
                        25,
                        15,
                        675),
            "80s-fast", new Mode(
                             "80s-fast",
                        "Prints text like in old movies, but a bit faster.",
                        5,
                        15,
                        15,
                        275),
            "wc4", new Mode(
                           "wc4",
                        "Like the mission screen in Wing Commander 4.",
                        45,
                        55,
                        45,
                        75));

        if (args.length > 0) {
            var cmd = args[0];
            if ("help".equals(cmd)) {
                showHelp(modes);
            } else if (modes.containsKey(cmd)) {
                try {
                    run(modes.get(cmd));
                } catch (final Exception e) {
                    System.err.println("Error:" + e.getMessage());
                }
            } else {
                System.out.println("Unknown mode: " + cmd);
                System.out.println("See 'help' for more information.");
            }
        } else {
            System.out.println("No mode given");
            System.out.println("See 'help' for more information.");
        }
    }

    private static void run(final Mode mode) throws InterruptedException {
        var random = new Random();
        var scanner = new Scanner(System.in);
        while (scanner.hasNext()) {
            var line = scanner.nextLine();
            for (var i = 0; i < line.length(); ++i) {
                System.out.print(line.charAt(i));
                Thread.sleep(RandomGenerator.getDefault().nextInt(mode.characterWaitMin(), mode.characterWaitMax()));
            }

            Thread.sleep(RandomGenerator.getDefault().nextInt(mode.lineWaitMin(), mode.lineWaitMax()));
            System.out.println();
        }
    }
}
