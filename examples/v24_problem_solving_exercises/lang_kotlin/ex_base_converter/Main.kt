fun main() { val raw = readLine(); val n = raw?.trim()?.toIntOrNull() ?: 42; println("binary " + n.toString(2)); println("hex " + n.toString(16).uppercase()) }
