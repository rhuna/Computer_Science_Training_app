import java.util.*;
public class Main { public static void main(String[] args) { Scanner sc = new Scanner(System.in); int n = sc.hasNextInt() ? sc.nextInt() : 42; System.out.println("binary " + Integer.toBinaryString(n)); System.out.println("hex " + Integer.toHexString(n).toUpperCase()); } }
