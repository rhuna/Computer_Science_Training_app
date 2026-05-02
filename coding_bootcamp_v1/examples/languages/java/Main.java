import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Java Word Frequency Starter - enter a sentence: ");
        String[] words = scanner.nextLine().split("\\s+");
        Map<String, Integer> counts = new TreeMap<>();
        for (String word : words) {
            counts.put(word, counts.getOrDefault(word, 0) + 1);
        }
        counts.forEach((word, count) -> System.out.println(word + ": " + count));
    }
}
